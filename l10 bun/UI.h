
#include "Service.h"
class UI {
	Service serv;
	Cos cos;
public:
	UI(Service serv, Cos cos) :serv{ serv }, cos{ cos } {};
	void start_UI();
	void afisare_cos();
};
