#ifndef BAIZEPROTOCOL_H
#define BAIZEPROTOCOL_H

#include <QtCore>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

class BaizeProtocol
{
public:
	typedef struct{
		QString ret;
		QString errMsg;
	} BaseResponse;

	typedef struct{
		QString from;
		QString key;
	} BaseRequest;

	typedef struct{
		QString fromUser;
		QString toUser;
		QString content;
		QString type;
		QString msgId;
	} Message;

	typedef struct{
		QString userName;
		QString nickName;
		QString remarkname;
		QString displayName;
	} Contact;

	typedef struct{
		BaseRequest baseRequest;
		Message message;
	} Request_message;

	typedef struct{
		BaseRequest baseRequest;
		QList<Contact> contact;
	} Request_contact;

	typedef struct{
		BaseResponse baseResponse;
		Message message;
	} Response_message;

	typedef struct{
		BaseResponse baseResponse;
	} Response_contact;
public:
	explicit BaizeProtocol();

	static Response_message reslove_message_json(const QByteArray &message);

	static Response_contact resolve_contact_json(const QByteArray &contact);

public:
	static QJsonDocument makeup_message(Request_message params);

	static QJsonDocument markup_contact(Request_contact params);

signals:

public slots:
};

#endif // BAIZEPROTOCOL_H
