#include "Request.h"

//void Request::saveCookieFile(){
//	if(this->cookieFile == nullptr){
//		return;
//	}
//	this->cookieFile->clear();
//	this->cookieFile->beginGroup("cookie");
//	QList<QNetworkCookie> cookies = this->cookie->getCookies();
//	qDebug() << "[DEBUG]:" << FuncName << ": saved cookies:" << cookies;
//	for(QNetworkCookie c: cookies){
//		this->cookieFile->setValue(QString::fromUtf8(c.name()), QString::fromUtf8(c.value()));
//	}
//	this->cookieFile->endGroup();
//}

//void Request::loadCookieFile(){
//	if(this->cookieFile == nullptr){
//		return;
//	}
//	this->cookieFile->beginGroup("cookie");
//	QStringList keys = this->cookieFile->childKeys();
//	QList<QNetworkCookie> cookies;
//	for(QString key: keys){
//		QNetworkCookie cookie;
//		cookie.setName(key.toUtf8());
//		cookie.setValue(this->cookieFile->value(key).toString().toUtf8());
//		cookies.append(cookie);
//	}
//	this->cookie->setCookies(cookies);
//	qDebug() << "[DEBUG]:" << FuncName << ": loaded cookies:" << cookies;
//}

void Request::setRawHeaders(const QHash<QString, QString> &header){
	QStringList headerKeys = header.keys();
	foreach(QString headerKey, headerKeys){
		this->httpRequest->setRawHeader(headerKey.toUtf8(), header.value(headerKey, QString()).toUtf8());
	}
}

bool Request::waitingForResponse(QNetworkReply *reply, int timeout){
	if(waitingLoop->isRunning()){
		waitingLoop->exit();
	}
	QTimer timer;
	connect(reply, SIGNAL(finished()), this->waitingLoop, SLOT(quit()));
	connect(&timer, SIGNAL(timeout()), this->waitingLoop, SLOT(quit()));
	timer.start(timeout);
	this->waitingLoop->exec();
	if(timer.isActive()){
		timer.stop();
		return true;
	}else{
		reply->abort();
		return false;
	}
	return false;
}

Request::Response Request::integrateResponse(QNetworkReply *reply){
	Response response;
	response.statusCode = 0;
	if(reply == nullptr){
		qDebug() << FuncName << ": QNetworkReply is nullptr";
		response.error = QNetworkReply::UnknownServerError;
		return response;
	}
	if(reply->error() != QNetworkReply::NoError){
		qDebug() << FuncName << ": QNetworkReply Has Error:" << reply->errorString();
		response.error = reply->error();
		response.errorContent = reply->errorString();
		return response;
	}
	bool ok = false;
	QVariant statusCodeVariant = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	int statusCode = statusCodeVariant.toInt(&ok);
	if(!ok){
		qDebug() << __func__ << "integrateResponse: HttpStatusCodeAttribute not integer. data:" << (statusCodeVariant.isNull() ? "Null" : statusCodeVariant);
		response.error = QNetworkReply::UnknownServerError;
		return response;
	}
	qint64 bytesAvailable = 0;
	do{
		bytesAvailable = reply->bytesAvailable();
		QThread::currentThread()->msleep(10);
	}while(bytesAvailable != reply->bytesAvailable());

	if(reply->error() == QNetworkReply::NoError){
		response.statusCode = statusCode;
		response.content = reply->readAll();
		response.error = QNetworkReply::NoError;
		response.errorContent = QString();
	}else{
		response.statusCode = 0;
		response.content = QByteArray();
		response.error = reply->error();
		response.errorContent = reply->errorString();
	}

#ifdef DEBUG_VERBOSE
	QList<QNetworkCookie> cookies = this->cookie->getCookies();
	for(QNetworkCookie c: cookies){
		qDebug() << "[INFOR]:" << FuncName << ": cookie key:" << c.name() << "value:" << c.value() << "domain:" << c.domain();
	}
	for(QNetworkReply::RawHeaderPair a: reply->rawHeaderPairs()){
		qDebug() << "[INFOR]:" << FuncName << ": response header:" << a.first << "=" << a.second;
	}
#endif
	//this->saveCookieFile();

	return response;
}

