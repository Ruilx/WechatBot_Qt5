#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <QSettings>
#include <QString>
#include "WechatProtocol.h"

class Snapshot
{
	//QSettings *setting = new QSettings(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationName(), QApplication::organizationName());
	QSettings *setting = nullptr;
public:
	Snapshot(const QString &filename){
		this->setting = new QSettings(filename, QSettings::IniFormat);
		this->setting->setIniCodec("utf-8");
	}

	void readSnapshot(QHash<QString, QString> &params, WechatProtocol::SyncKey &syncList, quint64 &syncCount){
		this->setting->beginGroup("params");
		QStringList keys = this->setting->childKeys();
		for(QString key: keys){
			if(params.contains(key)){
				params.take(key);
			}
			params.insert(key, this->setting->value(key).toString());
		}
		this->setting->endGroup();

		this->setting->beginGroup("synckey");
		if(!syncList.list.isEmpty()){
			syncList.list.clear();
		}
		keys = this->setting->childKeys();
		for(QString key: keys){
			WechatProtocol::SyncKey_Node node;
			node.key = key;
			node.val = this->setting->value(key).toString();
			syncList.list.append(node);
		}
		this->setting->endGroup();
		syncList.count = syncList.list.length();

		this->setting->beginGroup("syncCount");
		syncCount = this->setting->value("count").toLongLong();
		this->setting->endGroup();
	}

	void saveSnapshot(const QHash<QString, QString> &params, const WechatProtocol::SyncKey &syncList, const quint64 &syncCount){
		this->setting->clear();
		this->setting->beginGroup("params");
		for(QString key: params.keys()){
			this->setting->setValue(key, params.value(key));
		}
		this->setting->endGroup();
		this->setting->beginGroup("synckey");
		for(WechatProtocol::SyncKey_Node node: syncList.list){
			this->setting->setValue(node.key, node.val);
		}
		this->setting->endGroup();
		this->setting->beginGroup("synccount");
		this->setting->setValue("count", syncCount);
		this->setting->endGroup();
	}
};

#endif // SNAPSHOT_H
