#pragma once
#ifndef FILM
#define FILM
#include <string>
#include<iostream>
using std::cout;
using std::string;
using std::to_string;

class Film {
private:
	int id;
	string titlu;
	string gen;
	string actor;
	int an;
public:
	int get_id() const noexcept;
	string get_titlu() const;
	string get_actor() const;
	string get_gen() const;
	int get_an() const noexcept;
	Film(int id, string titlu, string gen, string actor, int an) :id{ id }, titlu{ titlu }, gen{ gen }, actor{ actor }, an{ an } {}
	string get_string() const;
	Film(const Film& film) :id{ film.id }, titlu{ film.titlu }, actor{ film.actor }, gen{ film.gen }, an{ film.an } {
	}
};

void teste_domain();
#endif
