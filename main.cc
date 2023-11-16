#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "hulpfuncties.h"


int main(int argc, char** argv) {
    bool debugMode = false;
    std::string filename;

    if (argc >= 2) {
        if (std::string(argv[1]) == "<"){
            debugMode = true;
            if (argc >= 3){
                filename = argv[2];
            }
            std::cout<<"debugMode ingeschakeld"<<std::endl;
        }
        
    }

    std::ifstream file;
    if (!filename.empty()){
        file.open(filename);
        if (!file.is_open()){
            std::cerr << "Bestand niet gevonden: " << filename << std::endl;
            return 1;
        }
    }

    bool menu = true;
    std::string keuze;
    parse exp;


    while (menu) {
        if (!debugMode) {
            std::cout << std::endl
            << "Kies een optie:" << std::endl
            << "* exp <expressie>" << std::endl
            << "* dot <bestandsnaam>" << std::endl
            << "* mat <string>" << std::endl
            << "* end " << std::endl
            << std::endl;
        }

        std::string line;

        if (file.is_open() && std::getline(file, line)){
            keuze = line;
        } else{
            std::getline(std::cin, keuze);
        }
        
        
        if (keuze.substr(0, 4) == "exp ") {
            std::string formule = keuze.substr(4);
            exp.CallExpr(formule);

        } else if (keuze.substr(0, 4) == "dot ") {
            std::string uitvoer = keuze.substr(4);

        } else if (keuze.substr(0, 4) == "mat ") {
            std::string uitvoer = keuze.substr(4);
            std::cout<< "dit is deel 2" << std::endl;
        } else if (keuze == "end") {
            menu = false;
        } else {
            std::cout << "Ongeldige instructie, probeer nog eens." << std::endl;
        }
    }

    if (file.is_open()) {
        file.close();
    }

    return 0;
}