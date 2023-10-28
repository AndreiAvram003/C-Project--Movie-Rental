#include "Film.h"
#include <assert.h>
int Film::get_id() const noexcept {
	return id;
}

string Film::get_actor() const {
	return actor;
}
string Film::get_gen()const {
	return gen;
}
string Film::get_titlu() const {
	return titlu;
}
int Film::get_an() const noexcept {
	return an;
}

string Film::get_string()const {
	string f;
	f += "ID-ul: " + to_string(id);
	f += " ";
	f = f + "Titlul: " + titlu;
	f += " ";
	f += "Genul: " + gen;
	f += " ";
	f += "Actorul: " + actor;
	f += " ";
	f += "An: " + to_string(an);
	f += "\n";
	return f;
}

void teste_domain() {
	Film f{ 1,"Ion","Ioana","Ionica",1920 };
	assert(f.get_id() == 1);
	assert(f.get_titlu() == "Ion");
	assert(f.get_gen() == "Ioana");
	assert(f.get_actor() == "Ionica");
	assert(f.get_an() == 1920);
	assert(f.get_string() == "ID-ul: 1 Titlul: Ion Genul: Ioana Actorul: Ionica An: 1920\n");
}