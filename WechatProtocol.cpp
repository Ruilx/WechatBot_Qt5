#include "WechatProtocol.h"
#include "Global.h"

WechatProtocol::Member WechatProtocol::resolve_member_json(const QJsonObject &member){
	Member m;
	for(QString key: member.keys()){
		QJsonValue value = member.value(key);
		if(key == "Uin"){
			m.uin = QString::number(value.toInt());
		}else if(key == "UserName"){
			m.userName = value.toString();
		}else if(key == "NickName"){
			m.nickName = value.toString();
		}else if(key == "AttrStatus"){
			m.attrStatus = QString::number(value.toInt());
		}else if(key == "PYInitial"){
			m.pyInitial = value.toString();
		}else if(key == "PYQuanPin"){
			m.pyQuanPin = value.toString();
		}else if(key == "RemarkPYInitial"){
			m.remarkPyInitial = value.toString();
		}else if(key == "RemarkPYQuanPin"){
			m.remarkPyQuanPin = value.toString();
		}else if(key == "MemberStatus"){
			m.memberStatus = QString::number(value.toInt());
		}else if(key == "DisplayName"){
			m.displayName = value.toString();
		}else if(key == "KeyWord"){
			m.keyWord = value.toString();
		}
	}
	return m;
}

WechatProtocol::Contact WechatProtocol::resolve_contact_json(const QJsonObject &contact){
	Contact c;
	for(QString key: contact.keys()){
		QJsonValue value = contact.value(key);
		if(key == "Uin"){
			c.uin = QString::number(value.toInt());
		}else if(key == "UserName"){
			c.userName = value.toString();
		}else if(key == "NickName"){
			c.nickName = value.toString();
		}else if(key == "HeadImgUrl"){
			c.headImgUrl = value.toString();
		}else if(key == "ContactFlag"){
			c.contactFlag = QString::number(value.toInt());
		}else if(key == "MemberCount"){
			c.memberCount = QString::number(value.toInt());
		}else if(key == "MemberList"){
			if(value.isArray()){
				QJsonArray memberList = value.toArray();
				for(QJsonValue value: memberList){
					QJsonObject member = value.toObject();
					c.memberList.append(WechatProtocol::resolve_member_json(member));
				}
			}
		}else if(key == "RemarkName"){
			c.remarkName = value.toString();
		}else if(key == "HideInputBarFlag"){
			c.hideInputBarFlag = QString::number(value.toInt());
		}else if(key == "Sex"){
			c.sex = QString::number(value.toInt());
		}else if(key == "Signature"){
			c.signature = value.toString();
		}else if(key == "VerifyFlag"){
			c.verifyFlag = QString::number(value.toInt());
		}else if(key == "OwnerUin"){
			c.ownerUin = QString::number(value.toInt());
		}else if(key == "PYInitial"){
			c.pyInitial = value.toString();
		}else if(key == "PYQuanPin"){
			c.pyQuanPin = value.toString();
		}else if(key == "RemarkPYInitial"){
			c.remarkPyInitial = value.toString();
		}else if(key == "RemarkPYQuanPin"){
			c.remarkPyQuanPin = value.toString();
		}else if(key == "StarFriend"){
			c.starFriend = QString::number(value.toInt());
		}else if(key == "AppAccountFlag"){
			c.appAccountFlag = QString::number(value.toInt());
		}else if(key == "Statues"){
			c.statues = QString::number(value.toInt());
		}else if(key == "AttrStatus"){
			c.attrStatus = QString::number(value.toInt());
		}else if(key == "Province"){
			c.province = value.toString();
		}else if(key == "City"){
			c.city = value.toString();
		}else if(key == "Alias"){
			c.alias = value.toString();
		}else if(key == "SnsFlag"){
			c.snsFlag = QString::number(value.toInt());
		}else if(key == "UniFriend"){
			c.uniFriend = QString::number(value.toInt());
		}else if(key == "DisplayName"){
			c.displayName = value.toString();
		}else if(key == "ChatRoomId"){
			c.chatRoomId = QString::number(value.toInt());
		}else if(key == "KeyWord"){
			c.keyWord = value.toString();
		}else if(key == "EncryChatRoomId"){
			c.encryChatRoomId = value.toString();
		}else if(key == "IsOwner"){
			c.isOwner = QString::number(value.toInt());
		}
	}
	return c;
}

WechatProtocol::SyncKey WechatProtocol::resolve_syncKey_json(const QJsonObject &syncKey){
	SyncKey sk;
	sk.count = QString::number(syncKey.value("Count").toInt());
	QJsonValue list = syncKey.value("List").toArray();
	if(list.isArray()){
		QJsonArray listList = list.toArray();
		for(QJsonValue value: listList){
			QJsonObject syncKey_List = value.toObject();
			SyncKey_Node s;
			for(QString key: syncKey_List.keys()){
				QJsonValue value = syncKey_List.value(key);
				if(key == "Key"){
					s.key = QString::number(value.toInt());
				}else if(key == "Val"){
					s.val = QString::number(long(value.toDouble()));
				}
			}
			sk.list.append(s);
		}
	}
	return sk;
}

