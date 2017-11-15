#ifndef NETWORKCOOKIE_H
#define NETWORKCOOKIE_H

#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QString>
#include <QSettings>
#include "Global.h"

/**
 * @brief The NetworkCookie class
 * cookie 中可以设置的项目:
 * --> Name
 * --> Value
 * --> Domain
 * --> ExpirationDate
 * --> HttpOnly
 * --> Path
 * --> Secure
 */

class NetworkCookie : public QNetworkCookieJar{
	Q_OBJECT

	static NetworkCookie *instance;
public:
	NetworkCookie(QObject *parent = nullptr): QNetworkCookieJar(parent){

	}
	~NetworkCookie(){

	}

	void saveCookie(const QString &cookieIniFile){
		QSettings cookieFile(cookieIniFile, QSettings::IniFormat);
		if(!cookieFile.isWritable()){
			qDebug() << "[ERROR]:" << FuncName << ": savecookie failed: file cannot write. filename:" << cookieIniFile;
			return;
		}
		QList<QNetworkCookie> cookieList = this->getCookies();
		for(QNetworkCookie cookie: cookieList){
			cookieFile.beginGroup(QString::fromUtf8(cookie.name()));
			cookieFile.setValue("Name", cookie.name());
			cookieFile.setValue("Value", cookie.value());
			cookieFile.setValue("Domain", cookie.domain());
			cookieFile.setValue("ExpirationDate", cookie.expirationDate());
			cookieFile.setValue("HttpOnly", cookie.isHttpOnly());
			cookieFile.setValue("Path", cookie.path());
			cookieFile.setValue("Secure", cookie.isSecure());
			cookieFile.endGroup();
		}
	}

	void loadCookie(const QString &cookieIniFile){
		QSettings cookieFile(cookieIniFile, QSettings::IniFormat);
		QList<QNetworkCookie> cookieList;
		QStringList cookieHeads = cookieFile.childGroups();
		for(QString cookieHead: cookieHeads){
			cookieFile.beginGroup(cookieHead);
			QStringList cookieItems = cookieFile.childKeys();
			QNetworkCookie cookie;
			for(QString cookieItem: cookieItems){
				QVariant value = cookieFile.value(cookieItem);
				if(cookieItem == "Name"){
					cookie.setName(value.toByteArray());
				}else if(cookieItem == "Value"){
					cookie.setValue(value.toByteArray());
				}else if(cookieItem == "Domain"){
					cookie.setDomain(value.toString());
				}else if(cookieItem == "ExpirationDate"){
					cookie.setExpirationDate(value.toDateTime());
				}else if(cookieItem == "HttpOnly"){
					cookie.setHttpOnly(value.toBool());
				}else if(cookieItem == "Path"){
					cookie.setPath(value.toString());
				}else if(cookieItem == "Secure"){
					cookie.setSecure(value.toBool());
				}
			}
			cookieList.append(cookie);
			cookieFile.endGroup();
		}
		this->setCookies(cookieList);
	}

	QList<QNetworkCookie> getCookies(){
		return allCookies();
	}
	void setCookie(const QNetworkCookie &cookie){
		if(this == nullptr){
			return;
		}
		this->setCookie(cookie);
	}
	void setCookies(const QList<QNetworkCookie> &cookieList){
		if(this == nullptr){
			return;
		}
		this->setAllCookies(cookieList);
	}

	static NetworkCookie *getInstance(){
		if(instance == nullptr){
			instance = new NetworkCookie();
		}
		return instance;
	}
};

#endif // NETWORKCOOKIE_H
