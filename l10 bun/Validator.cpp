#include "Validator.h"
#include <stdexcept>
#include <assert.h>

void Validator::valideaza(const Film& film) {
	string erori = "";
	if (film.get_id() <= 0)
		erori += "Id invalid\n";

	if (film.get_titlu() == "")
		erori += "Titlu invalid\n";

	if (film.get_gen() == "")
		erori += "Gen invalid\n";
	if (film.get_actor() == "")
		erori += "Actor invalid\n";

	if (film.get_an() <= 0)
		erori += "An invalid\n";

	if (erori != "")
		throw Valid_Error{ erori };

}

void teste_validator() {
	Film film1{ 1,"Scufita Rosie","Frati Grimm","Basm",1950 };
	Film film_nou{ 1,"Scufita bRosie","Frati bGrimm","bBasm",1920 };
	Film film_gresit{ 0,"Scufita Rosie","Frati Grimm","Basm",1950 };
	Film film_gresit1{ 1,"","Frati Grimm","Basm",1950 };
	Film film_gresit2{ 1,"a","","Basm",1950 };
	Film film_gresit3{ 1,"v","Frati Grimm","",1950 };
	Film film_gresit4{ 1,"l","Frati Grimm","Basm",0 };
	Validator v;
	try {
		v.valideaza(film_gresit);
	}
	catch (Valid_Error& e) {
		assert(e.get_msg() == "Id invalid\n");
	}
	try {
		v.valideaza(film_gresit1);
	}
	catch (Valid_Error& e) {
		assert(e.get_msg() == "Titlu invalid\n");
	}
	try {
		v.valideaza(film_gresit2);
	}
	catch (Valid_Error& e) {
		assert(e.get_msg() == "Gen invalid\n");
	}
	try {
		v.valideaza(film_gresit3);
	}
	catch (Valid_Error& e) {
		assert(e.get_msg() == "Actor invalid\n");
	}
	try {
		v.valideaza(film_gresit4);
	}
	catch (Valid_Error& e) {
		assert(e.get_msg() == "An invalid\n");
	}
}