WechatProtocol::RecommendInfo WechatProtocol::resolve_recommendInfo_json(const QJsonObject &recommendInfo){
	RecommendInfo r;
	for(QString key: recommendInfo.keys()){
		QJsonValue value = recommendInfo.value(key);
		if(key == "UserName"){
			r.userName = value.toString();
		}else if(key == "NickName"){
			r.nickName = value.toString();
		}else if(key == "QQNum"){
			r.qqNum = QString::number(value.toInt());
		}else if(key == "Province"){
			r.province = value.toString();
		}else if(key == "City"){
			r.city = value.toString();
		}else if(key == "Content"){
			r.content = value.toString();
		}else if(key == "Signature"){
			r.signature = value.toString();
		}else if(key == "Alias"){
			r.alias = value.toString();
		}else if(key == "Scene"){
			r.scene = QString::number(value.toInt());
		}else if(key == "VerifyFlag"){
			r.verifyFlag = QString::number(value.toInt());
		}else if(key == "AttrStatus"){
			r.attrStatus = QString::number(value.toInt());
		}else if(key == "Sex"){
			r.sex = QString::number(value.toInt());
		}else if(key == "Ticket"){
			r.ticket = value.toString();
		}else if(key == "OpCode"){
			r.opCode = QString::number(value.toInt());
		}
	}
	return r;
}

WechatProtocol::AppInfo WechatProtocol::resolve_appInfo_json(const QJsonObject &appInfo){
	AppInfo a;
	for(QString key: appInfo.keys()){
		QJsonValue value = appInfo.value(key);
		if(key == "AppID"){
			a.appId = value.toString();
		}else if(key == "Type"){
			a.type = QString::number(value.toInt());
		}
	}
	return a;
}

WechatProtocol::AddMsg WechatProtocol::resolve_addMsg_json(const QJsonObject &addMsg){
	AddMsg a;
	for(QString key: addMsg.keys()){
		QJsonValue value = addMsg.value(key);
		if(key == "MsgId"){
			a.msgId = value.toString();
		}else if(key == "FromUserName"){
			a.fromUserName = value.toString();
		}else if(key == "ToUserName"){
			a.toUserName = value.toString();
		}else if(key == "MsgType"){
			a.msgType = QString::number(value.toInt());
		}else if(key == "Content"){
			a.content = value.toString();
		}else if(key == "Status"){
			a.status = QString::number(value.toInt());
		}else if(key == "ImgStatus"){
			a.imgStatus = QString::number(value.toInt());
		}else if(key == "CreateTime"){
			a.createTime = QString::number(long(value.toDouble()));
		}else if(key == "VoiceLength"){
			a.voiceLength = QString::number(value.toInt());
		}else if(key == "PlayLength"){
			a.playLength = QString::number(value.toInt());
		}else if(key == "FileName"){
			a.fileName = value.toString();
		}else if(key == "FileSize"){
			a.fileSize = value.toString();
		}else if(key == "MediaId"){
			a.mediaId = value.toString();
		}else if(key == "Url"){
			a.url = value.toString();
		}else if(key == "AppMsgType"){
			a.appMsgType = QString::number(value.toInt());
		}else if(key == "StatusNotifyCode"){
			a.statusNotifyCode = QString::number(value.toInt());
		}else if(key == "StatusNotifyUserName"){
			a.statusNotifyUserName = value.toString();
		}else if(key == "RecommendInfo"){
			if(value.isObject()){
				a.recommendInfo = WechatProtocol::resolve_recommendInfo_json(value.toObject());
			}
		}else if(key == "ForwardFlag"){
			a.forwardFlag = QString::number(value.toInt());
		}else if(key == "AppInfo"){
			if(value.isObject()){
				a.appInfo = WechatProtocol::resolve_appInfo_json(value.toObject());
			}
		}else if(key == "HasProductId"){
			a.hasProductId = QString::number(value.toInt());
		}else if(key == "Ticket"){
			a.ticket = value.toString();
		}else if(key == "ImgHeight"){
			a.imgHeight = QString::number(value.toInt());
		}else if(key == "ImgWidth"){
			a.imgWidth = QString::number(value.toInt());
		}else if(key == "SubMsgType"){
			a.subMsgType = QString::number(value.toInt());
		}else if(key == "NewMsgId"){
			a.newMsgId = QString::number(long(value.toDouble()));
		}else if(key == "OriContent"){
			a.oriContent = value.toString();
		}
	}
	return a;
}

WechatProtocol::ModContact WechatProtocol::resolve_modContact_json(const QJsonObject &modContact){
	Q_UNUSED(modContact);
	ModContact m;

	return m;
}

