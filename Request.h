#ifndef REQUEST_H
#define REQUEST_H

#include "Global.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QSettings>
#include "NetworkCookie.h"


class Request : public QObject
{
	Q_OBJECT
	const QString cookieIniFileName = "cookie.ini";
public:
	typedef struct{
		int statusCode;
		QByteArray content;
		QNetworkReply::NetworkError error;
		QString errorContent;
	} Response;
private:

	QNetworkRequest *httpRequest = new QNetworkRequest();
	QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager(this);
	NetworkCookie *cookie = new NetworkCookie(this);

	bool isFinished = false;
	QEventLoop *waitingLoop = new QEventLoop(this);

	void setRawHeaders(const QHash<QString, QString> &header);

	bool waitingForResponse(QNetworkReply *reply, int timeout = 30000);

	Response integrateResponse(QNetworkReply *reply);

	void integrateRequest();

public:

	Request(const QHash<QString, QString> &header, QObject *parent = 0);
	Request(QObject *parent = 0);

	~Request();

	Response get(const QString &url);

	Response post(const QString &url, const QByteArray &data);
	Response post(const QString &url, const QString &data);
	Response post(const QString &url, const QHash<QString, QString> data);

	inline QList<QNetworkCookie> getCookie(){
		return this->cookie->getCookies();
	}

	inline void setCookie(const QList<QNetworkCookie> &cookie){
		this->cookie->setCookies(cookie);
	}

	inline void setHeaders(const QHash<QString, QString> &header){
		this->setRawHeaders(header);
	}

	inline void saveCookie(){
		this->cookie->saveCookie(this->cookieIniFileName);
	}

	inline void loadCookie(){
		this->cookie->loadCookie(this->cookieIniFileName);
	}

protected:
//	virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;

signals:
//	void responseSignal(QString name, Response response);

public slots:
//	void serviceRequestFinished(QNetworkReply *reply){
//		if(reply == nullptr){
//			qDebug() << __func__ << "QNetworkReply is nullptr";
//			return;
//		}
//		bool ok = false;
//		int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(&ok);
//		if(!ok){
//			qDebug() << __func__ << "HttpStatusCodeAttribute not integer.";
//			return;
//		}
//		if(reply->error() == QNetworkReply::NoError){
//			Response response;
//			response.name = this->name;
//			response.statusCode = statusCode;
//			response.content = reply->readAll();
//			response.error = QNetworkReply::NoError;
//			response.errorContent = QString();
//			emit this->responseSignal(this->name, response);
//		}else{
//			Response response;
//			response.name = this->name;
//			response.statusCode = 0;
//			response.content = QByteArray();
//			response.error = reply->error();
//			response.errorContent = reply->errorString();
//			emit this->responseSignal(this->name, response);
//		}

//		reply->deleteLater();
//	}
};

#endif // REQUEST_H
