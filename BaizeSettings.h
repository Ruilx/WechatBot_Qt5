#ifndef BAIZESETTINGS_H
#define BAIZESETTINGS_H

#include <QtCore>

class BaizeSettings
{
	QSettings *bzSetting;
	QHash<QString, QVariant> kvMap;
public:
	static BaizeSettings *getInstance(){
		if(_instance == nullptr){
			_instance = new BaizeSettings("baize.ini");
		}
		return _instance;
	}

	static inline BaizeSettings *baizeSettings(){
		return BaizeSettings::getInstance();
	}

	BaizeSettings(const QString &filename){
		this->bzSetting = new QSettings(filename, QSettings::IniFormat);
		this->bzSetting->beginGroup("baize");
		foreach(QString key, this->bzSetting->childKeys()){
			this->kvMap.insert(key, this->bzSetting->value(key));
		}
		this->bzSetting->endGroup();
	}

	QString getValue(QString key){
		return this->kvMap.value(key, QString()).toString();
	}
};

#endif // BAIZESETTINGS_H
