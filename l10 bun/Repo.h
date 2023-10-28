#pragma once
#include<vector>
#include"Film.h"
#include<random>
using std::vector;
class Repo_Exception {
private:
	string msg;
public:
	Repo_Exception(string msg) : msg{ msg } {

	}
	string get_msg() {
		return msg;
	}
};





class Repo {
protected:
	vector<Film> filme;
public:
	Repo() {
	}
	virtual void adauga_film(const Film& film);
	virtual void sterge_film(int id);
	virtual void modifica_film(const Film& film);
	const vector<Film>& get_all();
	const Film& cauta_film(int id);
};


void teste_repo();



