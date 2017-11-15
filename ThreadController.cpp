#include "ThreadController.h"

ThreadController *ThreadController::_instance = nullptr;

ThreadController::ThreadController(){
}

void ThreadController::insertThread(qint64 tid, QThread *thread){
	this->threads.insert(tid, thread);
}

QThread *ThreadController::getThread(qint64 tid){
	return this->threads.value(tid, nullptr);
}

bool ThreadController::quitThread(QThread *thread){
	if(thread == nullptr){
		return false;
	}
	thread->quit();
	thread->wait(10000);
	delete thread;
	return true;
}

bool ThreadController::quitThread(qint64 tid){
	return this->quitThread(this->threads.value(tid, nullptr));
}

void ThreadController::quitAllThread(){
	QList<qint64> threadIds = this->threads.keys();
	foreach(qint64 id, threadIds){
		this->quitThread(this->threads.value(id, nullptr));
	}
}

ThreadController *ThreadController::getInstance(){
	if(_instance == nullptr){
		_instance = new ThreadController();
	}
	return _instance;
}

QHash<qint64, QThread*> ThreadController::getHashTable(){
	return this->threads;
}
