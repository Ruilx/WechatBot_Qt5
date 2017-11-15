#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore>
#include "Utils.h"
#include "BaizeSettings.h"

#define FunctionName __func__
#define FuncName FunctionName
#define _FileName __FILE__
#define _LineNum __LINE__

#define Wechat_jslogin							"https://login.wx.qq.com/jslogin"
#define Wechat_l								"https://login.weixin.qq.com/l/%1" // %1 = {}
#define Wechat_qrcode							"https://login.weixin.qq.com/qrcode/%1" // %1 = {uuid}
#define Wechat_cgi_bin_mmwebwx_bin_login		"https://login.wx.qq.com/cgi-bin/mmwebwx-bin/login?tip=%1&uuid=%2&_=%3&loginicon=%4" // %1 = {tip}, %2 = {uuid}, %3 = {now}
#define Wechat_cgi_bin_mmwebwx_bin_synccheck	"https://%1/cgi-bin/mmwebwx-bin/synccheck?%2" // %1 = {base_host}, %2 {params}
#define Wechat_cgi_bin_mmwebwx_bin_webwxsync	"%1/webwxsync?sid=%2&skey=%3&lang=en_US&pass_ticket=%4" // %1 = {base_uri}, %2 = {sid}, %3 = {skey}, %4 = {pass_ticket}
#define Wechat_cgi_bin_mmwebwx_bin_webwxinit	"%1/webwxinit?r=%2&lang=en_US&pass_ticket=%3" // %1 = {base_uri}, %2 = {r}, %3 = {pass_ticket}
// https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxstatusnotify?pass_ticket=qOXQtm16YzIbuXdDHI7odUwtHKpPhfdN%252Fh8eah8%252Br3m9HN0RuSQVjVk9V7ezZjyf
#define Wechat_cgi_bin_mmwebwx_bin_webwxstatusnotify	"%1/webwxstatusnotify?pass_ticket=%2" // %1 = {base_uri}, %2 = {pass_ticket}
// https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxsendmsg
#define Wechat_cgi_bin_mmwebwx_bin_webwxsendmsg	"%1/webwxsendmsg"
// https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxlogout?redirect=1&type=0&skey=%40crypt_90eaca79_58bf52eca1224ff8a06734c55858a57a
#define Wechat_cgi_bin_mmwebwx_bin_webwxlogout	"%1/webwxlogout?redirect=%2&type=0&skey=%3" // %1 = {base_uri}, %2 = {redirect}, %3 = {skey}
// https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxgetcontact
#define Wechat_cgi_bin_mmwebwx_bin_webwxgetcontact	"%1/webwxgetcontact?r=%2&seq=%3&skey=%4&pass_ticket=%5" // %1 = {base_uri}, %2 = {r}, %3 = {seq}, %4 = {skey}, %5 = {pass_ticket}
// https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxbatchgetcontact
#define Wechat_cgi_bin_mmwebwx_bin_webwxbatchgetcontact	"%1/webwxbatchgetcontact?type=ex&r=%2&lang=zh_CN&pass_ticket=%3" // %1 = {base_uri}, %2 = {r}, %3 = {pass_ticket}
// https://wx2.qq.com/cgi-bin/mmwebwx-bin/webwxpushloginurl?uin=579575447
#define Wechat_cgi_bin_mmwebwx_bin_webwxpushloginurl	"%1/webwxpushloginurl?uin=%2" // %1 = {base_uri}, %2 = {uin}

#define WechatAppId					"wx782c26e4c19acffb"
#define WechatFirstLoginUrl			Wechat_jslogin
#define WechatGetQrCodeContent		Wechat_l
#define WechatGetQrCodePicUrl		Wechat_qrcode
#define WechatSecondLoginUrl		Wechat_cgi_bin_mmwebwx_bin_login
#define WechatBotSyncCheckUrl		Wechat_cgi_bin_mmwebwx_bin_synccheck
#define WechatBotSyncUrl			Wechat_cgi_bin_mmwebwx_bin_webwxsync
#define WechatInitUrl				Wechat_cgi_bin_mmwebwx_bin_webwxinit
#define WechatSendMsgUrl			Wechat_cgi_bin_mmwebwx_bin_webwxsendmsg
#define WechatGetContactUrl			Wechat_cgi_bin_mmwebwx_bin_webwxgetcontact
#define WechatGetBatchContactUrl	Wechat_cgi_bin_mmwebwx_bin_webwxbatchgetcontact
#define WechatPushLoginUrl			Wechat_cgi_bin_mmwebwx_bin_webwxpushloginurl

#define BaizeMessageHandleToken		"BaizeMessageHandleToken"
#define BaizeMessageHandleUrl		"BaizeMessageHandleUrl"
//#undef BaizeMessageHandleUrl
//#define BaizeMessageHandleUrl		"BaizeMessageHandleUrl"
/*
 * r = R%w629Hd9wpjd;;,d-_93/c?\dkw0499s\nsi2/a
 * sk = &9*3926dhhci388^s2930047cHsf92hhHslf-h;.''a
 * sp = Seifu4tebbeufhYd9eGaggs093*dh2((dsu_)-*3
 * from = Fus837*d7GsckIYs937%%s530++-s=d94ucCyst
 * fun = 'Wen'
 */
