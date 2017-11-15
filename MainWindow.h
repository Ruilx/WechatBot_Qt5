#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ThreadController.h"
#include "Bot.h"
#include "MessageQuery.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	Bot *bot = new Bot();
	MessageQuery *messageQuery = new MessageQuery();

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
public slots:
	void joinThread(QThread *thread){
		ThreadController::getInstance()->quitThread(thread);
		ThreadController::getInstance()->quitAllThread();
	}
};

#endif // MAINWINDOW_H
