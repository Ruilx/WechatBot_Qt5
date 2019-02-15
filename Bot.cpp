#include "Bot.h"

void Bot::sendAlertMessage(QString message){
	static const QString receiver = "The phone number";
	emit this->falltoAlert(receiver, message);
}

void Bot::updateNameList(const Bot::Contact &c){
	if(this->userNameList.contains(c.userName)){
		this->userNameList.remove(c.userName);
	}
	this->userNameList.insert(c.userName, c);
	if(this->nickNameList.contains(c.nickName)){
		this->nickNameList.remove(c.nickName);
	}
	this->nickNameList.insert(c.nickName, c);
	if(this->remarkNameList.contains(c.remarkName)){
		this->remarkNameList.remove(c.remarkName);
	}
	this->remarkNameList.insert(c.remarkName, c);
	if(this->uinList.contains(c.uin)){
		this->uinList.remove(c.uin);
	}
	this->uinList.insert(c.uin, c);
}

void Bot::messageProcessing(Message msg){
	qDebug() << "[INFOR]:" << FuncName << ": Message:";
	qDebug() << "[INFOR]:" << FuncName << ": ----> FromUserName:" << msg.fromUserName << "(" << this->userNameList.value(msg.fromUserName).nickName << ")";
	qDebug() << "[INFOR]:" << FuncName << ": ----> ToUserName:  " << msg.toUserName << "(" << this->userNameList.value(msg.toUserName).nickName << ")";
	qDebug() << "[INFOR]:" << FuncName << ": ----> Content:     " << msg.content;
	qDebug() << "[INFOR]:" << FuncName << ": ----> MessageId:   " << msg.messageId;

	if(!msg.content.startsWith("# ")){
		qDebug() << "[INFOR]:" << FuncName << ": message not start with '#', abandoned.";
	}else{
		emit this->messageProcessingSignal(msg);
	}
//	Bot::Message reply;
//	reply.fromUserName = msg.toUserName;
//	reply.toUserName = msg.fromUserName;
//	reply.content = msg.content;
//	this->sendMessage(reply);
}

void Bot::timerEvent(QTimerEvent *){
	static int failedTimes = 0;
	this->stopTimer();
	if(this->sync() == false){
		if(this->forceToExit){
			qDebug() << "[FATAL]:" << FuncName << ": sync failed, fatal error exit.";
			this->request->saveCookie();
			this->sendAlertMessage("Failed to sync wechat informations.");
			//emit this->exitThread(QThread::currentThread());
			ThreadController::getInstance()->quitAllThread();
			return;
		}else{
			if(failedTimes < 10){
				qDebug() << "[WARNI]:" << FuncName << ": sync failed, but still has retry chance.";
			}else{
				qDebug() << "[FATAL]:" << FuncName << ": sync failed, no more retry chance.";
				this->request->saveCookie();
				this->sendAlertMessage(QString("Failed to sync wechat informations. retry times: %1").arg(failedTimes));
				ThreadController::getInstance()->quitAllThread();
			}
		}
	}else{
		qDebug() << "[INFOR]:" << FuncName << ": Get sync. Normal state returned.";
	}
	this->resumeTimer();
	this->snapshot->saveSnapshot(this->params, this->syncList, this->syncCount);
	this->syncCount++;
}

bool Bot::doLogin(){
	int failedTimes = 0;
	if(!this->login()){
		while(!this->login(false)){
			qDebug() << "[WARNI]:" << FuncName << ": Login Failure times:" << failedTimes;
			if(failedTimes >= 20){
				this->sendAlertMessage(QString("Failed to login Wechat Platform. 阈值: 20, 已对接失败次数:%1").arg(failedTimes));
				qDebug() << "[FATAL]:" << FuncName << ": Failed to login Wechat Platform. Failed: " << failedTimes << "/20";
				return false;
			}else{
				failedTimes++;
			}
		}
	}
	return true;
}

Bot::Bot(QObject *parent) : QObject(parent){
	this->params.insert("uuid", "");
	this->params.insert("skey", "");
	this->params.insert("sid", "");
	this->params.insert("uin", "");
	this->params.insert("pass_ticket", "");
	this->params.insert("device_id", QString("e").append(Utils::repeat(Utils::rand, 15)));
	this->params.insert("base_uri", "");
	this->params.insert("base_host", "");
	//this->params.insert("base_request", "");
	this->params.insert("sync_host", "");
	// this->params.insert("sync_key", "");
	this->params.insert("sync_key_str", "");
}