#define SecretKey		"SecretKey"
#define ServicePassword	"ServicePassword"
#define From			"From"
#define Fun				"Fun"

#define Salt			"Salt"
#define TokenKey		"TokenKey"

typedef struct {
	QString fromUserName;
	QString toUserName;
	QString content;
	QString messageId;
} Message;


class Utils;

class Global{
	static Global *instance;
private:
	QHash<QString, QString> wechatLoginHeaders;
	QHash<QString, QString> wechatHeaders;
	QHash<QString, QString> wechatMsgHeaders;
	QHash<QString, QString> baizeHeaders;
	QHash<QString, QString> wechatContactHeaders;
public:
	QString getWechatAppId() const{
		return QString(WechatAppId);
	}

	QString getWechatFirstLoginUrl() const{
		return QString(WechatFirstLoginUrl);
	}

	QString getWechat_jslogin() const{
		return QString(Wechat_jslogin);
	}

	QString getWechatGetQrCodeContent(const QString &uuid) const{
		return QString(WechatGetQrCodeContent).arg(uuid);
	}

	QString getWechat_l(const QString &uuid) const{
		return QString(Wechat_l).arg(uuid);
	}

	QString getWechatGetQrCodePicUrl(const QString &uuid) const{
		return QString(WechatGetQrCodePicUrl).arg(uuid);
	}

	QString getWechat_qrcode(const QString &uuid) const{
		return QString(Wechat_qrcode).arg(uuid);
	}

	QString getWechatSecondLoginUrl(const QString &tip, const QString &uuid, const QString &now = QString(), bool loginIcon = true) const{
		QString _ = now.isEmpty() ? Utils::now() : now;
		return QString(WechatSecondLoginUrl).arg(tip).arg(uuid).arg(_).arg(loginIcon ? "true" : "");
	}

	QString getWechat_cgi_bin_mmwebwx_bin_login(const QString &tip, const QString &uuid, const QString &now = QString(), bool loginIcon = true) const{
		QString _ = now.isEmpty() ? Utils::now() : now;
		return QString(Wechat_cgi_bin_mmwebwx_bin_login).arg(tip).arg(uuid).arg(_).arg(loginIcon ? "true" : "");
	}

	QString getWechatBotSyncCheckUrl(const QString &baseHost, const QString &params) const{
		return QString(WechatBotSyncCheckUrl).arg(baseHost).arg(params);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_synccheck(const QString &baseHost, const QString &params) const{
		return QString(Wechat_cgi_bin_mmwebwx_bin_synccheck).arg(baseHost).arg(params);
	}

	QString getWechatBotSyncUrl(const QString &baseUri, const QString &sid, const QString &skey, const QString &passTicket) const{
		return QString(WechatBotSyncUrl).arg(baseUri).arg(sid).arg(skey).arg(passTicket);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_webwxsync(const QString &baseUri, const QString &sid, const QString &skey, const QString &passTicket) const{
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxsync).arg(baseUri).arg(sid).arg(skey).arg(passTicket);
	}

	QString getWechatInitUrl(const QString &baseUri, const QString &r, const QString &passTicket) const{
		return QString(WechatInitUrl).arg(baseUri).arg(r).arg(passTicket);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_webwxinit(const QString &baseUri, const QString &r, const QString &passTicket) const{
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxinit).arg(baseUri).arg(r).arg(passTicket);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_webwxstatusnotify(const QString &baseUri, const QString &pass_ticket){
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxstatusnotify).arg(baseUri).arg(pass_ticket);
	}

	QString getWechatStatusNotify(const QString &baseUri, const QString &pass_ticket){
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxstatusnotify).arg(baseUri).arg(pass_ticket);
	}

	QString getWechatSendMsgUrl(const QString &baseUri){
		return QString(WechatSendMsgUrl).arg(baseUri);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_webwxsendmsg(const QString &baseUri){
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxsendmsg).arg(baseUri);
	}

	QString getWechatGetContactUrl(const QString &baseUri, const QString &r, const QString &seq, const QString &skey, const QString &passTicket){
		return QString(WechatGetContactUrl).arg(baseUri).arg(r).arg(seq).arg(skey).arg(passTicket);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_webwxgetcontact(const QString &baseUri, const QString &r, const QString &seq, const QString &skey, const QString &passTicket){
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxgetcontact).arg(baseUri).arg(r).arg(seq).arg(skey).arg(passTicket);
	}

	QString getWechatGetBatchContactUrl(const QString &baseUri, const QString &r, const QString &passTicket){
		return QString(WechatGetBatchContactUrl).arg(baseUri).arg(r).arg(passTicket);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_webwxbatchgetcontact(const QString &baseUri, const QString &r, const QString &passTicket){
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxbatchgetcontact).arg(baseUri).arg(r).arg(passTicket);
	}

