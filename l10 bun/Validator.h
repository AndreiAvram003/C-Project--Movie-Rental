
#include "Film.h"
class Valid_Error {
private:
	string msg;
public:
	Valid_Error(string msg) : msg{ msg } {

	}
	string get_msg() {
		return msg;
	}
};


class Validator {
public:
	void valideaza(const Film& film);
};

void teste_validator();