bool Bot::getQrCode(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	QHash<QString, QString> params;
	params.insert("appid", Global::getInstance()->getWechatAppId());
	params.insert("fun", "new");
	params.insert("lang", "zh_CN");
	params.insert("_", Utils::now());
	try{
		//Request request("getQrCode", Global::getInstance()->getWechatHeaders());
		this->request->setHeaders(Global::getInstance()->getWechatHeaders());
		Request::Response response = this->request->get(QString(Global::getInstance()->getWechatFirstLoginUrl()).append("?").append(Utils::urlParamsBuilder(params)));
		if(response.error != QNetworkReply::NoError){
			throw response;
		}
		WechatProtocol::Response_jslogin res = WechatProtocol::resolve_jslogin(response.content);
		if(res.window_QRLogin_code != "200"){
			throw QString("res.window_QRLogin_code != 200");
		}
		this->params["uuid"] = res.window_QRLogin_uuid;
		qDebug() << "[INFOR]:" << FuncName << ": User's UUID:" << this->params.value("uuid");

		//			QString data = QString::fromUtf8(response.content);
		//			QString regex = "window.QRLogin.code = (\\d+); window.QRLogin.uuid = \"(\\S+?)\"";
		//			QStringList resGroup = data.replace(QRegExp(regex), "\\1 \\2").split(" ");
		//			if(resGroup.length() < 2){
		//				throw QString("resGroup length < 2");
		//			}
		//			QString code = resGroup[0];
		//			this->params["uuid"] = resGroup[1];
		//			qDebug() << "[DEBUG]" << __func__ << " User's UUID: " << this->params.value("uuid");
		//			if(code != "200"){
		//				throw QString("resGroup code != 200");
		//			}

		//Request requestQrCodePic("getQrCodePic", Global::getInstance()->getWechatHeaders());
		this->request->setHeaders(Global::getInstance()->getWechatHeaders());
		Request::Response responseQrCodePic = this->request->get(QString(Global::getInstance()->getWechatGetQrCodePicUrl(this->params.value("uuid"))));
		if(responseQrCodePic.error != QNetworkReply::NoError){
			throw response;
		}
		QByteArray dataQrcodePic = responseQrCodePic.content;
		if(dataQrcodePic.isEmpty()){
			throw QString("responseQrCodePic.dataQrcodePic is null.");
		}
//		qDebug() << "[INFOR]:" << FuncName << ": responseQrCodePic.content:" << responseQrCodePic.content.left(100);

		this->showQrCodeDialog->setPixmap(dataQrcodePic);
		connect(this->qrThread, SIGNAL(started()), this->showQrCodeDialog, SLOT(show()));
		connect(this->qrThread, SIGNAL(finished()), this->showQrCodeDialog, SLOT(deleteLater()));
		connect(this, SIGNAL(setQrPixmap(QByteArray)), this->showQrCodeDialog, SLOT(setPixmapSlot(QByteArray)));
		ThreadController::getInstance()->insertThread((qint64)this->qrThread, this->qrThread);
		this->qrThread->start();

	}catch(Request::Response response){
		qDebug() << "[ERROR]:" << FuncName << "Response error:" << response.errorContent;
		return false;
	}catch(QString str){
		qDebug() << "[ERROR]:" << FuncName << "String error:" << str;
		return false;
	}
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================" << "RETURN";
	return true;
}

