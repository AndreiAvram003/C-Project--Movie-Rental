#include "CosGui.h"
#include "CosGUIRead.h"

void CosGUI::loadDataCos() {
	lstcos->clear();
	auto all = cos.get_all();
	for (const auto& a : all) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(a.get_string()));
		lstcos->addItem(item);
	}
}

void CosGUI::update() {
	loadDataCos();
}
void CosGUI::initGUICos() {
	QHBoxLayout* lymaincos = new QHBoxLayout{};
	setLayout(lymaincos);
	QVBoxLayout* sfcos = new QVBoxLayout;
	QVBoxLayout* sflcos = new QVBoxLayout;
	sflcos->addWidget(lstcos);
	lymaincos->addLayout(sflcos);
	auto stgly = new QVBoxLayout;
	auto lybtn = new QVBoxLayout{};
	lybtn->addWidget(btnaddcos);
	lybtn->addWidget(btnrandcos);
	lybtn->addWidget(btngoleste);
	lybtn->addWidget(btnexporta);
	lybtn->addWidget(btnpaint);
	stgly->addLayout(lybtn);
	stgly->addLayout(sfcos);
	lymaincos->addLayout(stgly);
}


void CosGUI::initConnectCos() {
	QObject::connect(btnaddcos, &QPushButton::clicked, [&]() {
		QDialog* addWind = new QDialog();
		addWind->setWindowTitle("Adauga Film");
		QVBoxLayout* mly = new QVBoxLayout(addWind);
		addWind->setLayout(mly);
		auto formly = new QFormLayout;
		QLineEdit* idEdit = new QLineEdit;
		formly->addRow("Id-ul filmului dorit adaugat", idEdit);
		auto btl = new QVBoxLayout;
		QPushButton* addBtn = new QPushButton("&Adauga!");
		QPushButton* cancelBtn = new QPushButton("&Anuleaza!");
		btl->addWidget(addBtn);
		btl->addWidget(cancelBtn);
		QObject::connect(addBtn, &QPushButton::clicked, [&]() {
			int id = idEdit->text().toInt();
			try {
				cos.adauga_cos(id);
				loadDataCos();
			}
			catch (Repo_Exception&) {
				QMessageBox::information(nullptr, "Info", "Film inexistent");
			}
			addWind->close();
			});
		QObject::connect(cancelBtn, &QPushButton::clicked, [&]() {
			addWind->close();
			});
		mly->addLayout(formly);
		mly->addLayout(btl);
		addWind->exec();
		});



	QObject::connect(btnrandcos, &QPushButton::clicked, [&]() {
		QDialog* addWind = new QDialog();
		addWind->setWindowTitle("Adauga Filme Random");
		QVBoxLayout* mly = new QVBoxLayout(addWind);
		addWind->setLayout(mly);
		auto formly = new QFormLayout;
		QLineEdit* idEdit = new QLineEdit;
		formly->addRow("Numarul de filme", idEdit);
		auto btl = new QVBoxLayout;
		QPushButton* addBtn = new QPushButton("&Adauga!");
		QPushButton* cancelBtn = new QPushButton("&Anuleaza!");
		btl->addWidget(addBtn);
		btl->addWidget(cancelBtn);
		QObject::connect(addBtn, &QPushButton::clicked, [&]() {
			int n = idEdit->text().toInt();
				cos.random(n);
				loadDataCos();
			addWind->close();
			});
		QObject::connect(cancelBtn, &QPushButton::clicked, [&]() {
			addWind->close();
			});
		mly->addLayout(formly);
		mly->addLayout(btl);
		addWind->exec();
		});


	QObject::connect(btngoleste, &QPushButton::clicked, [&]() {
		lstcos->clear();
		});
	QObject::connect(btnpaint, &QPushButton::clicked, [&]() {
		CartCRUDRead* paint = new CartCRUDRead(cos);
		paint->show();
		});

	QObject::connect(btnexporta, &QPushButton::clicked, [&]() {
		cos.exporta();
		});

}
