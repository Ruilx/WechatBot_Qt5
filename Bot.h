#ifndef BOT_H
#define BOT_H

#include <QtCore>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include "Global.h"
#include "Utils.h"
#include "Request.h"
#include "ShowQrcode.h"
#include "WechatProtocol.h"
#include "Snapshot.h"
#include "ThreadController.h"

class Bot : public QObject
{
	Q_OBJECT

	QHash<QString, QString> params;
	WechatProtocol::SyncKey syncList;
	ShowQrcode *showQrCodeDialog = new ShowQrcode(nullptr);
	QThread *qrThread = new QThread(this);
	Snapshot *snapshot = new Snapshot("wechat.snapshot.ini");

	Request *request = new Request(this);

	typedef struct{
		QString device_id;
		QString sid;
		QString skey;
		QString uin;
	}BaseRequest;

	BaseRequest baseRequest;

	quint64 syncCount = 0L;
	bool forceToExit = false;

	WechatProtocol::User myProfile;
public:

	typedef struct {
		QString userName; //@c4047cc0208ff9383308837cbf757db0
		QString nickName; //中文
		QString remarkName; //备注
		QString displayName; //空?
		QString uin; // UIN 微信用户识别码
	} Contact;
private:
	QHash<QString, Contact> userNameList;
	QHash<QString, Contact> nickNameList;
	QHash<QString, Contact> remarkNameList;
	QHash<QString, Contact> uinList;

	int timerId = -1;
	inline void stopTimer(){
		if(this->timerId == -1){
			qDebug() << "[WARNI]:" << FuncName << ": Kill Timer attached invalid timerid" << this->timerId << ", nothing to be killed.";
			return;
		}
		this->killTimer(this->timerId);
		this->timerId = -1;
	}

	inline void resumeTimer(){
		if(this->timerId != -1){
			qDebug() << "[WARNI]:" << FuncName << ": Ready Timer attached timer is already running, try to killed...";
			this->killTimer(this->timerId);
			this->timerId = -1;
		}
		this->timerId = this->startTimer(1500);
	}

	inline void sendAlertMessage(QString message);

	inline void updateNameList(const Contact &c);

protected:
	virtual void messageProcessing(Message msg);

	void timerEvent(QTimerEvent *);

	bool doLogin();

public:
	explicit Bot(QObject *parent = 0);

	/**
	 * @brief getQrCode 取得登录二维码
	 * @return
	 */
	bool getQrCode();

	/**
	 * @brief init 主要做登录获取SyncKey
	 * @return
	 */
	bool init();

	bool statusNotify();

	/**
	 * @brief login 登录, 主要控制用户在手机上点击确认登录之后获取sKey, Sid, Uid, SyncKeys的
	 * @param usingSnapShot
	 * @return
	 */
	bool login(bool usingSnapShot = true);

	/**
	 * @brief syncCheck 循环消息检查
	 * @return
	 */
	WechatProtocol::Response_synccheck syncCheck();

	/**
	 * @brief syncHostCheck
	 * @return
	 */
	bool syncHostCheck();

	/**
	 * @brief syncMessage 获得最新的消息
	 * @return
	 */
	WechatProtocol::Response_webwxsync syncMessage();

	/**
	 * @brief handleMsg 处理消息(发送信号)
	 */
	void handleMsg();

	/**
	 * @brief sendMsg 发送消息
	 * @param msg 消息结构体
	 * @return
	 */
	bool sendMsg(Message msg);

	/**
	 * @brief getContact 获得好友列表
	 * @return
	 */
	bool getContact();

	/**
	 * @brief getBatchContact 获得群组列表
	 * @param usernames
	 * @return
	 */
	bool getBatchContact(QStringList usernames);

	bool sync();
signals:
	void messageProcessingSignal(Message msg);
	void falltoAlert(QString mobile, QString content);
	void exitThread(QThread *thread);

	void setQrPixmap(const QByteArray &picData);
public slots:
	void sendMessage(Message msg){
		if(!this->sendMsg(msg)){
			qDebug() << "[ERROR]:" << FuncName << ": send message failed.";
		}
	}

	/**
	 * @brief start 线程开始的时候
	 */
	void start();
};

#endif // BOT_H
