#ifndef WECHATPROTOCOL_H
#define WECHATPROTOCOL_H

#include <QtCore>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QtXml>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QDomNode>

//namespace Profile_ns {

//typedef struct{
//	QString buff;
//}UserName;

//typedef struct{
//	QString buff;
//}NickName;

//typedef struct{
//	QString buff;
//}BindEmail;

//typedef struct{
//	QString buff;
//}BindMobile;

//}

class WechatProtocol
{
public:
	typedef struct{
		QString ret;
		QString msg;
		QString uuid;
	}Cgi_bin_mmwebwx_bin_webwxpushloginurl, Response_webwxpushloginurl;

	typedef struct{
		QString window_QRLogin_code;
		QString window_QRLogin_uuid;
		QString window_QRLogin_error;
	}Response_jslogin;

	typedef struct{
		QString window_code;
		QByteArray window_userAvatar;
		QString window_redirect_uri;
	}Cgi_bin_mmwebwx_bin_login, Response_login;

	typedef struct{
		QString ret;
		QString message;
		QString skey;
		QString wxsid;
		QString wxuin;
		QString pass_ticket;
		QString isgrayscale;
	}Cgi_bin_mmwebwx_bin_webwxnewloginpage, Response_webwxnewloginpage;

	typedef struct{
		QString uin;				// 0
		QString userName;			// 用户名称, 一个@为好友, 两个@为群组
		QString nickName;			// 昵称
		QString attrStatus;
		QString pyInitial;			// 用户名拼音缩写(大写字母)
		QString pyQuanPin;			// 用户名拼音全拼
		QString remarkPyInitial;	// 备注拼音缩写(大写字母)
		QString remarkPyQuanPin;	// 备注拼音全拼
		QString memberStatus;
		QString displayName;		// ""
		QString keyWord;			//
	}Member;

	typedef struct{
		QString uin;				// 0
		QString userName;			// 用户名称, 一个@为好友, 两个@为群组
		QString nickName;			// 昵称
		QString headImgUrl;			// 头像图片地址
		QString contactFlag;		// 类型 1:好友 2:群组 3:公众号
		QString memberCount;		// 成员数量, 只有在群组信息中有效
		QList<Member> memberList;	// 成员列表
		QString remarkName;			// 备注名称
		QString hideInputBarFlag;	// 0
		QString sex;				// 性别 0:未设置/公众号/保密 1:男 2:女
		QString signature;			// 公众号功能介绍/好友的个性签名
		QString verifyFlag;			// 0
		QString ownerUin;			// 0
		QString pyInitial;			// 用户名拼音缩写(大写字母)
		QString pyQuanPin;			// 用户名拼音全拼
		QString remarkPyInitial;	// 备注拼音缩写(大写字母)
		QString remarkPyQuanPin;	// 备注拼音全拼
		QString starFriend;			// 是否星标朋友 0:否 1:是
		QString appAccountFlag;		// 0
		QString statues;			// 0
		QString attrStatus;			// 119911
		QString province;			// 省
		QString city;				// 市
		QString alias;				//
		QString snsFlag;			// 17
		QString uniFriend;			// 0
		QString displayName;		// ""
		QString chatRoomId;			// 0
		QString keyWord;			//
		QString encryChatRoomId;	//
		QString isOwner;			// 群组中是否是创建者 0:否 1:是
	}Contact;

	typedef struct{
		QString key;
		QString val;
	}SyncKey_Node;

	typedef struct{
		QString count;
		QList<SyncKey_Node> list;
	} SyncKey;

	typedef struct{
		QString uin;
		QString userName;
		QString nickName;
		QString headImgUrl;
		QString remarkName;
		QString pyInitial;
		QString pyQuanPin;
		QString remarkPyInitial;
		QString remarkPyQuanPin;
		QString hideInputBarFlag;
		QString starFriend;
		QString sex;
		QString signature;
		QString appAccountFlag;
		QString verifyFlag;
		QString contactFlag;
		QString webWxPluginSwitch;
		QString headImgFlag;
		QString snsFlag;
	}User;

	typedef struct{
		QString title;
		QString digest;
		QString cover;
		QString url;
	}MPArticle;

	typedef struct{
		QString userName;
		QString mpArticleCount;
		QList<MPArticle> mpArticleList;
		QString time;
		QString nickName;
	}MPSubscribeMsg;

	typedef struct{
		QString ret;
		QString errMsg;
	} BaseResponse;

	typedef struct{
		QString deviceId;
		QString sid;
		QString skey;
		QString uin;
	} BaseRequest;

	typedef struct{
		BaseResponse baseResponse;
		QString count;
		QList<Contact> ContactList;
		SyncKey syncKey;
		User user;
		QString chatSet;
		QString sKey;
		QString clientVersion;
		QString systemTime;
		QString grayScale;
		QString inviteStartCount;
		QString mpSubscribeMsgCount;
		QList<MPSubscribeMsg> mpSubscribeMsgList;
		QString clickReportInterval;
	}Cgi_bin_mmwebwx_bin_webwxinit, Response_webwxinit;

	typedef struct{
		BaseResponse baseResponse;
		QString msgId;
	}Cgi_bin_mmwebwx_bin_webwxstatusnotify, Response_webwxstatusnotify;

	typedef struct{
		BaseResponse baseResponse;
		QString memberCount;
		QList<Contact> memberList;
		QString seq;
	}Cgi_bin_mmwebwx_bin_webwxgetcontact, Response_webwxgetcontact;