WechatProtocol::DelContact WechatProtocol::resolve_delContact_json(const QJsonObject &delContact){
	Q_UNUSED(delContact);
	DelContact d;

	return d;
}

WechatProtocol::ModChatRoomMember WechatProtocol::resolve_modChatRoomMember_json(const QJsonObject &modChatRoomMember){
	Q_UNUSED(modChatRoomMember);
	ModChatRoomMember m;

	return m;
}

WechatProtocol::Profile WechatProtocol::resolve_profile_json(const QJsonObject &profile){
	Profile p;
	for(QString key: profile.keys()){
		QJsonValue value = profile.value(key);
		if(key == "BitFlag"){
			p.bitFlag = QString::number(value.toInt());
		}else if(key == "UserName"){
			if(value.isObject()){
				p.userName.buff = value.toObject().value("Buff").toString();
			}
		}else if(key == "NickName"){
			if(value.isObject()){
				p.nickName.buff = value.toObject().value("Buff").toString();
			}
		}else if(key == "BindUin"){
			p.bindUin = QString::number(value.toInt());
		}else if(key == "BindEmail"){
			if(value.isObject()){
				p.bindEmail.buff = value.toObject().value("Buff").toString();
			}
		}else if(key == "BindMobile"){
			if(value.isObject()){
				p.bindMobile.buff = value.toObject().value("Buff").toString();
			}
		}else if(key == "Status"){
			p.status = QString::number(value.toInt());
		}else if(key == "Sex"){
			p.sex = QString::number(value.toInt());
		}else if(key == "PersonalCard"){
			p.personalCard = QString::number(value.toInt());
		}else if(key == "Alias"){
			p.alias = value.toString();
		}else if(key == "HeadImgUpdateFlag"){
			p.headImgUpdateFlag = QString::number(value.toInt());
		}else if(key == "HeadImgUrl"){
			p.headImgUrl = value.toString();
		}else if(key == "Signature"){
			p.signature = value.toString();
		}
	}
	return p;
}

WechatProtocol::Response_jslogin WechatProtocol::resolve_jslogin(const QByteArray &data){
	/* Wechat jslogin response:
		 * [Success]: window.QRLogin.code = 200; window.QRLogin.uuid = "4bXVC8utqQ==";
		 * [Failure]: window.QRLogin.code = 400; window.QRLogin.error = "";
		 */
	Response_jslogin res;
	QString dataStr = QString::fromUtf8(data);
	QString regex = "window.QRLogin.code = (\\d+); window.QRLogin.(\\S+) = \"(\\S+)\";";
	QStringList dataArr = dataStr.replace(QRegExp(regex), "\\1 \\2 \\3").split(" ");
	if(dataArr.length() < 3){
		qDebug() << "[ERROR]:" << FuncName << ": data:" << data << "illegal.";
		return Response_jslogin{"0", "", ""};
	}
	res.window_QRLogin_code = dataArr.at(0);
	if(dataArr.at(1) == "uuid"){
		res.window_QRLogin_uuid = dataArr.at(2);
	}else if(dataArr.at(1) == "error"){
		res.window_QRLogin_error = dataArr.at(2);
	}else{
		qDebug() << "[DEBUG]:" << FuncName << ": data:" << data << "renamed?";
		return res;
	}
	return res;
}

WechatProtocol::Response_login WechatProtocol::resolve_cgi_bin_mmwebwx_bin_login(const QByteArray &data){
	/* Wechat cgi-bin/mmwebwx-bin/login response:
		 * [Waiting]: window.code=408;
		 * [Scanned]: window.code=201;window.userAvatar = 'data:img/jpg;base64,...'
		 * [Logined]: window.code=200;\nwindow.redirect_uri="https://..."
		 */
	Response_login res;
	qDebug() << "[INFOR]:" << FuncName << "data:" << data.left(60) << "...";
	if(data.startsWith('\x1F')){
		// 遇到扫描二维码返回乱码的问题, data开头是\x1F, 会炸
		qDebug() << "[WARNI]:" << FuncName << "Data startswith \\x1F, don't analysis.";
		return res;
	}
	QByteArray _d(data);
	_d.replace(' ', "");
	_d.replace('\n', "");
	QByteArrayList dataArr = _d.split(';');
	for(int i = 0; i < dataArr.length();){
		if(dataArr.at(i).isEmpty()){
			dataArr.removeAt(i);
		}else{
			if(dataArr.at(i).startsWith("base64")){
				dataArr[i-1].append(';').append(dataArr.at(i));
				dataArr.removeAt(i);
			}else{
				i++;
			}
		}
	}
	for(QByteArray p: dataArr){
		QString pRaw = QString::fromUtf8(p);
		if(pRaw.isEmpty()){
			qDebug() << "[ERROR]:" << FuncName << ": data:" << data.left(100) << "... illegal.";
			return Response_login{"0", "", ""};
		}
		QStringList kvPair = pRaw.split("=", QString::KeepEmptyParts);
		if(kvPair.length() == 1){
			kvPair.append("");
		}
		if(kvPair.at(0) == "window.code"){
			res.window_code = kvPair.at(1);
		}else if(kvPair.at(0) == "window.userAvatar"){
			QByteArray userAvatar = kvPair.at(1).toUtf8();
			res.window_userAvatar = userAvatar.replace('\'', "");
		}else if(kvPair.at(0) == "window.redirect_uri"){
			QString uri = kvPair.at(1);
			for(int i = 2; i < kvPair.length();){
				uri.append("=").append(kvPair.at(i));
				kvPair.removeAt(i);
			}
			uri.remove('"');
			res.window_redirect_uri = uri;
			qDebug() << "[INFOR]:" << FuncName << ": URL:" << uri;
		}else{
			qDebug() << "[WARNI]:" << FuncName << ": data has more params:" << kvPair.at(0) << "=>" << kvPair.at(1);
		}
	}
	return res;
}

