#ifndef SHOWQRCODE_H
#define SHOWQRCODE_H

#include <QtWidgets>
#include "Global.h"

class ShowQrcode : public QWidget
{
	Q_OBJECT
	QLabel *qrcode = new QLabel();
	QPixmap *qrPixmap = new QPixmap();
public:
	ShowQrcode(const QByteArray &picData, QWidget *parent = 0) : QWidget(parent){
		if(!this->qrPixmap->loadFromData(picData)){
			qDebug() << FuncName << "qrPixmap load failed.";
		}
		if(this->qrPixmap->isNull()){
			this->qrcode->setText(tr("Picture loaded failure."));
			this->resize(350, 350);
		}else{
			this->qrcode->setPixmap(*this->qrPixmap);
			this->resize(this->qrPixmap->size());
		}

		QVBoxLayout *mainLay = new QVBoxLayout;
		this->setLayout(mainLay);
		mainLay->addWidget(this->qrcode, 0, Qt::AlignCenter);
	}

	ShowQrcode(QWidget *parent = 0) : QWidget(parent){
		this->qrcode->setText(tr("Picture loaded failure."));
		this->resize(350, 350);

		QVBoxLayout *mainLay = new QVBoxLayout;
		this->setLayout(mainLay);
		mainLay->addWidget(this->qrcode, 0, Qt::AlignCenter);
	}

	void setPixmap(const QPixmap &pic){
		if(this->qrPixmap != nullptr){
			delete this->qrPixmap;
			this->qrPixmap = nullptr;
		}
		this->qrPixmap = new QPixmap(pic);
	}

	void setPixmap(const QByteArray &picData){
		if(!this->qrPixmap->loadFromData(picData)){
			qDebug() << "[ERROR]:" << FuncName << ":pic data is not vaild.";
		}
		if(!this->qrPixmap->isNull()){
			this->qrcode->setPixmap(*this->qrPixmap);
			this->resize(this->qrPixmap->size());
		}
	}

signals:

public slots:
	void setPixmapSlot(const QByteArray &picData){
		this->setPixmap(picData);
	}
};

#endif // SHOWQRCODE_H