bool Bot::init(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	QString url = Global::getInstance()->getWechatInitUrl(this->params.value("base_uri"), Utils::time_negate(), this->params.value("pass_ticket"));
	QJsonObject baseRequest{
		{"Uin", this->params.value("uin")},
		{"Sid", this->params.value("sid")},
		{"Skey", this->params.value("skey")},
		{"DeviceID", this->params.value("device_id")}
	};
	QJsonObject request{
		{"BaseRequest", baseRequest}
	};
	QJsonDocument jsonDumps(request);
	WechatProtocol::Response_webwxinit res;
	try{
		//Request request("login", Global::getInstance()->getWechatHeaders(), this);
		this->request->setHeaders(Global::getInstance()->getWechatLoginHeaders());
		Request::Response response = this->request->post(url, jsonDumps.toJson(QJsonDocument::Compact));
		if(response.error != QNetworkReply::NoError){
			throw response;
		}
		res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxinit(response.content);
		if(res.baseResponse.ret == "-1"){
			throw QString("data resolve failed.");
		}

		this->syncList.count = res.syncKey.count;
		this->syncList.list = res.syncKey.list;

		this->params["sync_key_str"] = Utils::syncKeyStrBuilder(this->syncList);
		qDebug() << "[INFOR]:" << "User's syncKeyStr" << this->params["sync_key_str"];

		// insert active contact list
		for(WechatProtocol::Contact mem: res.ContactList){
			Contact c;
			c.userName = mem.userName;
			c.nickName = mem.nickName;
			c.remarkName = mem.remarkName;
			c.displayName = mem.displayName;
			c.uin = mem.uin;
			qDebug() << "[INFOR]:" << FuncName << ": InitName:" << c.userName << "NickName:" << c.nickName << "RemarkName:" << c.remarkName << "DisplayName:" << c.displayName;
			this->updateNameList(c);
		}

		// recover my profile
		this->myProfile = res.user;
		Contact c;
		c.userName = res.user.userName;
		c.nickName = res.user.nickName;
		c.remarkName = res.user.remarkName;
		c.uin = res.user.uin;
		c.displayName = "";
		qDebug() << "[INFOR]:" << FuncName << ": MyName:" << c.userName << "NickName:" << c.nickName << "RemarkName:" << c.remarkName << "DisplayName:" << c.displayName;
		this->updateNameList(c);

	}catch(Request::Response response){
		qDebug() << "[ERROR]:" << FuncName << "Response error:" << response.errorContent;
		return false;
	}catch(QString str){
		qDebug() << "[ERROR]:" << FuncName << "String error:" << str;
		return false;
	}
	return res.baseResponse.ret == 0;
}

bool Bot::statusNotify(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	QString url = Global::getInstance()->getWechatStatusNotify(this->params.value("base_uri"), this->params.value("pass_ticket"));
	QJsonObject baseRequest{
		{"Uin", this->params.value("uin")},
		{"Sid", this->params.value("sid")},
		{"Skey", this->params.value("skey")},
		{"DeviceID", this->params.value("device_id")}
	};
	QJsonObject request{
		{"BaseRequest", baseRequest},
		{"ClientMsgId", Utils::now()},
		{"Code", 3},
		{"FromUserName", this->myProfile.userName},
		{"ToUserName", this->myProfile.userName}
	};
	QJsonDocument jsonDumps(request);
	try{
		this->request->setHeaders(Global::getInstance()->getWechatMsgHeaders());
		Request::Response response = this->request->post(url, jsonDumps.toJson(QJsonDocument::Compact));
		if(response.error != QNetworkReply::NoError){
			throw response;
		}
		WechatProtocol::Response_webwxstatusnotify res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxstatusnotify(response.content);
		if(res.baseResponse.ret == "-1"){
			throw QString("data resolve failed.");
		}
		if(res.baseResponse.ret != "0"){
			throw QString("Wechat reported that this request is failed: retCode: %1, msg: %2").arg(res.baseResponse.ret).arg(res.baseResponse.errMsg);
		}
		qDebug() << "[INFOR]:" << FuncName << ": Get MsgId:" << res.msgId;
		return true;
	}catch(Request::Response res){
		qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
		return false;
	}catch(QString str){
		qDebug() << "[ERROR]:" << FuncName << ": String error:" << str;
		return false;
	}
}