WechatProtocol::Response_webwxnewloginpage WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxnewloginpage(const QByteArray &data){
	qDebug() << "[INFOR]:" << FuncName << ": data:" << QString::fromUtf8(data);
	Response_webwxnewloginpage res;
	QDomDocument doc;
	QString errorStr;
	int errorLine = 0, errorCol = 0;

	if(!doc.setContent(data, &errorStr, &errorLine, &errorCol)){
		qDebug() << "[ERROR]:" << FuncName << ": data parse content failed at (" << errorLine << "," << errorCol << ")" << "," << errorStr;
		return Response_webwxnewloginpage{"-1", errorStr, "", "", "", "", ""};
	}
	if(doc.isNull()){
		qDebug() << "[ERROR]:" << FuncName << ": xml is empty.";
		return Response_webwxnewloginpage{"-1", errorStr, "", "", "", "", ""};
	}
	QDomElement root = doc.documentElement();
	if(root.tagName() != "error"){
		qDebug() << "[ERROR]:" << FuncName << ": xml is invaild. root.name =" << root.tagName() << " != 'error'.";
		return Response_webwxnewloginpage{"-1", errorStr, "", "", "", "", ""};
	}
	QDomNodeList list = root.childNodes();
	for(int i = 0; i < list.length(); i++){
		QDomNode tag = list.at(i);
		QDomElement element = tag.toElement();
		QDomNode dom = element.childNodes().at(0);
		if(dom.isText()){
			QString title = element.tagName();
			QString value = dom.toText().data();
			if(title == "ret"){
				res.ret = value;
			}else if(title == "message"){
				res.message = value;
			}else if(title == "skey"){
				res.skey = value;
			}else if(title == "wxsid"){
				res.wxsid = value;
			}else if(title == "wxuin"){
				res.wxuin = value;
			}else if(title == "pass_ticket"){
				res.pass_ticket = value;
			}else if(title == "isgrayscale"){
				res.isgrayscale = value;
			}
		}
	}
	return res;
}

