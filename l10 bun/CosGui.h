#pragma once
#include<iostream>
#include<sstream>
#include<QtWidgets/qwidget.h>
#include<QtWidgets/qlayout.h>
#include<QtWidgets/qlistwidget.h>
#include<QtWidgets/qformlayout.h>
#include<QtWidgets/qlineedit.h>
#include<QtWidgets/qpushbutton.h>
#include<QtWidgets/qdialog.h>
#include<QtWidgets/qmessagebox.h>
#include "Service.h"
#include "observer.h"
#include "observable.h"




class CosGUI : public QWidget,public Observer {
public:
	CosGUI(Cos& cos) : cos { cos } {
		cos.addObserver(this);
		initGUICos();
		loadDataCos();
		initConnectCos();
	}
private:
	Cos& cos;
	void initGUICos();
	void loadDataCos();
	void initConnectCos();
	void update() override;

	QListWidget* lstcos = new QListWidget();
	QPushButton* btnaddcos = new QPushButton("&Adauga");
	QPushButton* btnrandcos = new QPushButton("&Random");
	QPushButton* btngoleste = new QPushButton("&Goleste");
	QPushButton* btnexporta = new QPushButton("&Exporta");
	QPushButton* btnpaint = new QPushButton("&Paint");
};