bool Bot::login(bool usingSnapShot){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	qDebug() << "[INFOR]:" << FuncName << ": Using snapShot:" << usingSnapShot;
	if(usingSnapShot){
		this->snapshot->readSnapshot(this->params, this->syncList, this->syncCount);
	}else{
		if(this->params.value("uin").isEmpty() || this->params.value("base_uri").isEmpty()){
			// 扫描二维码登录
			this->getQrCode();
		}else{
			// 手机确认登录
			this->request->loadCookie();
			qDebug() << "[DEBUG]:" << FuncName << ": loaded cookie:" << this->request->getCookie();
			QString url = Global::getInstance()->getWechatPushLoginUrl(this->params.value("base_uri"), this->params.value("uin"));
			this->request->setHeaders(Global::getInstance()->getWechatHeaders());
			try{
				Request::Response response = this->request->get(url);
				if(response.error != QNetworkReply::NoError){
					throw response;
				}
				WechatProtocol::Response_webwxpushloginurl res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxpushloginurl(response.content);
				if(res.ret == "-1"){
					throw QString("Data resolve failed.");
				}
				if(res.ret != "0"){
					throw QString("Wechat reported that push login ret's failed: msg: %1").arg(res.msg);
				}
				if(!res.uuid.isEmpty()){
					this->params["uuid"] = res.uuid;
				}else{
					throw QString("UUID is empty.");
				}

				goto tryLogin;
			}catch(Request::Response res){
				qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
				this->params["uin"] = "";
				return false;
			}catch(QString str){
				qDebug() << "[ERROR]:" << FuncName << ": String error:" << str;
				this->params["uin"] = "";
				return false;
			}
		}
	}

	if(usingSnapShot && this->syncList.list.isEmpty()){
		qDebug() << "[INFOR]:" << FuncName << ": synclist is empty, will using qrcode login.";
		return false;
	}

tryLogin:

	QString redirectUrl;
	int tip = 1;

	while(redirectUrl.isEmpty()){
		QString url = Global::getInstance()->getWechatSecondLoginUrl(QString::number(tip), this->params.value("uuid"));

		try{
			//Request request("login", Global::getInstance()->getWechatHeaders());
			this->request->setHeaders(Global::getInstance()->getWechatLoginHeaders());
			Request::Response response = this->request->get(url);
			if(response.error != QNetworkReply::NoError){
				throw response;
			}
//			if(response.content.startsWith('\x1F')){
//				qDebug() << "RESPONSE:" << QString::fromUtf8(response.content);
//				Q_ASSERT(false);
//			}
			WechatProtocol::Response_login res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_login(response.content);
			if(res.window_code == "0"){
				throw QString("data resolve failed.");
			}else if(res.window_code == "201"){
				QByteArray avatar = res.window_userAvatar;
				QByteArray newAvatar = QByteArray::fromBase64(avatar.remove(0,20));
				//this->showQrCodeDialog->setPixmap(newAvatar);
				emit this->setQrPixmap(newAvatar);
				tip = 0;
			}else if(res.window_code == "200"){
				//redirectUrl = res.window_redirect_uri.append("&fun=new&version=v2");
				redirectUrl = res.window_redirect_uri.append("&fun=new");
				QUrl url(redirectUrl);
				if(!url.isValid()){
					throw QString("invaild redirect url:").append(redirectUrl);
				}
				/*
				[DEBUG] User's base_uri: https://wx2.qq.com/cgi-bin/mmwebwx-bin
				[DEBUG] User's base_host: wx2.qq.com
				[DEBUG] Direct URL: https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxnewloginpage?ticket=A7L5HGy_A57myGlz1gj-JMaZ@qrticket_0&uuid=od2b4XJNBA==&lang=zh_CN&scan=1501961815&fun=new
				*/
				QStringList urlPattern = url.path().split("/", QString::SkipEmptyParts);
				QString path = "/";
				if(urlPattern.length() >= 2){
					for(int i = 0; i < urlPattern.length() -1; i++){
						path.append(urlPattern.at(i));
						if(i < urlPattern.length() -2){
							path.append("/");
						}
					}
				}else{
					path = url.path();
					/* 微信的LoginBasePath必定是分割大于等于两块的, 其中baseUri是删除最后一块的Action地址名, 一般微信URL固定为
					 * /cgi-bin/mmwebwx-bin/
					 * 拿到的却是/cgi-bin/mmwebwx-bin/webwxnewloginpage
					 * 所以要将后面的webwxnewloginpage去掉, 所以这个else一般不执行
					 */
				}
				this->params["base_host"] = QString("https://").append(url.host());
				this->params["base_uri"] = QString(this->params.value("base_host")).append(path);
				qDebug() << "[INFOR]:" << FuncName << ": User's base_host:" << this->params.value("base_host");
				qDebug() << "[INFOR]:" << FuncName << ": User's base_uri:" << this->params.value("base_uri");
			}else if(res.window_code == "400"){
				throw QString("Snapshot expired.");
				return false;
			}else if(res.window_code == "408"){
				tip = 1;
				continue;
			}
		}catch(Request::Response res){
			qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
			return false;
		}catch(QString str){
			qDebug() << "[ERROR]:" << FuncName << ": String error:" << str;
			return false;
		}
	}
	//this->showQrCodeDialog->close();
	ThreadController::getInstance()->quitThread(this->qrThread);
	this->qrThread = nullptr;

//	try{
//		this->request->setHeaders(Global::getInstance()->getWechatHeaders());
//		qDebug() << "[DEBUG]:" << FuncName << "第一次以普通Headers来请求页面写入cookie, 不获取其返回";
//		Request::Response response = this->request->get(redirectUrl);
//		if(response.error != QNetworkReply::NoError){
//			throw response;
//		}
//		qDebug() << "[DEBUG]:" << FuncName << "瞅一眼response:" << response.content;
//	}catch(Request::Response res){
//		qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
//		return false;
//	}

	try{
		//Request request("getUserData", Global::getInstance()->getWechatHeaders());
		//this->request->setHeaders(Global::getInstance()->getWechatLoginHeaders());
		this->request->setHeaders(Global::getInstance()->getWechatHeaders());
		//qDebug() << "[DEBUG]:" << FuncName << "第二次以login的Headers来请求页面获得XML.";
		Request::Response response = this->request->get(redirectUrl);
		if(response.error != QNetworkReply::NoError){
			throw response;
		}
		WechatProtocol::Response_webwxnewloginpage res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxnewloginpage(response.content);
		if(res.ret == "-1"){
			throw QString("data resolve failed: data:'%1' message:'%2'").arg(QString(response.content)).arg(res.message);
		}
		this->params["skey"] = res.skey;
		qDebug() << "[DEBUG]:" << FuncName << ": User's skey:" << this->params.value("skey");
		this->params["sid"] = res.wxsid;
		qDebug() << "[DEBUG]:" << FuncName << ": User's sid:" << this->params.value("sid");
		this->params["uin"] = res.wxuin;
		qDebug() << "[DEBUG]:" << FuncName << ": User's uin:" << this->params.value("uin");
		this->params["pass_ticket"] = res.pass_ticket;
		qDebug() << "[DEBUG]:" << FuncName << ": User's pass_ticket:" << this->params.value("pass_ticket");

		this->baseRequest.device_id = this->params.value("device_id");
		this->baseRequest.sid = this->params.value("sid");
		this->baseRequest.uin = this->params.value("uin");
		this->baseRequest.skey = this->params.value("skey");
	}catch(Request::Response res){
		qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
		return false;
	}catch(QString str){
		qDebug() << "[ERROR]:" << FuncName << ": String error:" << str;
		return false;
	}

	this->init();
	this->snapshot->saveSnapshot(this->params, this->syncList, this->syncCount);
	return true;
}