WechatProtocol::Response_webwxinit WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxinit(const QByteArray &data){
	Response_webwxinit res{
		BaseResponse{"-1", ""},
		"0",
		QList<Contact>(),
		SyncKey{"0", QList<SyncKey_Node>()},
		User{},
		"", "", "", "", "", "", "", QList<MPSubscribeMsg>(), ""
	};
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if(error.error != QJsonParseError::NoError){
		qDebug() << "[ERROR]:" << FuncName << ": Json data is not valid. data:" << data;
		return res;
	}
	if(doc.isArray()){
		qDebug() << "[ERROR]:" << FuncName << ": Json root expected object, array touched. data:" << data;
		return res;
	}
	QJsonObject root = doc.object();
	if(root.isEmpty()){
		qDebug() << "[ERROR]:" << FuncName << ": Json object empty. data:" << data;
		return res;
	}
	for(QString key: root.keys()){
		QJsonValue value = root.value(key);
		if(key == "BaseResponse"){
			if(value.isObject()){
				QJsonObject baseResponse = value.toObject();
				res.baseResponse.ret = QString::number(baseResponse.value("Ret").toInt(-1));
				res.baseResponse.errMsg = baseResponse.value("ErrMsg").toString();
			}
		}else if(key == "Count"){
			res.count = QString::number(value.toInt());
		}else if(key == "ContactList"){
			if(value.isArray()){
				QJsonArray contactList = value.toArray();
				for(QJsonValue value: contactList){
					QJsonObject contact = value.toObject();
					res.ContactList.append(WechatProtocol::resolve_contact_json(contact));
				}
			}
		}else if(key == "SyncKey"){
			if(value.isObject()){
				QJsonObject syncKey = value.toObject();
				res.syncKey = WechatProtocol::resolve_syncKey_json(syncKey);
			}
		}else if(key == "User"){
			if(value.isObject()){
				QJsonObject user = value.toObject();
				for(QString key: user.keys()){
					QJsonValue value = user.value(key);
					if(key == "Uin"){
						res.user.uin = QString::number(value.toInt());
					}else if(key == "UserName"){
						res.user.userName = value.toString();
					}else if(key == "NickName"){
						res.user.nickName = value.toString();
					}else if(key == "HeadImgUrl"){
						res.user.headImgUrl = value.toString();
					}else if(key == "RemarkName"){
						res.user.remarkName = value.toString();
					}else if(key == "PYInitial"){
						res.user.pyInitial = value.toString();
					}else if(key == "PYQuanPin"){
						res.user.pyQuanPin = value.toString();
					}else if(key == "RemarkPYInitial"){
						res.user.remarkPyInitial = value.toString();
					}else if(key == "RemarkPYQuanPin"){
						res.user.remarkPyQuanPin = value.toString();
					}else if(key == "HideInputBarFlag"){
						res.user.hideInputBarFlag = QString::number(value.toInt());
					}else if(key == "StarFriend"){
						res.user.starFriend = QString::number(value.toInt());
					}else if(key == "Sex"){
						res.user.sex = QString::number(value.toInt());
					}else if(key == "Signature"){
						res.user.signature = value.toString();
					}else if(key == "AppAccountFlag"){
						res.user.appAccountFlag = QString::number(value.toInt());
					}else if(key == "VerifyFlag"){
						res.user.verifyFlag = QString::number(value.toInt());
					}else if(key == "ContactFlag"){
						res.user.contactFlag = QString::number(value.toInt());
					}else if(key == "WebWxPluginSwitch"){
						res.user.webWxPluginSwitch = QString::number(value.toInt());
					}else if(key == "HeadImgFlag"){
						res.user.headImgFlag = QString::number(value.toInt());
					}else if(key == "SnsFlag"){
						res.user.snsFlag = QString::number(value.toInt());
					}
				}
			}
		}else if(key == "ChatSet"){
			res.chatSet = value.toString();
		}else if(key == "SKey"){
			res.sKey = value.toString();
		}else if(key == "ClientVersion"){
			res.clientVersion = QString::number(value.toInt());
		}else if(key == "SystemTime"){
			res.systemTime = QString::number(long(value.toDouble()));
		}else if(key == "GrayScale"){
			res.grayScale = QString::number(value.toInt());
		}else if(key == "InviteStartCount"){
			res.inviteStartCount = QString::number(value.toInt());
		}else if(key == "MPSubscribeMsgCount"){
			res.mpSubscribeMsgCount = QString::number(value.toInt());
		}else if(key == "MPSubscribeMsgList"){
			if(value.isArray()){
				QJsonArray mpSubscribeMsgList = value.toArray();
				for(QJsonValue value: mpSubscribeMsgList){
					QJsonObject mpSubscribeMsg = value.toObject();
					MPSubscribeMsg m;
					for(QString key: mpSubscribeMsg.keys()){
						QJsonValue value = mpSubscribeMsg.value(key);
						if(key == "UserName"){
							m.userName = value.toString();
						}else if(key == "MPArticleCount"){
							m.mpArticleCount = QString::number(value.toInt());
						}else if(key == "MPArticleList"){
							if(value.isArray()){
								QJsonArray mpArticleList = value.toArray();
								for(QJsonValue value: mpArticleList){
									QJsonObject mpArticle = value.toObject();
									MPArticle a;
									for(QString key: mpArticle.keys()){
										QJsonValue value = mpArticle.value(key);
										if(key == "Title"){
											a.title = value.toString();
										}else if(key == "Digest"){
											a.digest = value.toString();
										}else if(key == "Cover"){
											a.cover = value.toString();
										}else if(key == "Url"){
											a.url = value.toString();
										}
									}
									m.mpArticleList.append(a);
								}
							}
						}else if(key == "Time"){
							m.time = QString::number(long(value.toDouble()));
						}else if(key == "NickName"){
							m.nickName = value.toString();
						}
					}
					res.mpSubscribeMsgList.append(m);
				}
			}
		}else if(key == "ClickReportInterval"){
			res.clickReportInterval = QString::number(value.toInt());
		}
	}
	return res;
}

