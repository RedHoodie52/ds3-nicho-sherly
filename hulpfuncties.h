// #ifndef HULPFUNCTIES_H
// #define HULPFUNCTIES_H

// #include <iostream>
// #include <vector>
// #include <array>

// // struct Automaat{
// //     enum{
// //         PLUS,
// //         TIMES,
// //         VARIABLE
// //     } type;


// //     char variable;
// //     Automaat* links;
// //     Automaat* rechts;
    
// //     Automaat(int _type, Automaat* _links, Automaat* _rechts):type(_type), 
// //                 variable('$'), links(_links), rechts(_rechts) {}

// //     Automaat(){
// //         type = Automaat::VARIABLE;
// //         variable = '$';
// //         links = nullptr;
// //         rechts = nullptr;
// //     }

// // };

// using Automaat = std::vector<std::array<int, 4>>;

// class parse{
//     public:

//         parse(){
//             huidigeLetter = ' ';
//             lengteExpressie = 0;
//             huidigpos = 0;
//             state = 1;
//         }
//         Automaat Expr(); // |
//         Automaat Term(); // .
//         Automaat Fact(); // *
        
//         void CallExpr(std::string formule);
//         void printAutomaat(Automaat);
//         Automaat Concat(Automaat, Automaat);
//         Automaat Star(Automaat);
//         Automaat Union(Automaat, Automaat);


        

//     private:
//         std::string expressie;
//         char huidigeLetter;
//         int lengteExpressie, huidigpos, state;
//         Automaat Aut;
//         // std::vector<std::pair<char, int[2]>> Automaton;



// };

// #endif

#ifndef HULPFUNCTIES_H
#define HULPFUNCTIES_H

#include <iostream>
#include <vector>
#include <array>

// struct Automaat{
//     enum{
//         PLUS,
//         TIMES,
//         VARIABLE
//     } type;


//     char variable;
//     Automaat* links;
//     Automaat* rechts;

//     Automaat(int _type, Automaat* _links, Automaat* _rechts):type(_type), 
//                 variable('$'), links(_links), rechts(_rechts) {}

//     Automaat(){
//         type = Automaat::VARIABLE;
//         variable = '$';
//         links = nullptr;
//         rechts = nullptr;
//     }

// };

using Automaat = std::vector<std::array<int, 4>>;
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
        void printAutomaat(const Automaat& automaat) const;




    private:
        std::string expressie;
        char huidigeLetter;
        int lengteExpressie, huidigpos, state;
        Automaat Aut;
        std::vector<std::pair<char, int[2]>> Automaton;



};

#endif