void Request::integrateRequest(){
#ifdef DEBUG_VERBOSE
	QByteArrayList headers = this->httpRequest->rawHeaderList();
	for(QByteArray header: headers){
		qDebug() << "[INFOR]:" << FuncName << ": request header:" << header << "=" << this->httpRequest->rawHeader(header);
	}
#endif
}

Request::Request(const QHash<QString, QString> &header, QObject *parent) : QObject(parent){
	this->setRawHeaders(header);

	//	this->cookieFile = new QSettings("cookies.ini", QSettings::IniFormat);
	//	this->cookieFile->setIniCodec("utf-8");

	this->networkAccessManager->setCookieJar(this->cookie);
	//this->loadCookieFile();
	//this->connect(this->networkAccessManager, &QNetworkAccessManager::finished, this, &Request::requestFinished);
}

Request::Request(QObject *parent) : QObject(parent){
//	this->cookieFile = new QSettings("cookies.ini", QSettings::IniFormat);
//	this->cookieFile->setIniCodec("utf-8");

	this->networkAccessManager->setCookieJar(this->cookie);
}

Request::~Request(){
	this->saveCookie();
	this->networkAccessManager->disconnect();
	if(this->httpRequest != nullptr){
		delete this->httpRequest;
	}
}

Request::Response Request::get(const QString &url){
	this->integrateRequest();
	qDebug() << "[INFOR]:" << FuncName << ": Request: GET:" << url;
	this->httpRequest->setUrl(QUrl(url));
	QNetworkReply *reply = this->networkAccessManager->get(*this->httpRequest);
	if(!this->waitingForResponse(reply)){
		return Response{408, QByteArray(), QNetworkReply::TimeoutError, "Request Timeout."};
	}
	Response res = this->integrateResponse(reply);
	reply->deleteLater();
	return res;
}

Request::Response Request::post(const QString &url, const QByteArray &data){
	this->integrateRequest();
	QByteArray _d = QByteArray(data);
	_d.replace('\n', "");
	qDebug() << "[INFOR]:" << FuncName << ": Request: POST(1):" << url << "-d" << _d;
	this->httpRequest->setUrl(QUrl(url));
	QNetworkReply *reply = this->networkAccessManager->post(*this->httpRequest, _d);
	if(!this->waitingForResponse(reply)){
		return Response{408, QByteArray(), QNetworkReply::TimeoutError, "Request Timeout."};
	}
	Response res = this->integrateResponse(reply);
	reply->deleteLater();
	return res;
}

Request::Response Request::post(const QString &url, const QString &data){
	this->integrateRequest();
	QString _d = QString(data).replace(QRegExp("[\\s\\n]"), "");
	qDebug() << "[INFOR]:" << FuncName << ": Request: POST(2):" << url << "-d" << _d;
	QByteArray _data = _d.toUtf8().toPercentEncoding();
	this->httpRequest->setUrl(QUrl(url));
	QNetworkReply *reply = this->networkAccessManager->post(*this->httpRequest, _data);
	if(!this->waitingForResponse(reply)){
		return Response{408, QByteArray(), QNetworkReply::TimeoutError, "Request Timeout."};
	}
	Response res = this->integrateResponse(reply);
	reply->deleteLater();
	return res;
}

Request::Response Request::post(const QString &url, const QHash<QString, QString> data){
	this->integrateRequest();
//	QStringList postArray;
//	QStringList keys = data.keys();
//	for(QString key: keys){
//		postArray.append(key.append("=").append(data.value(key)));
//	}
//	QByteArray _data = postArray.join("&").toUtf8();
	QByteArray _data = Utils::urlParamsBuilder(data).toUtf8();

//	QByteArray _d = QByteArray(_data).replace(' ', "");
//	_d.replace('\n', "");
	qDebug() << "[INFOR]:" << FuncName << ": Request: POST(3):" << url << "-d" << _data;

	this->httpRequest->setUrl(QUrl(url));
	QNetworkReply *reply = this->networkAccessManager->post(*this->httpRequest, _data);
	if(!this->waitingForResponse(reply)){
		return Response{408, QByteArray(), QNetworkReply::TimeoutError, "Request Timeout."};
	}
	Response res = this->integrateResponse(reply);
	reply->deleteLater();
	return res;
}






