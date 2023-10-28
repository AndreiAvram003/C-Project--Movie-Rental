#include "Repo.h"
#include <assert.h>



void Repo::adauga_film(const Film& film) {
	for (const Film& f : filme)
		if (f.get_id() == film.get_id()) {
			throw Repo_Exception("Film deja existent");
		}
	filme.push_back(film);
}

void Repo::sterge_film(int id) {
	int poz = -1;
	int ok = 0;
	for (const Film& f : filme) {
		poz++;
		if (f.get_id() == id) {
			ok = 1;
			break;
		}
	}
	if (ok == 0) {
		throw Repo_Exception("Film inexistent");
	}

	filme.erase(filme.begin() + poz);
}

const Film& Repo::cauta_film(int id) {
	for (const Film& f : filme) {
		if (f.get_id() == id)
			return f;
	}
	throw Repo_Exception("Film inexistent");
}

void Repo::modifica_film(const Film& film) {

	for (Film& f : filme) {
		if (f.get_id() == film.get_id()) {
			f = film;
			return;
		}
	}
	throw Repo_Exception("Film inexistent");
}

const vector<Film>& Repo::get_all() {
	return filme;

}

void teste_repo() {
	Repo filme;
	Film film{ 1,"Scufita Rosie","Frati Grimm","Basm",1950 };
	Film film_nou{ 1,"Scufita bRosie","Frati bGrimm","bBasm",1920 };
	Film film_gresit{ 2,"Scufita Rosie","Frati Grimm","Basm",1950 };
	filme.adauga_film(film);
	const auto& films = filme.get_all();
	assert(films.size() == 1);
	try {
		filme.adauga_film(film);
	}
	catch (Repo_Exception& e) {
		assert(true);
		assert(e.get_msg() == "Film deja existent");
	}
	filme.modifica_film(film_nou);
	assert(films[0].get_an() == 1920);
	try {
		filme.modifica_film(film_gresit);
	}
	catch (Repo_Exception& e) {
		assert(true);
		assert(e.get_msg() == "Film inexistent");
	}
	try {
		filme.sterge_film(2);
	}
	catch (Repo_Exception& e) {
		assert(true);
		assert(e.get_msg() == "Film inexistent");
	}
	filme.sterge_film(1);
	assert(films.size() == 0);



}