	typedef struct{
		BaseResponse baseResponse;
		QString count;
		QList<Contact> contactList;
	}Cgi_bin_mmwebwx_bin_webwxbatchgetcontact, Response_webwxbatchgetcontact;

	typedef struct{
		QString retcode;
		QString selector;
	}Cgi_bin_mmwebwx_bin_synccheck, Response_synccheck;

	typedef struct{
		QString bitFlag;
		struct{ QString buff; } userName;
		struct{ QString buff; } nickName;
		QString bindUin;
		struct{ QString buff; } bindEmail;
		struct{ QString buff; } bindMobile;
		QString status;
		QString sex;
		QString personalCard;
		QString alias;
		QString headImgUpdateFlag;
		QString headImgUrl;
		QString signature;
	}Profile;

	typedef struct{
		QString userName;
		QString nickName;
		QString qqNum;
		QString province;
		QString city;
		QString content;
		QString signature;
		QString alias;
		QString scene;
		QString verifyFlag;
		QString attrStatus;
		QString sex;
		QString ticket;
		QString opCode;
	} RecommendInfo;

	typedef struct{
		QString appId;
		QString type;
	} AppInfo;

	typedef struct{
		QString msgId;
		QString fromUserName;
		QString toUserName;
		QString msgType;
		QString content;
		QString status;
		QString imgStatus;
		QString createTime;
		QString voiceLength;
		QString playLength;
		QString fileName;
		QString fileSize;
		QString mediaId;
		QString url;
		QString appMsgType;
		QString statusNotifyCode;
		QString statusNotifyUserName;
		RecommendInfo recommendInfo;
		QString forwardFlag;
		AppInfo appInfo;
		QString hasProductId;
		QString ticket;
		QString imgHeight;
		QString imgWidth;
		QString subMsgType;
		QString newMsgId;
		QString oriContent;
	} AddMsg;

	typedef struct{

	} ModContact;

	typedef struct{

	} DelContact;

	typedef struct{

	} ModChatRoomMember;

	typedef struct{
		BaseResponse baseResponse;
		QString addMsgCount;
		QList<AddMsg> addMsgList;
		QString modContactCount;
		QList<ModContact> modContactList;
		QString delContactCount;
		QList<DelContact> delContactList;
		QString modChatRoomMemberCount;
		QList<ModChatRoomMember> modChatRoomMemberList;
		Profile profile;
		QString continueFlag;
		SyncKey syncKey;
		QString sKey;
		SyncKey syncCheckKey;
	}Cgi_bin_mmwebwx_bin_webwxsync, Response_webwxsync;

	typedef struct{
		BaseRequest baseRequest;
		SyncKey syncKey;
		QString rr;
	}Request_webwxsync;

	typedef struct{
		BaseRequest baseRequest;
		struct {
			QString type;
			QString content;
			QString fromUserName;
			QString toUserName;
			QString localId;
			QString clientMsgId;
		} msg;
		QString scene;
	}Request_webwxsendmsg;

	typedef struct{
		QString userName;
		QString chatRoomId;
	}BatchContact_Node;

	typedef struct{
		BaseRequest baseRequest;
		QString count;
		QList<BatchContact_Node> list;
	}Request_webwxbatchgetcontact;

public:
	static Member resolve_member_json(const QJsonObject &member);

	static Contact resolve_contact_json(const QJsonObject &contact);

	static SyncKey resolve_syncKey_json(const QJsonObject &syncKey);

	static RecommendInfo resolve_recommendInfo_json(const QJsonObject &recommendInfo);

	static AppInfo resolve_appInfo_json(const QJsonObject &appInfo);

	static AddMsg resolve_addMsg_json(const QJsonObject &addMsg);

	static ModContact resolve_modContact_json(const QJsonObject &modContact);

	static DelContact resolve_delContact_json(const QJsonObject &delContact);

	static ModChatRoomMember resolve_modChatRoomMember_json(const QJsonObject &modChatRoomMember);

	static Profile resolve_profile_json(const QJsonObject &profile);

public:
	WechatProtocol();

	static Response_jslogin resolve_jslogin(const QByteArray &data);

	static Response_login resolve_cgi_bin_mmwebwx_bin_login(const QByteArray &data);

	static Response_webwxnewloginpage resolve_cgi_bin_mmwebwx_bin_webwxnewloginpage(const QByteArray &data);

	static Response_webwxinit resolve_cgi_bin_mmwebwx_bin_webwxinit(const QByteArray &data);

	static Response_webwxstatusnotify resolve_cgi_bin_mmwebwx_bin_webwxstatusnotify(const QByteArray &data);

	static Response_webwxgetcontact resolve_cgi_bin_mmwebwx_bin_webwxgetcontact(const QByteArray &data);

	static Response_webwxbatchgetcontact resolve_cgi_bin_mmwebwx_bin_webwxbatchgetcontact(const QByteArray &data);

	static Response_synccheck resolve_cgi_bin_mmwebwx_bin_synccheck(const QByteArray &data);

	static Response_webwxsync resolve_cgi_bin_mmwebwx_bin_webwxsync(const QByteArray &data);

	static Response_webwxpushloginurl resolve_cgi_bin_mmwebwx_bin_webwxpushloginurl(const QByteArray &data);

	static QJsonDocument makeup_cgi_bin_mmwebwx_bin_webwxsync(Request_webwxsync params);

	static QJsonDocument makeup_cgi_bin_mmwebwx_bin_webwxsendmsg(Request_webwxsendmsg params);

	static QJsonDocument makeup_cgi_bin_mmwebwx_bin_webwxbatchgetcontact(Request_webwxbatchgetcontact params);
};

#endif // WECHATPROTOCOL_H
