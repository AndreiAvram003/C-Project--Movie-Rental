#include <stdlib.h>
#include <QtWidgets/QApplication>
#include <iostream>
#include "ProductGui.h"
#include "FileRepo.h"
#include "UI.h"
int main(int argc, char* argv[])
{
    teste_repo();
    teste_service();
    teste_validator();
    teste_domain();
    FileRepo repo("films.txt");
    Validator val;
    Service serv{ repo,val};
    Cos cos{ repo };
    QApplication a(argc, argv);
    gui guiPtr{serv,cos};
    guiPtr.show();
    return a.exec();
}