WechatProtocol::Response_synccheck Bot::syncCheck(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	int failedTimes = 0;
	while(failedTimes < 10){
		QHash<QString, QString> params;
		params.insert("r", Utils::time_negate());
		params.insert("skey", this->params.value("skey"));
		params.insert("sid", this->params.value("sid"));
		params.insert("uin", this->params.value("uin"));
		params.insert("deviceid", this->params.value("device_id"));
		params.insert("synckey", this->params.value("sync_key_str"));
		params.insert("_", Utils::now());

		QString url = Global::getInstance()->getWechatBotSyncCheckUrl(this->params.value("sync_host"), Utils::urlParamsBuilder(params));
		//Request request("syncCheck", Global::getInstance()->getWechatHeaders());
		this->request->setHeaders(Global::getInstance()->getWechatHeaders());

		try{
			Request::Response response = this->request->get(url);
			if(response.error != QNetworkReply::NoError){
				throw response;
			}
			WechatProtocol::Response_synccheck res =  WechatProtocol::resolve_cgi_bin_mmwebwx_bin_synccheck(response.content);
			if(res.retcode == "-1"){
				throw QString("data resolve failed.");
			}
			if(res.retcode == "0" && res.selector == "0"){
				if(failedTimes != 0){
					qDebug() << "[DEBUG]: Recoveryed from failed stage," << failedTimes << " retried attached.";
					failedTimes = 0;
				}
				// 使用continue的话会使这个线程一直处于忙碌阶段而无法进行发送信息(前提是必须有一段回到事件循环中才能触发发送消息的信息)
				// 在这里进行return, 因为上层(调用该函数)的函数对0进行了判断, 所以在这里直接返回0, 并重置失败次数.
				// 上面这段判断代码在return的时候其实不起什么作用, 只是输出一下成功之前有失败的尝试.
				//continue;
				return res;
			}else{
				return res;
			}
		}catch(Request::Response res){
			qDebug() << "[ERROR]:" << FuncName << ": Response Error:" << res.errorContent << "Failed times:" << failedTimes;
			failedTimes++;
		}catch(QString str){
			qDebug() << "[ERROR]:" << FuncName << ": String Error:" << str << "Failed times:" << failedTimes;
			failedTimes++;
		}
	}
	qDebug() << "[ERROR]:" << FuncName << ": Failed times out of range." << "Threshold times:" << failedTimes;
	return WechatProtocol::Response_synccheck{"-1", "-1"};
}

