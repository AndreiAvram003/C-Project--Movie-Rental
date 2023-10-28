#include<iostream>
#include "UI.h"
using std::cin;
using std::cout;
using std::string;
void UI::afisare_cos() {
	const vector<Film>& cos_filme = cos.get_all();
	for (const Film v : cos_filme) {
		cout << v.get_string() << "\n";
	}
	if (cos_filme.size() == 0) {
		cout << "Nu exista filme in cos\n";
	}
}
void UI::start_UI() {
	while (true) {
		cout << "0.Exit \n1.Adauga film: \n2.Afiseaza filme \n3.Sterge film \n4.Modifica film \n5.Afiseaza filme care au un anumit an\n6.Sorteaza filme dupa titlu \n7.Afiseaza cosul de inchirieri \n8.Adauga film in cos \n9.Goleste cosul \n10.Exporta cosul intr-un fisier \n11.Adauga filme random in cos \n12.Raport dupa titluri \n13.Undo\n";
		int cmd = 0;
		cin >> cmd;
		if (cmd == 0) {
			break;
		}
		if (cmd == 1) {
			int id;
			string titlu;
			string gen;
			string autor;
			int an;
			cout << "Introduceti id-ul: ";
			cin >> id;
			cout << "\n";
			cout << "Introduceti titlul: ";
			cin >> titlu;
			cout << "\n";
			cout << "Introduceti genul: ";
			cin >> gen;
			cout << "Introduceti autorul: ";
			cin >> autor;
			cout << "\n";
			cout << "Introduceti anul: ";
			cin >> an;
			cout << "\n";
			try {
				serv.add(id, titlu, gen, autor, an);
				cout << "Film adaugat cu succes \n";
			}
			catch (Repo_Exception& ex) {
				cout << ex.get_msg();
			}
			catch (Valid_Error& e) {
				cout << e.get_msg();
			}

		}
		if (cmd == 2) {
			vector<Film> filme = serv.get_all();
			for (const auto& f : filme) {
				cout << f.get_string();
			}
		}
		if (cmd == 3) {
			int id;
			cout << "Alegeti id-ul filmului dorit sa stergeti: ";
			cin >> id;
			cout << "\n";
			serv.sterge(id);
			cout << "Film sters cu succes\n";
		}
		if (cmd == 4) {
			int id;
			string titlu, actor, gen;
			int an;
			cout << "Alegeti id-ul filmului dorit modificat: ";
			cin >> id;
			cout << "\nTitlu nou: ";
			cin >> titlu;
			cout << "Gen nou: ";
			cin >> gen;
			cout << "Actor nou: ";
			cin >> actor;
			cout << "An nou: ";
			cin >> an;
			serv.modifica(id, titlu, gen, actor, an);
			cout << "Film modificat cu succes\n";
		}
		if (cmd == 5) {
			int an;
			cout << "Alegeti anul dupa care cautati filmele: ";
			cin >> an;
			vector<Film> filme = serv.get_all();
			for (Film f : filme) {
				if (f.get_an() == an)
					cout << f.get_string();
			}
		}
		if (cmd == 6) {
			auto Compare_Titlu = [](Film a, Film b) {return a.get_titlu() < b.get_titlu(); };
			vector<Film> v = serv.sorteaza(Compare_Titlu);
			for (int i = 0; i < v.size(); i++)
				cout << v[i].get_string() << " ";
		}
		if (cmd == 7) {
			afisare_cos();
		}
		if (cmd == 8) {
			int id;
			cout << "Alegeti id-ul filmului pe care doriti sa il adaugati: ";
			cin >> id;
			cout << "\n";
			vector<Film> filme = serv.get_all();
			for (Film f : filme) {
				if (f.get_id() == id) {
					try {
						cos.adauga_cos(id);
						cout << "Film adaugat cu succes \n";
					}
					catch (Repo_Exception& ex) {
						cout << ex.get_msg();
					}
				}
			}
			cout << "\n";
			afisare_cos();
		}

		if (cmd == 9) {
			cos.goleste_cos();
			cout << "\n";
			afisare_cos();
		}
		if (cmd == 10) {
			cos.exporta();
		}
		if (cmd == 11) {
			int n;
			cout << "Alegeti cate filme doriti sa adaugati: ";
			cin >> n;
			cout << "\n";
			cos.random(n);
			afisare_cos();
		}

		if (cmd == 12) {
			unordered_map<string, vector<Film>> raport = serv.get_all_titluri();
			for (const auto& pair : raport) {
				string attribute = pair.first;
				cout << "--- " << attribute << " filter ---\n";
				vector<Film> filme_filtrate = pair.second;
				cout << "Toate filmele cu actorul  " << attribute << " sunt: \n";
				for (const auto& film : filme_filtrate) {
					cout << film.get_string();
				}
				cout << "\n";
			}
		}
		if (cmd == 13) {
			if (serv.Undo() == false)
				cout << "Nu avem pe ce face undo";
			else {
				cout << "Undo efectuat cu succes";
				cout << std::endl;
			}
		}
	}
}