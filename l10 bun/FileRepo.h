#pragma once
#include "Repo.h"
#include<fstream>
#include<iostream>
class FileRepo : public Repo {
private:
	std::fstream f;
	string file_name;
	void read_all_from_file();
	void write_all_to_file();
public:
	FileRepo(string file_name) : file_name{ file_name } {
		read_all_from_file();
	};
	void adauga_film(const Film& film) override;
	void sterge_film(int id) override;
	void modifica_film(const Film& film) override;
};

void FileRepo::adauga_film(const Film& film) {
	Repo::adauga_film(film);
	write_all_to_file();
}
void FileRepo::sterge_film(int id) {
	Repo::sterge_film(id);
	write_all_to_file();
}
void FileRepo::modifica_film(const Film& film) {
	Repo::modifica_film(film);
	write_all_to_file();
}

void FileRepo::write_all_to_file() {
	f.open(file_name, std::ios::out);
	for (const Film& fi : filme) {
		f << fi.get_id() << " " << fi.get_titlu() << " " << fi.get_actor() << " " << fi.get_gen() << " " << fi.get_an() << "\n";
	}
	f.close();
}

void FileRepo::read_all_from_file() {
	f.open(file_name, std::ios::in);
	int id;
	string titlu;
	string actor;
	string gen;
	int an;
	while (f >> id >> titlu >> actor >> gen >> an) {
		Film f(id, titlu, actor, gen, an);
		filme.push_back(f);
	}
	f.close();
}