bool Bot::sync(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	qDebug() << "[INFOR]:" << FuncName << "SyncCount:" << this->syncCount;
	/**
	 * return:: true: 表示此次循环放弃, 择时执行新的循环片段.
	 * return::false: 表示此循环失败, 不用再进行循环, 已失败.
	 */
	WechatProtocol::Response_synccheck res = this->syncCheck();
	if(res.retcode == "-1"){
		qDebug() << "[ERROR]:" << FuncName << "Sync reported sync is failed, Exiting...";
		qDebug() << "[ERROR]:" << "Failed.";
		//TODO: emit join the thread.
		return false;
	}else if(res.retcode == "0"){
		if(res.selector == "0"){
			// Normal request
			return true;
		}else if(res.selector == "2"){
			// New message
			QThread::currentThread()->msleep(1000);
			this->handleMsg();
			return true;
		}else if(res.selector == "7"){
			// Enter/Exit the chat area.
			//TODO: Reserved.
			return true;
		}
	}else if(res.retcode == "1100"){
		// Failed & exitted.
		//TODO: exit or relogin.
		static int loginFailedTimes = 0;
		qDebug() << "[ERROR]:" << FuncName << ": Wechat reported that this account has been logouted. tried to relogin. Failed times:" << loginFailedTimes;
		if(loginFailedTimes < 10 && this->doLogin()){
			loginFailedTimes = 0;
			return true;
		}else{
			return false;
		}
	}else if(res.retcode == "1101"){
		// 1101 means the request is out of time.
		// give the message to next sync check.
		qDebug() << "[WARNI]:" << FuncName << ": Wechat reported that the request is out of date.";
		return true;
	}else if(res.retcode == "1102"){
		// maybe cookie set wrong?
		//TODO: exit...? temp... not exit.
		qDebug() << "[ERROR]:" << FuncName << ": Wechat reported that this terminal had a bad request cookie?";
		return false;
	}
	qDebug() << "[ERROR]:" << FuncName << ": an unsupport retcode:" << res.retcode;
	return false;
}

void Bot::start(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	// Do Login
	if(!this->doLogin()){
		return;
	}
	// Status Notify
	if(!this->statusNotify()){
		qDebug() << "[ERROR]:" << FuncName << ": Status Notify Failed.";
	}
	// GetContact
	bool ok = false;
	for(int i = 0; i < 10; i++){
		if(!this->getContact()){
			qDebug() << "[ERROR]:" << FuncName << ": Get Contact Failed.";
		}else{
			ok = true;
			break;
		}
	}
	if(!ok){
		qDebug() << "[FATAL]:" << FuncName << ": Get Contact failed out of trying times.";
		qApp->exit(1);
		ThreadController::getInstance()->quitAllThread();
	}
	// Find sync host
	if(!this->syncHostCheck()){
		qDebug() << "[FATAL]:" << FuncName << ": Check host failed.";
		qApp->exit(1);
		ThreadController::getInstance()->quitAllThread();
	}
	QStringList names;
	for(QString key: this->userNameList.keys()){
		if(key.startsWith("@@")){
			names.append(key);
		}
	}
	if(!names.isEmpty()){
		this->getBatchContact(names);
	}
	// Ready Timer
	this->resumeTimer();
}

bool Bot::syncHostCheck(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	// Test webpush(2).wx2.qq.com for sync host
	QStringList hosts = (QStringList() << "webpush." << "webpush2.");
	for(QString host: hosts){
		this->params["sync_host"] = host.append(QString(this->params.value("base_host")).remove("https://"));
		qDebug() << "[INFOR]:" << FuncName << ": sync host:" << this->params.value("sync_host");
		WechatProtocol::Response_synccheck res = this->syncCheck();
		if(res.retcode == "0"){
			return true;
		}
	}
	qDebug() << "[ERROR]:" << FuncName << ": sync host not found.";
	return false;
}

