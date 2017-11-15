#include "MainWindow.h"
#include <QMetaType>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QThread *messageQueryThread = new QThread(this);
	QThread *botThread = new QThread(this);

	connect(messageQueryThread, SIGNAL(started()), this->messageQuery, SLOT(start()));
	connect(messageQueryThread, SIGNAL(finished()), this->messageQuery, SLOT(deleteLater()));
	connect(botThread, SIGNAL(started()), this->bot, SLOT(start()));
	connect(botThread, SIGNAL(finished()), this->bot, SLOT(deleteLater()));
	connect(this->bot, SIGNAL(exitThread(QThread*)), this, SLOT(joinThread(QThread*)));

	qRegisterMetaType<Message>("Message");
	connect(this->bot, &Bot::messageProcessingSignal, this->messageQuery, &MessageQuery::sendQuery);
	connect(this->messageQuery, &MessageQuery::replyMessage, this->bot, &Bot::sendMessage);

	this->messageQuery->moveToThread(messageQueryThread);
	this->bot->moveToThread(botThread);

	ThreadController::getInstance()->insertThread((qint64)messageQueryThread, messageQueryThread);
	ThreadController::getInstance()->insertThread((qint64)botThread, botThread);

	messageQueryThread->start();
	botThread->start();
}

MainWindow::~MainWindow()
{
	ThreadController::getInstance()->quitAllThread();
}
