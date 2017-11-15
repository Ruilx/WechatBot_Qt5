#ifndef MESSAGEQUERY_H
#define MESSAGEQUERY_H

#include <QObject>
#include "Request.h"
#include "BaizeProtocol.h"
#include "Bot.h"

class MessageQuery : public QObject
{
	Q_OBJECT

	Request *request = new Request(this);
public:
	explicit MessageQuery(QObject *parent = 0): QObject(parent){

	}



signals:
	void replyMessage(Message message);
public slots:
	void start(){
		qDebug() << "[INFOR]:" << FuncName << ": MessageQuery started.";
	}

	/**
	 * @brief sendQuery 向申请服务器查询内容
	 * @param message
	 */
	void sendQuery(Message message){
		QString url = Global::getInstance()->getBaizeMessageHandleUrl();
		this->request->setHeaders(Global::getInstance()->getBaizeHeaders());
		BaizeProtocol::Request_message msg;
		{
			msg.baseRequest.from = From;
			msg.baseRequest.key = SecretKey;
			msg.message.fromUser = message.fromUserName;
			msg.message.toUser = message.toUserName;
			msg.message.content = message.content;
			msg.message.type = "1";
			msg.message.msgId = message.messageId;
		}
		//QHash<QString, QString> params;
		//params.insert("json", QString::fromUtf8(BaizeProtocol::makeup_message(msg).toJson(QJsonDocument::Compact)));
		try{
			Request::Response response = request->post(url, BaizeProtocol::makeup_message(msg).toJson(QJsonDocument::Compact));
			if(response.error != QNetworkReply::NoError){
				throw response;
			}
			qDebug() << "[DEBUG]:" << FuncName << ": response content:" << response.content;
			BaizeProtocol::Response_message res = BaizeProtocol::reslove_message_json(response.content);
			if(res.baseResponse.ret == "-1"){
				throw QString("data resolve failed.");
			}
			if(res.baseResponse.ret != 0){
				throw QString("response retcode abnormal.");
			}
			Message replyMessage;
			replyMessage.fromUserName = res.message.fromUser;
			replyMessage.toUserName = res.message.toUser;
			replyMessage.content = res.message.content;
			replyMessage.messageId = res.message.msgId;
			emit this->replyMessage(replyMessage);
			return;
		}catch(Request::Response res){
			qDebug() << "[ERROR]:" << FuncName << ": Response error:" << res.errorContent;
		}catch(QString str){
			qDebug() << "[ERROR]:" << FuncName << ": String error:" << str;
		}
		Message replyErrorMessage;
		replyErrorMessage.fromUserName = msg.message.toUser;
		replyErrorMessage.toUserName = msg.message.fromUser;
		replyErrorMessage.content = "服务器暂时不可用, 请稍后再试.";
		replyErrorMessage.messageId = Utils::time() + Utils::repeat(Utils::rand, 4);
		emit this->replyMessage(replyErrorMessage);
	}

};

#endif // MESSAGEQUERY_H