WechatProtocol::Response_webwxstatusnotify WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxstatusnotify(const QByteArray &data){
	Response_webwxstatusnotify res{BaseResponse{"-1", ""}, ""};
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if(error.error != QJsonParseError::NoError){
		qDebug() << "[ERROR]:" << FuncName << ": Json data is not valid. data:" << data;
		return res;
	}
	if(doc.isArray()){
		qDebug() << "[ERROR]:" << FuncName << ": Json root expected object, array touched. data:" << data;
		return res;
	}
	QJsonObject root = doc.object();
	if(root.isEmpty()){
		qDebug() << "[ERROR]:" << FuncName << ": Json object empty. data:" << data;
		return res;
	}
	for(QString key: root.keys()){
		QJsonValue value = root.value(key);
		if(key == "BaseResponse"){
			if(value.isObject()){
				QJsonObject baseResponse = value.toObject();
				res.baseResponse.ret = QString::number(baseResponse.value("Ret").toInt(-1));
				res.baseResponse.errMsg = baseResponse.value("ErrMsg").toString();
			}
		}else if(key == "MsgID"){
			res.msgId = value.toString();
		}
	}
	return res;
}

WechatProtocol::Response_webwxgetcontact WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxgetcontact(const QByteArray &data){
	Response_webwxgetcontact res{
		BaseResponse{"-1", ""},
		"",
		QList<Contact>(),
		""
	};
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if(error.error != QJsonParseError::NoError){
		qDebug() << "[ERROR]:" << FuncName << ": Json data is not valid. data:" << data;
		return res;
	}
	if(doc.isArray()){
		qDebug() << "[ERROR]:" << FuncName << ": Json root expected object, array touched. data:" << data;
		return res;
	}
	QJsonObject root = doc.object();
	if(root.isEmpty()){
		qDebug() << "[ERROR]:" << FuncName << ": Json object empty. data:" << data;
		return res;
	}
	for(QString key: root.keys()){
		QJsonValue value = root.value(key);
		if(key == "BaseResponse"){
			if(value.isObject()){
				QJsonObject baseResponse = value.toObject();
				res.baseResponse.ret = QString::number(baseResponse.value("Ret").toInt());
				res.baseResponse.errMsg = baseResponse.value("ErrMsg").toString();
			}
		}else if(key == "MemberCount"){
			res.memberCount = QString::number(value.toInt());
		}else if(key == "MemberList"){
			if(value.isArray()){
				QJsonArray memberList = value.toArray();
				for(QJsonValue value: memberList){
					QJsonObject member = value.toObject();
					res.memberList.append(WechatProtocol::resolve_contact_json(member));
				}
			}
		}else if(key == "Seq"){
			res.seq = QString::number(value.toInt());
		}
	}
	return res;
}

WechatProtocol::Response_webwxbatchgetcontact WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxbatchgetcontact(const QByteArray &data){
	Response_webwxbatchgetcontact res{
		BaseResponse{"-1", ""},
		"",
		QList<Contact>()
	};
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if(error.error != QJsonParseError::NoError){
		qDebug() << "[ERROR]:" << FuncName << ": Json data is not vaild. data:" << data;
		return res;
	}
	if(doc.isArray()){
		qDebug() << "[ERROR]:" << FuncName << ": Json root expected object, array touched. data:" << data;
		return res;
	}
	QJsonObject root = doc.object();
	if(root.isEmpty()){
		qDebug() << "[ERROR]:" << FuncName << ": Json object empty. data:" << data;
		return res;
	}
	for(QString key: root.keys()){
		QJsonValue value = root.value(key);
		if(key == "BaseResponse"){
			if(value.isObject()){
				QJsonObject baseResponse = value.toObject();
				res.baseResponse.ret = QString::number(baseResponse.value("Ret").toInt());
				res.baseResponse.errMsg = baseResponse.value("ErrMsg").toString();
			}
		}else if(key == "Count"){
			res.count = QString::number(value.toInt());
		}else if(key == "ContactList"){
			if(value.isArray()){
				QJsonArray contactList = value.toArray();
				for(QJsonValue value: contactList){
					QJsonObject contact = value.toObject();
					res.contactList.append(WechatProtocol::resolve_contact_json(contact));
				}
			}
		}
	}
	return res;
}

