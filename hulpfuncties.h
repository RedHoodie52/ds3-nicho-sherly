#ifndef HULPFUNCTIES_H
#define HULPFUNCTIES_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using Automaat = std::vector<std::vector<int>>;
// {fromState, symbol, toState1, toState2}

class parse{
    public:

        Automaat Expr(); // |
        Automaat Term(); // .
        Automaat Fact(); // *

        void callExpr(std::string formule);
        
        Automaat Concat(Automaat, Automaat);
        Automaat Star(Automaat);
        Automaat Union(Automaat, Automaat);

        void printDOT(const std::string& uitvoerNaam);
        void printHelpDOT(Automaat, std::ofstream&);

        void callMatch(std::string match);
        void findEpsilon(int path, std::vector<int>& bezocht);
        int findSymbol(int path, char symbol);
        


    private:
        std::string expressie;
        char huidigeLetter;
        int lengteExpressie, huidigpos, state, beginState;
        Automaat Aut;
        std::vector<std::pair<char, int[2]>> Automaton;
        std::vector<int> onthoudE; // onthouden van epsilon




};

#endif