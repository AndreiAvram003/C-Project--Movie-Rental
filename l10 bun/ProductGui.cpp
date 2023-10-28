#include "ProductGui.h";
void gui::initGUI() {
	QHBoxLayout* lymain = new QHBoxLayout{};
	setLayout(lymain);
	lst->setModel(model);
	QVBoxLayout* s1 = new QVBoxLayout;
	QVBoxLayout* s2 = new QVBoxLayout;
	QVBoxLayout* sf = new QVBoxLayout;
	s1->addWidget(btnstit);
	s1->addWidget(btnstgen);
	s2->addWidget(btnstact);
	s2->addWidget(btnstan);
	s2->addWidget(btnexit);
	sf->addLayout(s1);
	sf->addLayout(s2);
	QVBoxLayout* sfl = new QVBoxLayout;
	sfl->addWidget(lst);
	lymain->addLayout(sfl);
	auto stgly = new QVBoxLayout;
	auto lybtn = new QVBoxLayout{};
	lybtn->addWidget(btnadd);
	lybtn->addWidget(btndel);
	lybtn->addWidget(btnmod);
	lybtn->addWidget(btnfilact);
	lybtn->addWidget(btnfiltit);
	lybtn->addWidget(btnundo);
	lybtn->addWidget(btncos);
	stgly->addLayout(lybtn);
	stgly->addLayout(sf);
	lymain->addLayout(stgly);

	/*auto filter_layout = new QFormLayout;
	filter_layout->addRow(btnfiltit);
	QHBoxLayout* filter_row = new QHBoxLayout{};
	filter_row->addWidget(new QLabel("Titlu"));
	filter_row->addWidget(filter_titlu);*/


	unordered_map<string, int> raport = serv.get_all_gens();
	auto stgly2 = new QVBoxLayout;
	auto lybtns = new QVBoxLayout{};
	for (const auto& a : raport) {
		QPushButton* btngen = new QPushButton(QString::fromStdString(a.first));
		lybtns->addWidget(btngen);
		string x = std::to_string(a.second);
		QString y = QString::fromStdString(x);
		QObject::connect(btngen, &QPushButton::clicked, [y]() {
			QMessageBox::information(nullptr, "Count", y);
			});
	}
	stgly2->addLayout(lybtns);
	//stgly2->addLayout(filter_layout);
	lymain->addLayout(stgly2);
}


void gui::load_filter(const vector<Film>& lista)
{
	filter_layout->clear();
	for (const auto& film : lista)
	{
		QListWidgetItem* item = new QListWidgetItem();
		string text = to_string(film.get_id()) + " " + film.get_titlu() + " " + film.get_gen() + " " + film.get_actor()+" "+to_string(film.get_an());
		item->setText(QString::fromStdString(text));
		filter_layout->addItem(item);
	}
}





void gui::loadData(const vector<Film>& lista) {
	model->setProduct(lista);
}