WechatProtocol::Response_synccheck WechatProtocol::resolve_cgi_bin_mmwebwx_bin_synccheck(const QByteArray &data){
	/* [SUCCESS]: window.synccheck={retcode:"xxx", selector:"xxx"}
	 * [FAILURE]: window.synccheck={retcode:"1100", selector:"0"}
	 * [EXIT ED]: window.synccheck={retcode:"1101", selector:"0"}
	 * [FAILURE]: window.synccheck={retcode:"1102", selector:"0"}
	 * [SYS ERR]: window.synccheck={retcode:"-1", selector:"-1"}
	 */
	Response_synccheck res;
	res.retcode = "-1";
	res.selector = "-1";
	QByteArray _d(data);
	_d.replace(' ', "");
	_d.replace('\n', "");
	QByteArrayList dataArr = _d.split(';');
	for(int i = 0; i < dataArr.length();){
		if(dataArr.at(i).isEmpty()){
			dataArr.takeAt(i);
		}else{
			i++;
		}
	}
	for(QByteArray p: dataArr){
		QString pRaw = QString::fromUtf8(p);
		if(pRaw.isEmpty()){
			qDebug() << "[ERROR]:" << FuncName << ": data:" << data.left(100) << "illegal.";
			return Response_synccheck{"-1", "-1"};
		}
		QStringList kvPair = pRaw.split("=", QString::SkipEmptyParts);
		if(kvPair.length() == 1){
			kvPair.append("");
		}
		//qDebug() << "[INFOR]:" << FuncName << "kvPair[0]=" << kvPair.at(0) << "kvPair[1]=" << kvPair.at(1);
		if(kvPair.at(0) == "window.synccheck"){
			// Json key must be surround with quote.
//			QJsonParseError error;
//			QJsonDocument doc = QJsonDocument::fromJson(kvPair.at(1).toUtf8(), &error);
//			if(error.error != QJsonParseError::NoError){
//				qDebug() << "[ERROR]:" << FuncName << ": Json data is not valid. data:" << kvPair.at(1);
//				return res;
//			}
//			if(doc.isArray()){
//				qDebug() << "[ERROR]:" << FuncName << ": Json root excepted object, array touched. data:" << data;
//				return res;
//			}
//			QJsonObject root = doc.object();
//			if(root.isEmpty()){
//				qDebug() << "[ERROR]:" << FuncName << ": Json object empty. data:" << data;
//				return res;
//			}
//			for(QString key: root.keys()){
//				QJsonValue value = root.value(key);
//				if(key == "retcode"){
//					res.retcode = QString::number(value.toInt());
//				}else if(key == "selector"){
//					res.selector = QString::number(value.toInt());
//				}
//			}
			// Use Regexp.
			QRegExp regexp("\\{retcode:\\\"(\\d+)\\\",selector:\\\"(\\d+)\\\"\\}");
			QString afterTrans = QString(kvPair.at(1)).replace(regexp, "\\1 \\2");
			//qDebug() << "[DEBUG]:" << FuncName << "afterTrans:" << afterTrans;
			QStringList params = afterTrans.split(" ", QString::KeepEmptyParts);
			qDebug() << "[DEBUG]:" << FuncName << "params:" << params;
			if(params.length() >= 2){
				res.retcode = params.at(0);
				res.selector = params.at(1);
			}else{
				qDebug() << "[ERROR]:" << FuncName << ": regexp splits the string into less than 2 parts.";
				// 默认地, res中的值已被设置成-1.
			}
		}
	}
	return res;
}

WechatProtocol::Response_webwxsync WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxsync(const QByteArray &data){
	Response_webwxsync res{
		BaseResponse{"-1",""},
		"", QList<AddMsg>(),
				"", QList<ModContact>(),
				"", QList<DelContact>(),
				"", QList<ModChatRoomMember>(),
				Profile{},
		"",
		SyncKey{},
		"",
		SyncKey{}
	};
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if(error.error != QJsonParseError::NoError){
		qDebug() << "[ERROR]:" << FuncName << ": Json data is not vaild. data:" << data;
		return res;
	}
	if(!doc.isObject()){
		qDebug() << "[ERROR]:" << FuncName << ": Json root expected object, array touched. data:" << data;
		return res;
	}
	QJsonObject root = doc.object();
	if(root.isEmpty()){
		qDebug() << "[ERROR]:" << FuncName << ": Json object empty. data:" << data;
		return res;
	}
	for(QString key: root.keys()){
		QJsonValue value = root.value(key);
		if(key == "BaseResponse"){
			if(value.isObject()){
				QJsonObject baseResponse = value.toObject();
				res.baseResponse.ret = QString::number(baseResponse.value("Ret").toInt());
				res.baseResponse.errMsg = baseResponse.value("ErrMsg").toString();
			}
		}else if(key == "AddMsgCount"){
			res.addMsgCount = QString::number(value.toInt());
		}else if(key == "AddMsgList"){
			if(value.isArray()){
				QJsonArray addMsgList = value.toArray();
				for(QJsonValue value: addMsgList){
					QJsonObject addMsg = value.toObject();
					res.addMsgList.append(WechatProtocol::resolve_addMsg_json(addMsg));
				}
			}
		}else if(key == "ModContactCount"){
			res.modContactCount = value.toString();
		}else if(key == "ModContactList"){
			if(value.isArray()){
				QJsonArray modContactList = value.toArray();
				for(QJsonValue value: modContactList){
					QJsonObject modContact = value.toObject();
					res.modContactList.append(WechatProtocol::resolve_modContact_json(modContact));
				}
			}
		}else if(key == "DelContactCount"){
			res.delContactCount = value.toString();
		}else if(key == "DelContactList"){
			if(value.isArray()){
				QJsonArray delContactList = value.toArray();
				for(QJsonValue value: delContactList){
					QJsonObject delContact = value.toObject();
					res.delContactList.append(WechatProtocol::resolve_delContact_json(delContact));
				}
			}
		}else if(key == "ModChatRoomMemberCount"){
			res.modChatRoomMemberCount = value.toString();
		}else if(key == "ModChatRoomMemberList"){
			if(value.isArray()){
				QJsonArray modChatRoomMemberList = value.toArray();
				for(QJsonValue value: modChatRoomMemberList){
					QJsonObject modChatRoomMember = value.toObject();
					res.modChatRoomMemberList.append(WechatProtocol::resolve_modChatRoomMember_json(modChatRoomMember));
				}
			}
		}else if(key == "Profile"){
			if(value.isObject()){
				res.profile = WechatProtocol::resolve_profile_json(value.toObject());
			}
		}else if(key == "ContinueFlag"){
			res.continueFlag = QString::number(value.toInt());
		}else if(key == "SyncKey"){
			if(value.isObject()){
				res.syncKey = WechatProtocol::resolve_syncKey_json(value.toObject());
			}
		}else if(key == "SKey"){
			res.sKey = value.toString();
		}else if(key == "SyncCheckKey"){
			if(value.isObject()){
				res.syncCheckKey = WechatProtocol::resolve_syncKey_json(value.toObject());
			}
		}
	}
	return res;
}