	QString getWechatPushLoginUrl(const QString &baseUri, const QString &uin){
		return QString(WechatPushLoginUrl).arg(baseUri).arg(uin);
	}

	QString getWechat_cgi_bin_mmwebwx_bin_webwxpushloginurl(const QString &baseUri, const QString &uin){
		return QString(Wechat_cgi_bin_mmwebwx_bin_webwxpushloginurl).arg(baseUri).arg(uin);
	}

	QHash<QString, QString> getWechatLoginHeaders() const{
		return this->wechatLoginHeaders;
	}

	QHash<QString, QString> getWechatHeaders() const{
		return this->wechatHeaders;
	}

	QHash<QString, QString> getWechatMsgHeaders() const{
		return this->wechatMsgHeaders;
	}

	QHash<QString, QString> getWechatContactHeaders() const{
		return this->wechatContactHeaders;
	}

	QString getBaizeMessageHandleUrl(){
		QString r = Utils::now();
		return BaizeSettings::baizeSettings()->getValue(BaizeMessageHandleUrl)
				.arg(r)
				.arg(BaizeSettings::baizeSettings()->getValue(SecretKey))
				.arg(Utils::easyCert(BaizeSettings::baizeSettings()->getValue(Salt),
									 BaizeSettings::baizeSettings()->getValue(ServicePassword),
									 BaizeSettings::baizeSettings()->getValue(TokenKey),
									 r))
				.arg(BaizeSettings::baizeSettings()->getValue(From))
				.arg(BaizeSettings::baizeSettings()->getValue(Fun));
	}

	QHash<QString, QString> getBaizeHeaders() const{
		return this->baizeHeaders;
	}

protected:
	Global(){
		this->wechatLoginHeaders.insert("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
		this->wechatLoginHeaders.insert("accept-encoding", "deflate, br");
		this->wechatLoginHeaders.insert("accept-language", "zh-CN,zh;q=0.8,en-US;q=0.6,en;q=0.4");
		this->wechatLoginHeaders.insert("cache-control", "max-age=0");
		this->wechatLoginHeaders.insert("host", "login.wx.qq.com");
		this->wechatLoginHeaders.insert("content-type", "application/json; charset=UTF-8");
		this->wechatLoginHeaders.insert("user-agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36");

		this->wechatHeaders.insert("accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
		this->wechatHeaders.insert("accept-encoding", "br");
		this->wechatHeaders.insert("accept-language", "zh-CN,zh;q=0.8,en-US;q=0.6,en;q=0.4");
		this->wechatHeaders.insert("cache-control", "max-age=0");
		this->wechatHeaders.insert("host", "wx2.qq.com");
		this->wechatHeaders.insert("referer", "https://wx2.qq.com/");
		this->wechatHeaders.insert("content-type", "application/json; charset=UTF-8");
		this->wechatHeaders.insert("user-agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36");

		this->wechatMsgHeaders.insert("accept", "application/json, text/plain, */*");
		this->wechatMsgHeaders.insert("accept-encoding", "br");
		this->wechatMsgHeaders.insert("accept-language", "zh-CN,zh;q=0.8,en-US;q=0.6,en;q=0.4");
		this->wechatMsgHeaders.insert("cache-control", "max-age=0");
		this->wechatMsgHeaders.insert("host", "wx2.qq.com");
		this->wechatMsgHeaders.insert("referer", "https://wx2.qq.com/");
		this->wechatMsgHeaders.insert("content-type", "application/json; charset=UTF-8");
		this->wechatMsgHeaders.insert("user-agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36");

		this->wechatContactHeaders.insert("accept", "application/json, text/plain, */*");
		this->wechatContactHeaders.insert("accept-encoding", "gzip, deflate, br");
		this->wechatContactHeaders.insert("accept-language", "zh-CN,zh;q=0.8");
		this->wechatContactHeaders.insert("cache-control", "max-age=0");
		this->wechatContactHeaders.insert("host", "wx2.qq.com");
		this->wechatContactHeaders.insert("referer", "https://wx2.qq.com/");
		this->wechatContactHeaders.insert("user-agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_0) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36");

		this->baizeHeaders.insert("accept", "text/plain, application/json, */*;q=0.8");
		this->baizeHeaders.insert("accept-encoding", "gzip, deflate, br");
		this->baizeHeaders.insert("accept-language", "zh-CN,zh;q=0.8,en-US;q=0.6,en;q=0.4");
		this->baizeHeaders.insert("cache-control", "max-age=0");
		this->baizeHeaders.insert("content-type", "application/json; charset=UTF-8");
		this->baizeHeaders.insert("user-agent", "QtSDK/5.7.0");
		this->baizeHeaders.insert("referer", "http://r.ncf/wechat_query_outline");

	}
	~Global(){

	}

public:
	static Global *getInstance(){
		if(instance == nullptr){
			instance = new Global();
		}
		return instance;
	}
};

#define DEBUG_VERBOSE

#endif // GLOBAL_H
