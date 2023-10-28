#include "Service.h"
#include <assert.h>
#include<fstream>
#include<algorithm>
#include<iostream>
#include<chrono>
#include<QDebug>
std::ifstream fi("cos.txt");
std::ofstream fo("cosGUI.txt");
using std::sort;

void Service::add(int id, string titlu, string gen, string actor, int an) {
	Film film{ id,titlu,gen,actor,an };
	valid.valideaza(film);
	filme.adauga_film(film);
	add_comanda(new UndoAdauga(filme, film));
}

void Service::add_comanda(ActiuneUndo* com) {
	comenzi.push_back(com);
}
const vector<Film>& Service::get_all() {
	return filme.get_all();
}

void UndoAdauga::doUndo() {
	filme.sterge_film(f.get_id());
}

void UndoSterge::doUndo() {
	filme.adauga_film(f);
}

void UndoModifica::doUndo() {
	filme.modifica_film(f_vechi);
}

void Service::sterge(int id) {

	Film fi = filme.cauta_film(id);
	filme.sterge_film(id);
	add_comanda(new UndoSterge(filme, fi));
}

void Service::modifica(int id, string titlu_nou, string gen_nou, string actor_nou, int an_nou) {
	Film film_nou{ id,titlu_nou,gen_nou,actor_nou,an_nou };
	Film f = filme.cauta_film(id);
	filme.modifica_film(film_nou);
	add_comanda(new UndoModifica(filme, film_nou, f));
}
bool Service::Undo() {
	if (comenzi.size() == 0)
		return false;
	ActiuneUndo* comanda = comenzi.back();
	comanda->doUndo();
	comenzi.pop_back();
	delete comanda;
	return true;


}

void Cos::adauga_cos(int id) {
	const vector<Film> films = filme.get_all();
	for (const Film v : films) {
		if (v.get_id() == id) {
			cos.push_back(v);
			notify();
			return;
		}
	}

	throw Repo_Exception("Nu exista acest film");
}

void Cos::goleste_cos() {
	cos.clear();
	notify();
}

const vector<Film>& Cos::get_all() {
	return cos;
}
void Cos::exporta() {
	for (const Film v : cos) {
		fo << v.get_string() << "\n";
	}
}
vector<Film> Service::sorteaza(std::function<bool(Film a, Film b)>Compare) {
	vector<Film> v = filme.get_all();
	sort(v.begin(), v.end(), Compare);
	return v;

}
vector<Film>Service::filtrare_t(string titlu) {
	vector<Film>v = filme.get_all();
	vector<Film>l;
	for (const auto& a : v) {
		if (a.get_titlu() == titlu)
			l.push_back(a);
			
	}
	return l;
}
vector<Film>Service::filtrare_a(string actor) {
	vector<Film>v = filme.get_all();
	vector<Film>l;
	for (const auto& a : v) {
		if (a.get_actor() == actor)
			l.push_back(a);

	}
	return l;
}

void Cos::random(int n) {
	vector<Film> v = filme.get_all();
	//std::random_shuffle(v.begin(), v.end());
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));
	for (int i = 0; i <= n - 1; i++) {
		cos.push_back(v[i]);

	}
	notify();
}


unordered_map<string,int> Service::get_all_gens() {
	vector<Film> v = filme.get_all();
	unordered_map<string, int> genuri;
	for (const Film& film : v) {
		string gen = film.get_gen();
		genuri[gen] = 0;
	}
	for (const Film& film : v) {
		string gen = film.get_gen();
		genuri[gen]++;
	}
	return genuri;
}

void teste_service() {
	Repo filme;
	Validator valid;
	Service film{ filme,valid };
	film.add(1, "Scufita Rosie", "Frati Grimm", "Basm", 1950);
	if (film.Undo() == true) {
		const auto& films = film.get_all();
		assert(films.size() == 0);
	}
	const auto& films = film.get_all();
	film.add(1, "Scufita Rosie", "Frati Grimm", "Basm", 1950);
	film.sterge(1);
	if (film.Undo() == true) {
		assert(films.size() == 1);
	}
	film.modifica(1, "Ion", "Ioana", "Ionica", 102);
	if (film.Undo() == true) {
		assert(films[0].get_an() == 1950);
	}
	film.add(2, "Hapciu", "Hapciu", "Hapciu", 103);
	auto Compare_Titlu = [](Film a, Film b) {return a.get_titlu() < b.get_titlu(); };
	vector<Film> v = film.sorteaza(Compare_Titlu);
	assert(v[0].get_titlu() == "Hapciu");
	Cos filmute{ filme };
	filmute.adauga_cos(1);
	const auto& filmee = filmute.get_all();
	assert(filmee.size() == 1);
	try {
		filmute.adauga_cos(5);
	}
	catch (Repo_Exception& e) {
		assert(e.get_msg() == "Nu exista acest film");
	}
	film.add(3, "Hapciu", "Hapciu", "Hapciuasd", 1103);
	filmute.goleste_cos();
	assert(filmee.size() == 0);
	filmute.random(3);
	const auto& teste = filmute.get_all();
	assert(teste.size() == 3);
	filmute.exporta();
	char j;
	fi >> j;
	filmute.goleste_cos();

}
