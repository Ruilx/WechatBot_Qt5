#include "BaizeProtocol.h"
#include "Global.h"

BaizeProtocol::Response_message BaizeProtocol::reslove_message_json(const QByteArray &data){
	Response_message res{
		BaseResponse{"-1", ""},
		Message{"", "", "", "", ""}
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
				res.baseResponse.ret = baseResponse.value("Ret").toString();
				res.baseResponse.errMsg = baseResponse.value("ErrMsg").toString();
			}
		}else if(key == "Message"){
			if(value.isObject()){
				QJsonObject msg = value.toObject();
				res.message.content = msg.value("Content").toString();
				res.message.fromUser = msg.value("FromUser").toString();
				res.message.msgId = msg.value("MsgId").toString();
				res.message.toUser = msg.value("ToUser").toString();
				res.message.type = msg.value("Type").toString();
			}
		}
	}
	return res;
}

BaizeProtocol::Response_contact BaizeProtocol::resolve_contact_json(const QByteArray &data){
	Response_contact res{
		BaseResponse{"-1", ""}
	};
	QJsonParseError error;
	QJsonDocument doc = QJsonDocument::fromJson(data, &error);
	if(error.error != QJsonParseError::NoError){
		qDebug() << "[ERROR]:" << FuncName << ": Json data is not vaild. data:" << data;
		return res;
	}
	if(!doc.isObject()){
		qDebug() << "[ERROR]:" << FuncName << ": Json object expected object. data" << data;
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
				res.baseResponse.ret = baseResponse.value("Ret").toString();
				res.baseResponse.errMsg = baseResponse.value("ErrMsg").toString();
			}
		}
	}
	return res;
}

QJsonDocument BaizeProtocol::makeup_message(BaizeProtocol::Request_message params){
	QJsonObject baseRequest{
		{"From", params.baseRequest.from},
		{"Key", params.baseRequest.key}
	};
	QJsonObject message{
		{"FromUser", params.message.fromUser},
		{"ToUser", params.message.toUser},
		{"MsgId", params.message.msgId},
		{"Content", params.message.content},
		{"Type", params.message.type}
	};
	QJsonObject request{
		{"BaseRequest", baseRequest},
		{"Message", message}
	};
	return QJsonDocument(request);
}

QJsonDocument BaizeProtocol::markup_contact(BaizeProtocol::Request_contact params){
	QJsonObject baseRequest{
		{"From", params.baseRequest.from},
		{"Key", params.baseRequest.key}
	};
	QJsonArray list;
	for(Contact node: params.contact){
		QJsonObject _obj{
			{"DisplayName", node.displayName},
			{"NickName", node.nickName},
			{"RemarkName", node.remarkname},
			{"UserName", node.userName}
		};
		list.append(_obj);
	}
	QJsonObject request{
		{"BaseRequest", baseRequest},
		{"List", list}
	};
	return QJsonDocument(request);
}
