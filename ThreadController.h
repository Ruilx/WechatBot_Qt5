#ifndef THREADCONTROLLER_H
#define THREADCONTROLLER_H

#include <QThread>
#include <QtCore>

class ThreadController
{
	QHash<qint64, QThread*> threads;
	static ThreadController *_instance;
public:
	ThreadController();

	void insertThread(qint64 tid, QThread *thread);
	QThread *getThread(qint64 tid);
	bool quitThread(QThread *thread);
	bool quitThread(qint64 tid);

	void quitAllThread();

	static ThreadController *getInstance();
	QHash<qint64, QThread *> getHashTable();
};

#endif // THREADCONTROLLER_H