WechatProtocol::Response_webwxsync Bot::syncMessage(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	QString url = Global::getInstance()->getWechat_cgi_bin_mmwebwx_bin_webwxsync(this->params.value("base_uri"), this->params.value("sid"), this->params.value("skey"), this->params.value("pass_ticket"));
	WechatProtocol::Request_webwxsync req;
	req.baseRequest.deviceId = this->params.value("device_id");
	req.baseRequest.sid = this->params.value("sid");
	req.baseRequest.skey = this->params.value("skey");
	req.baseRequest.uin = this->params.value("uin");

	req.syncKey.count = this->syncList.list.length();
	req.syncKey.list = this->syncList.list;

	req.rr = Utils::time_negate();

	QJsonDocument params = WechatProtocol::makeup_cgi_bin_mmwebwx_bin_webwxsync(req);
	//Request request("sync", Global::getInstance()->getWechatHeaders());
	this->request->setHeaders(Global::getInstance()->getWechatMsgHeaders());

	try{
		Request::Response response = this->request->post(url, params.toJson(QJsonDocument::Compact));
		if(response.error != QNetworkReply::NoError){
			throw response;
		}
		WechatProtocol::Response_webwxsync res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxsync(response.content);
		if(res.baseResponse.ret == "-1"){
			throw QString("data resolve failed.");
		}
		if(res.baseResponse.ret == "0"){
			this->syncList = res.syncKey;
			this->params["sync_key_str"] = Utils::syncKeyStrBuilder(this->syncList);
			return res;
		}else{
			throw QString("response retcode abnormal.");
		}
	}catch(Request::Response res){
		qDebug() << "[ERROR]: " << FuncName << ": Response error:" << res.errorContent;
	}catch(QString str){
		qDebug() << "[ERROR]: " << FuncName << ": String error:" << str;
	}
	return WechatProtocol::Response_webwxsync{
		WechatProtocol::BaseResponse{"-1",""},
		"", QList<WechatProtocol::AddMsg>(),
				"", QList<WechatProtocol::ModContact>(),
				"", QList<WechatProtocol::DelContact>(),
				"", QList<WechatProtocol::ModChatRoomMember>(),
				WechatProtocol::Profile{},
		"",
		WechatProtocol::SyncKey{},
		"",
		WechatProtocol::SyncKey{}
	};
}

void Bot::handleMsg(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	WechatProtocol::Response_webwxsync data = this->syncMessage();
	if(data.baseResponse.ret == "-1"){
		return;
	}
	for(WechatProtocol::AddMsg msg: data.addMsgList){
		Message message;
		message.fromUserName = msg.fromUserName;
		message.toUserName = msg.toUserName;
		message.content = msg.content;
		message.messageId = msg.msgId;
		messageProcessing(message);
	}
}

bool Bot::sendMsg(Message msg){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	QString url = Global::getInstance()->getWechatSendMsgUrl(this->params.value("base_uri"));
	QString msgId = Utils::now() + "0" + Utils::repeat(Utils::rand, 3);
	WechatProtocol::Request_webwxsendmsg message;
	message.baseRequest.deviceId = this->params.value("device_id");
	message.baseRequest.sid = this->params.value("sid");
	message.baseRequest.skey = this->params.value("skey");
	message.baseRequest.uin = this->params.value("uin");
	message.msg.type = "1";
	message.msg.content = msg.content;
	message.msg.fromUserName = msg.fromUserName;
	message.msg.toUserName = msg.toUserName;
	message.msg.localId = msg.messageId.isEmpty() ? msgId : msg.messageId;
	message.msg.clientMsgId = msg.messageId.isEmpty() ? msgId : msg.messageId;
	message.scene = "0";
	int maxFailedTimes = 5;
	//Request request("sendMsg", Global::getInstance()->getWechatMsgHeaders());
	this->request->setHeaders(Global::getInstance()->getWechatHeaders());
	for(int i = 0; i < maxFailedTimes; i++){
		try{
			Request::Response res = this->request->post(url, WechatProtocol::makeup_cgi_bin_mmwebwx_bin_webwxsendmsg(message).toJson(QJsonDocument::Compact));
			if(res.error != QNetworkReply::NoError){
				throw res;
			}
			if(res.statusCode != 200){
				throw QString("Server returns abnormal status code: %1").arg(res.statusCode);
			}
			return true;
		}catch(Request::Response res){
			qDebug() << "[WARNI]:" << FuncName << "Response error:" << res.errorContent;
			continue;
		}catch(QString str){
			qDebug() << "[WARNI]:" << FuncName << "String error:" << str;
			continue;
		}
	}
	qDebug() << "[ERROR]:" << FuncName << "Message send failed after" << maxFailedTimes << "times tried.";
	return false;
}

