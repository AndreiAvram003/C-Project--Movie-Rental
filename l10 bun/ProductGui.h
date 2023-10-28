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
#include "CosGui.h"
#include "CustomTableModel.h"
#include "qlistview.h"
#include "qtableview.h"
#include<QtWidgets/qlabel.h>
using std::stringstream;
class gui : public QWidget {
public:
	gui(Service& serv,Cos& cos) :serv{ serv }, cos { cos } {
		 initGUI();
		 loadData(serv.get_all());
		 initConnect();
	}
private:
	Service& serv;
	Cos& cos;
	QTableView* lst = new QTableView();
	CustomTableModel* model = new CustomTableModel{ serv.get_all() };
	QPushButton* btnexit = new QPushButton("&Exit");
	QPushButton* btnadd = new QPushButton("&Adauga");
	QPushButton* btndel = new QPushButton("&Sterge");
	QPushButton* btnmod = new QPushButton("&Modifica");
	QPushButton* btnstit = new QPushButton("&Sortare dupa titlu");
	QPushButton* btnstgen = new QPushButton("&Sortare dupa gen");
	QPushButton* btnstact = new QPushButton("&Sortare dupa actor");
	QPushButton* btnstan = new QPushButton("&Sortare dupa an");
	QPushButton* btnfiltit = new QPushButton("&Filtrare dupa titlu");
	QPushButton* btnfilact = new QPushButton("&Filtrare dupa actor");
	QPushButton* btnundo = new QPushButton("&Undo");
	QPushButton* btncos = new QPushButton("&Cos");
	CosGUI cosgui{ cos };
	QListWidget* filter_layout = new QListWidget;
	QLineEdit* filter_titlu = new QLineEdit;

	void initGUI();
	void loadData(const vector<Film>& lista);
	void initConnect();
	void load_filter(const vector<Film>& lista);
};
