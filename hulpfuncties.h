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

        void CallExpr(std::string formule);
        Automaat Concat(Automaat, Automaat);
        Automaat Star(Automaat);
        Automaat Union(Automaat, Automaat);
        void printAutomaat(Automaat& automaat) const;
        void printDOT(const std::string& uitvoerNaam);
        void printHelpDOT(Automaat, std::ofstream&);
        void callMatch(std::string match);
        bool calcMatch(std::string match);


    private:
        std::string expressie;
        char huidigeLetter;
        int lengteExpressie, huidigpos, state, beginState;
        Automaat Aut;
        std::vector<std::pair<char, int[2]>> Automaton;
        char currentSymbol;



};

#endif