WechatProtocol::Response_webwxpushloginurl WechatProtocol::resolve_cgi_bin_mmwebwx_bin_webwxpushloginurl(const QByteArray &data){
	Response_webwxpushloginurl res{
		"-1", "", ""
	};
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if(error.error != QJsonParseError::NoError){
		qDebug() << "[ERROR]:" << FuncName << ": Json data is not vaild. data:" << data;
		return res;
	}
	if(!doc.isObject()){
		qDebug() << "[ERROR]:" << FuncName << ": Json root expected object, array touched. data:" << data;
		return res;
	}
	QJsonObject root = doc.object();
	if(root.isEmpty()){
		qDebug() << "[ERROR]:" << FuncName << ": Json object empty. data:" << data;
		return res;
	}
	for(QString key: root.keys()){
		QJsonValue value = root.value(key);
		if(key == "ret"){
			res.ret = value.toString();
		}else if(key == "msg"){
			res.msg = value.toString();
		}else if(key == "uuid"){
			res.uuid = value.toString();
		}
	}
	return res;
}

QJsonDocument WechatProtocol::makeup_cgi_bin_mmwebwx_bin_webwxsync(WechatProtocol::Request_webwxsync params){
	QJsonObject baseRequest{
		{"DeviceID", params.baseRequest.deviceId},
		{"Sid", params.baseRequest.sid},
		{"Skey", params.baseRequest.skey},
		{"Uin", params.baseRequest.uin}
	};
	QJsonArray syncKeyList;
	for(SyncKey_Node n: params.syncKey.list){
		QJsonObject _obj{
			{"Key", n.key},
			{"Val", n.val}
		};
		syncKeyList.append(_obj);
	}
	QJsonObject syncKey{
		{"Count", syncKeyList.count()},
		{"List", syncKeyList}
	};
	QJsonObject request{
		{"BaseRequest", baseRequest},
		{"SyncKey", syncKey},
		{"rr", params.rr}
	};
	return QJsonDocument(request);
}

QJsonDocument WechatProtocol::makeup_cgi_bin_mmwebwx_bin_webwxsendmsg(WechatProtocol::Request_webwxsendmsg params){
	QJsonObject baseRequest{
		{"DeviceID", params.baseRequest.deviceId},
		{"Sid", params.baseRequest.sid},
		{"Skey", params.baseRequest.skey},
		{"Uin", params.baseRequest.uin}
	};
	QJsonObject msg{
		{"Type", params.msg.type},
		{"Content", params.msg.content},
		{"FromUserName", params.msg.fromUserName},
		{"ToUserName", params.msg.toUserName},
		{"LocalID", params.msg.localId},
		{"ClientMsgId", params.msg.clientMsgId}
	};
	QJsonObject request{
		{"BaseRequest", baseRequest},
		{"Msg", msg},
		{"Scene", params.scene}
	};
	return QJsonDocument(request);
}

QJsonDocument WechatProtocol::makeup_cgi_bin_mmwebwx_bin_webwxbatchgetcontact(WechatProtocol::Request_webwxbatchgetcontact params){
	QJsonObject baseRequest{
		{"DeviceID", params.baseRequest.deviceId},
		{"Sid", params.baseRequest.sid},
		{"Skey", params.baseRequest.skey},
		{"Uin", params.baseRequest.uin}
	};
	QJsonArray list;
	for(BatchContact_Node node: params.list){
		QJsonObject _obj{
			{"UserName", node.userName},
			{"ChatRoomId", node.chatRoomId}
		};
		list.append(_obj);
	}
	QJsonObject request{
		{"BaseRequest", baseRequest},
		{"Count", list.count()},
		{"List", list}
	};
	return QJsonDocument(request);
}