bool Bot::getContact(){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	QString url = Global::getInstance()->getWechatGetContactUrl(this->params.value("base_uri"), Utils::now(), "0", this->params.value("skey"), this->params.value("pass_ticket"));
	try{
		//Request request("getContact", Global::getInstance()->getWechatHeaders());
		this->request->setHeaders(Global::getInstance()->getWechatMsgHeaders());
		Request::Response response = this->request->get(url);
		if(response.error != QNetworkReply::NoError){
			throw response;
		}
		WechatProtocol::Response_webwxgetcontact res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxgetcontact(response.content);
		if(res.baseResponse.ret == "-1"){
			throw QString("data resolve failed.");
		}
		if(res.baseResponse.ret != "0"){
			throw QString("base response reply retcode: %1, msg: %2").arg(res.baseResponse.ret).arg(res.baseResponse.errMsg);
		}
		for(WechatProtocol::Contact mem: res.memberList){
			Contact c;
			c.userName = mem.userName;
			c.nickName = mem.nickName;
			c.remarkName = mem.remarkName;
			c.displayName = mem.displayName;
			c.uin = mem.uin;
			qDebug() << "[INFOR]:" << FuncName << ": UserName:" << c.userName << "Uin" << c.uin << "NickName:" << c.nickName << "RemarkName:" << c.remarkName << "DisplayName:" << c.displayName;
			this->updateNameList(c);
		}
		return true;
	}catch(Request::Response res){
		qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
	}catch(QString str){
		qDebug() << "[ERROR]:" << FuncName << ": String error:" << str;
	}
	return false;
}

bool Bot::getBatchContact(QStringList usernames){
	qDebug() << "[INFOR]:" << "====================" << FuncName << "====================";
	QString url = Global::getInstance()->getWechatGetBatchContactUrl(this->params.value("base_uri"), Utils::now(), this->params.value("pass_ticket"));
	WechatProtocol::Request_webwxbatchgetcontact batchContact;
	batchContact.baseRequest.deviceId = this->params.value("device_id");
	batchContact.baseRequest.sid = this->params.value("sid");
	batchContact.baseRequest.skey = this->params.value("skey");
	batchContact.baseRequest.uin = this->params.value("uin");
	for(QString username: usernames){
		WechatProtocol::BatchContact_Node node;
		node.userName = username;
		node.chatRoomId = "";
		batchContact.list.append(node);
	}
	batchContact.count = usernames.count();
	QJsonDocument req = WechatProtocol::makeup_cgi_bin_mmwebwx_bin_webwxbatchgetcontact(batchContact);
	try{
		//Request request("getBatchContact", Global::getInstance()->getWechatHeaders());
		this->request->setHeaders(Global::getInstance()->getWechatHeaders());
		Request::Response response = this->request->post(url, req.toJson(QJsonDocument::Compact));
		if(response.error != QNetworkReply::NoError){
			throw response;
		}
		//qDebug() << "[INFOR]:" << FuncName << ": Response:" << response.content;
		WechatProtocol::Response_webwxbatchgetcontact res = WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxbatchgetcontact(response.content);
		if(res.baseResponse.ret == "-1"){
			throw QString("data resolve failed.");
		}
		if(res.baseResponse.ret != "0"){
			throw QString("base response ret isnot 0, infor:%1").arg(res.baseResponse.errMsg);
		}
		for(WechatProtocol::Contact mem: res.contactList){
			Contact c;
			c.userName = mem.userName;
			c.nickName = mem.nickName;
			c.remarkName = mem.remarkName;
			c.displayName = mem.displayName;
			c.uin = mem.uin;
			qDebug() << "[INFOR]:" << FuncName << ": GroupName:" << c.userName << "Uin" << c.uin << "NickName:" << c.nickName << "RemarkName:" << c.remarkName << "DisplayName:" << c.displayName;
			this->updateNameList(c);
		}
		return true;
	}catch(Request::Response res){
		qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
	}catch(QString str){
		qDebug() << "[ERROR]:" << FuncName << ": String error:" << str;
	}
	return false;
}