void gui::initConnect() {
	QObject::connect(btnexit, &QPushButton::clicked, [&]() {
		QMessageBox::information(nullptr, "Info", "Exit buton apasat!");
		close();
		});

	QObject::connect(btncos, &QPushButton::clicked, [&]() {
		CosGUI* cosg = new CosGUI(cos);
		cosg->show();
		});
	QObject::connect(btnadd, &QPushButton::clicked, [&]() {
		QDialog* addWind = new QDialog();
		addWind->setWindowTitle("Adauga Film");
		QVBoxLayout* mly = new QVBoxLayout(addWind);
		addWind->setLayout(mly);
		auto formly = new QFormLayout;
		QLineEdit* idEdit = new QLineEdit;
		QLineEdit* titluEdit = new QLineEdit;
		QLineEdit* actorEdit = new QLineEdit;
		QLineEdit* genEdit = new QLineEdit;
		QLineEdit* anEdit = new QLineEdit;
		formly->addRow("Id", idEdit);
		formly->addRow("Titlu", titluEdit);
		formly->addRow("Actor", actorEdit);
		formly->addRow("gen", genEdit);
		formly->addRow("an", anEdit);
		auto btl = new QVBoxLayout;
		QPushButton* addBtn = new QPushButton("&Adauga!");
		QPushButton* cancelBtn = new QPushButton("&Anuleaza!");
		btl->addWidget(addBtn);
		btl->addWidget(cancelBtn);
		QObject::connect(addBtn, &QPushButton::clicked, [&]() {
			int id = idEdit->text().toInt();
			std::string titlu = titluEdit->text().toStdString();
			std::string actor = actorEdit->text().toStdString();
			std::string gen = genEdit->text().toStdString();
			int an = anEdit->text().toInt();
			try {
				serv.add(id, titlu, actor, gen, an);
				loadData(serv.get_all());
			}
			catch (Repo_Exception&) {
				QMessageBox::information(nullptr, "Info", "Film deja existent");
			}
			catch (Valid_Error& x) {
				stringstream os;
				os << x.get_msg();
				QMessageBox::information(nullptr, "Info", QString::fromStdString(os.str()));
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
	QObject::connect(btndel, &QPushButton::clicked, [&]() {
		QDialog* addWind = new QDialog();
		addWind->setWindowTitle("Sterge Film");
		QVBoxLayout* mly = new QVBoxLayout(addWind);
		addWind->setLayout(mly);
		auto formly = new QFormLayout;
		QLineEdit* idEdit = new QLineEdit;
		formly->addRow("Id-ul filmului dorit sters", idEdit);
		auto btl = new QVBoxLayout;
		QPushButton* delBtn = new QPushButton("&Sterge!");
		QPushButton* cancelBtn = new QPushButton("&Anuleaza!");
		btl->addWidget(delBtn);
		btl->addWidget(cancelBtn);
		QObject::connect(delBtn, &QPushButton::clicked, [&]() {
			int id = idEdit->text().toInt();
			try {
				serv.sterge(id);
				loadData(serv.get_all());
			}
			catch (Repo_Exception&) {
				QMessageBox::information(nullptr, "Info", "Film inexistent");
			}
			catch (Valid_Error& x) {
				stringstream os;
				os << x.get_msg();
				QMessageBox::information(nullptr, "Info", QString::fromStdString(os.str()));
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
	QObject::connect(btnmod, &QPushButton::clicked, [&]() {
		auto formly = new QFormLayout;
		QLineEdit* idEdit = new QLineEdit;
		QLineEdit* titluEdit = new QLineEdit;
		QLineEdit* actorEdit = new QLineEdit;
		QLineEdit* genEdit = new QLineEdit;
		QLineEdit* anEdit = new QLineEdit;
		QDialog* addWind = new QDialog();
		addWind->setWindowTitle("Modifica Activitate");
		QVBoxLayout* mly = new QVBoxLayout(addWind);
		addWind->setLayout(mly);

		formly->addRow("ID", idEdit);
		formly->addRow("Titlu nou", titluEdit);
		formly->addRow("Actor nou", actorEdit);
		formly->addRow("Gen nou", genEdit);
		formly->addRow("An nou", anEdit);
		auto btl = new QVBoxLayout;
		QPushButton* addBtn = new QPushButton("&Modifica!");
		QPushButton* cancelBtn = new QPushButton("&Anuleaza!");
		btl->addWidget(addBtn);
		btl->addWidget(cancelBtn);
		QObject::connect(addBtn, &QPushButton::clicked, [&]() {
			int id = idEdit->text().toInt();
			std::string titlu = titluEdit->text().toStdString();
			std::string actor = actorEdit->text().toStdString();
			std::string gen = genEdit->text().toStdString();
			int an = anEdit->text().toInt();
			try {
				serv.modifica(id, titlu, actor, gen, an);

				loadData(serv.get_all());
			}
			catch (Repo_Exception& x) {
				stringstream os;
				os << x.get_msg();
				QMessageBox::information(nullptr, "Info", QString::fromStdString(os.str()));
			}
			catch (Valid_Error& x) {
				stringstream os;
				os << x.get_msg();
				QMessageBox::information(nullptr, "Info", QString::fromStdString(os.str()));
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
	QObject::connect(btnstit, &QPushButton::clicked, [&]() {
		auto Compare_Titlu = [](Film a, Film b) {return a.get_titlu() < b.get_titlu(); };
		loadData(serv.sorteaza(Compare_Titlu));
		});
	QObject::connect(btnstgen, &QPushButton::clicked, [&]() {
		auto Compare_Gen = [](Film a, Film b) {return a.get_gen() > b.get_gen(); };
		loadData(serv.sorteaza(Compare_Gen));
		});
	QObject::connect(btnstan, &QPushButton::clicked, [&]() {
		auto Compare_An = [](Film a, Film b) {return a.get_an() < b.get_an(); };
		loadData(serv.sorteaza(Compare_An));
		});
	QObject::connect(btnstact, &QPushButton::clicked, [&]() {
		auto Compare_Actor = [](Film a, Film b) {return a.get_actor() < b.get_actor(); };
		loadData(serv.sorteaza(Compare_Actor));
		});

	QObject::connect(btnundo, &QPushButton::clicked, [&]() {
		try {
			serv.Undo();
			loadData(serv.get_all());
		}
		catch (Repo_Exception&) {
			QMessageBox::information(nullptr, "Info", "Nu mai avem undo");
		}
		});



	QObject::connect(btnfiltit, &QPushButton::clicked, [&]() {
		QDialog* addWind = new QDialog();
		addWind->setWindowTitle("Filtru");
		QVBoxLayout* mly = new QVBoxLayout(addWind);
		addWind->setLayout(mly);
		auto formly = new QFormLayout;
		QLineEdit* titluEdit = new QLineEdit;
		formly->addRow("Titlu", titluEdit);
		QVBoxLayout* btl = new QVBoxLayout;
		QPushButton* filBtn = new QPushButton("&Filtreaza!");
		QPushButton* cancelBtn = new QPushButton("&Inchide!");
		btl->addWidget(filBtn);
		btl->addWidget(cancelBtn);
		mly->addLayout(formly);
		mly->addLayout(btl);
		QObject::connect(filBtn, &QPushButton::clicked, [&]() {
			std::string ti = titluEdit->text().toStdString();
			vector<Film>fil = serv.filtrare_t(ti);
			vector<Film>all = serv.get_all();
			loadData(fil);
			});
		addWind->exec();
		});


		QObject::connect(btnfilact, &QPushButton::clicked, [&]() {
			QDialog* addWind = new QDialog();
			addWind->setWindowTitle("Filtru");
			QVBoxLayout* mly = new QVBoxLayout(addWind);
			addWind->setLayout(mly);
			auto formly = new QFormLayout;
			QLineEdit* actEdit = new QLineEdit;
			formly->addRow("Actor", actEdit);
			QVBoxLayout* btl = new QVBoxLayout;
			QPushButton* filBtn = new QPushButton("&Filtreaza!");
			QPushButton* cancelBtn = new QPushButton("&Inchide!");
			btl->addWidget(filBtn);
			btl->addWidget(cancelBtn);
			mly->addLayout(formly);
			mly->addLayout(btl);
			QObject::connect(filBtn, &QPushButton::clicked, [&]() {
				std::string act = actEdit->text().toStdString();
				vector<Film>fil = serv.filtrare_a(act);
				vector<Film>all = serv.get_all();
				loadData(fil);

				});
			addWind->exec();
			});
}