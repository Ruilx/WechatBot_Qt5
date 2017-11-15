#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDateTime>
#include <QHash>
#include <QCryptographicHash>
#include "WechatProtocol.h"

typedef QString(Unit)(void);

class Utils
{
public:
	Utils();

	/**
	 * @brief repeat 返回一个指定函数的返回的字符串的repeat次的结果
	 * @param unit 一个返回QString, 没有参数的函数指针
	 * @param repeat 重复执行那个函数多少次
	 * @return 链接字符串的结果
	 */
	static QString repeat(Unit unit, int repeat);

	/**
	 * @brief rand 0-9的随机数, 返回字符串
	 * @return 字符串0-9
	 */
	static QString rand();

	/**
	 * @brief now 返回一个字符串时间戳, 精确到毫秒
	 * @return 字符串时间戳
	 */
	static QString now();

	/**
	 * @brief time 返回一个字符串时间戳, 精确到秒
	 * @return 字符串时间戳
	 */
	static QString time();

	/**
	 * @brief time_negate 返回一个字符串时间戳取反, 精确到秒取反
	 * @return 字符串时间戳取反
	 */
	static QString time_negate();

	/**
	 * @brief urlParamsBuilder URL参数合成字符串
	 * @param params kv映射组
	 * @return 使用k=v&k=v方式返回消息
	 */
	static QString urlParamsBuilder(const QHash<QString, QString> &params);

	/**
	 * @brief syncKeyStrBuilder 微信特有的SyncKey的请求的字符串方式
	 * @param syncKeyList SyncKey的内容
	 * @return 字符串
	 */
	static QString syncKeyStrBuilder(const WechatProtocol::SyncKey &syncKeyList){
		QStringList pattern;
		for(WechatProtocol::SyncKey_Node p: syncKeyList.list){
			pattern.append(p.key + "_" + p.val);
		}
		return pattern.join('|');
	}

	/**
	 * @brief easyCert 简单对接加密
	 * @param salt
	 * @param secretKey
	 * @param token
	 * @param r
	 * @return
	 */
	static QString easyCert(const QString &salt, const QString &secretKey, const QString &token, const QString &r){
		QCryptographicHash sha256(QCryptographicHash::Md5);
		sha256.addData(salt.toUtf8());
		sha256.addData(secretKey.toUtf8());
		sha256.addData(token.toUtf8());
		sha256.addData(r.toUtf8());
		return QString::fromUtf8(sha256.result().toHex().toUpper());
	}

	static float now_number();
};

#endif // UTILS_H
