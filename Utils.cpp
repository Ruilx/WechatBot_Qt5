#include "Utils.h"


QString Utils::repeat(Unit unit, int repeat){
	QString result;
	for(int i = 0; i < repeat; i++){
		result.append(unit());
	}
	return result;
}

QString Utils::rand(){
	return QString::number(qrand() % 10);
}

QString Utils::now(){
	return QString::number(QDateTime::currentDateTime().currentMSecsSinceEpoch(), 10);
}

float Utils::now_number(){
	return double(QDateTime::currentDateTime().currentMSecsSinceEpoch() / 10) / 100.0f;
}

QString Utils::time(){
	return QString::number(int(QDateTime::currentDateTime().currentMSecsSinceEpoch() / 1000), 10);
}

QString Utils::time_negate(){
	return QString::number(qAbs(~int(QDateTime::currentDateTime().currentMSecsSinceEpoch() / 1000)), 10);
}

QString Utils::urlParamsBuilder(const QHash<QString, QString> &params){
	QStringList keys = params.keys();
	QStringList kvStr;
	for(QString key: keys){
		kvStr.append(key.append("=") + params.value(key, "").toUtf8().toPercentEncoding());
	}
	return kvStr.join("&");
}
