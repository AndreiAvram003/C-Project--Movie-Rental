#ifndef SERVICE
#define SERVICE
#include <string>
#include "Repo.h"
#include "Validator.h"
#include <functional>
#include <unordered_map>
#include "observable.h"
using std::unordered_map;
using std::string;
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	ActiuneUndo() = default;
};
class Service {
	Repo& filme;
	Validator valid;
	vector<ActiuneUndo*> comenzi;
	void add_comanda(ActiuneUndo* com);
public:
	Service(Repo& filme, Validator valid) : filme{ filme }, valid{ valid } {

	}
	void add(int id, string titlu, string gen, string actor, int an);
	const vector<Film>& get_all();
	void sterge(int id);
	void modifica(int id, string titlu, string gen, string actor, int an);
	vector<Film> sorteaza(std::function<bool(Film a, Film b)>Compare);
	
	unordered_map<string, int> get_all_gens();
	vector<Film>filtrare_t(string titlu);
	vector<Film>filtrare_a(string actor);
	Film cauta(int id);
	bool Undo();
};


class UndoAdauga :public ActiuneUndo {
private:
	Repo& filme;
	Film f;
public:
	void doUndo() override;
	UndoAdauga(Repo& filme, Film& f) :filme{ filme }, f{ f } {};
};

class UndoSterge :public ActiuneUndo {
private:
	Repo& filme;
	Film f;
public:
	void doUndo() override;
	UndoSterge(Repo& filme, Film f) :filme{ filme }, f{ f } {};
};

class UndoModifica :public ActiuneUndo {
private:
	Repo& filme;
	Film f;
	Film f_vechi;
public:
	void doUndo() override;
	UndoModifica(Repo& filme, Film& f, Film& f_vechi) :filme{ filme }, f{ f }, f_vechi{ f_vechi } {};
};

void teste_service();

class Cos : public Observable{
private:
	Repo& filme;
	vector<Film> cos;
public:
	Cos(Repo& filme) : filme{ filme } {}
	void adauga_cos(int id);
	void goleste_cos();
	void exporta();
	const vector<Film>& get_all();
	void random(int n);
};
#endif