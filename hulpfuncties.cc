// #include <iostream>
// #include "hulpfuncties.h"

// bool isLetter(char letter){
//     if(letter >= 'a' || letter <= 'z'){
//         return true;
//     }

//     return false;
// }

// void parse::printAutomaat(Automaat eind){

//     for(const auto& array : eind){
//         for (int i = 0; i < lengteExpressie; i++) {
//             std::cout << array[i] << " ";
//         }
//         std::cout << std::endl;
//     }
    
// }

// void parse::CallExpr(std::string formule){
//     expressie = formule;
//     // expressie = "c(a|bb)*c";
//     lengteExpressie = expressie.size();
//     huidigpos = 0;
//     huidigeLetter = expressie[0]; 
//     Aut = Expr();
//     printAutomaat(Aut);

// }

// Automaat parse::Union(Automaat een, Automaat twee){
//     Automaat drie;

//     // drie.insert(een.end(), twee.begin(), twee.end());

//     return een;

// }

// Automaat parse::Expr(){
//     // Automaat Aut;
//     Automaat Aut1 = Term();
    
//     if (huidigeLetter == '|' ){ 
//         huidigpos++;
//         huidigeLetter = expressie[huidigpos]; // lees volgende letter
//         Automaat Aut2 = Expr(); // recursie!
//         Aut1 = Union(Aut1, Aut2);
//     }

//     return Aut1;// plus van Aut1 en Aut2;
// } // Expr

// Automaat parse::Concat(Automaat een, Automaat twee){
//     Automaat drie;

//     // drie.insert(een.end(), twee.begin(), twee.end());

//     return een;

// }

// Automaat parse::Term(){
//     Automaat Aut1 = Fact(); // 1 a 2 // 3 b 4 // 5 b 6
    
//     if (huidigeLetter == '(' || isLetter(huidigeLetter)){
//         Automaat Aut2 = Term(); // recursie!
//         Aut1 = Concat(Aut1, Aut2);
//     }

    
    
//     return Aut1; // concatenatie van Aut1 en Aut2;
// } // Term

// Automaat parse::Star(Automaat een){
//     // begin state is final state
//     // of 

//     return een;

// }


// Automaat parse::Fact(){
//     Automaat Aut1;

//     if (huidigeLetter == '('){ 
//         huidigpos++;
//         huidigeLetter = expressie[huidigpos]; // lees volgende letter
//         Aut1 = Expr();

//         if (huidigeLetter == ')'){
//             huidigpos++;
//             huidigeLetter = expressie[huidigpos]; // lees volgende letter
//         } else{
//             // error;
//         }
//     } else if(isLetter(huidigeLetter)){  // letter opslaan 
//         std::cout << "hallo" << std::endl;
//         Aut1.push_back({state, huidigeLetter, state+1, 0}); //tak met huidigeLetter;
//         state += 2;
//         huidigpos++;
//         if(huidigpos != lengteExpressie-1){
//             huidigeLetter = expressie[huidigpos]; // lees volgende letter
//         }
//     } else{
//         throw std::runtime_error("Value is in valid");
//     }

//     if (huidigeLetter == '*'){ // eventueel while?
//         Aut1 = Star(Aut1);
//         huidigpos++;
//         huidigeLetter = expressie[huidigpos]; // lees volgende letter
//         if(huidigpos != lengteExpressie-1){
//             huidigeLetter = expressie[huidigpos]; // lees volgende letter
//         }
//     }
    
//     return Aut1;
// } // Fact

#include <iostream>
#include "hulpfuncties.h"

bool isLetter(char letter){
    if(letter >= 'a' && letter <= 'z'){
        return true;
    }

    return false;
}

void parse::CallExpr(std::string formule){
    expressie = formule;
    lengteExpressie = expressie.size();
    huidigpos = 0;
    


    Automaat result = Expr();



    printAutomaat(result);


}

void parse::printAutomaat(const Automaat& automaat) const {
    std::cout << "From State\tSymbol\tTo State 1\tTo State 2" << std::endl;
    for (const auto& transition : automaat) {
        std::cout << transition[0] << "\t\t"
                  << transition[1] << "\t\t"
                  << transition[2] << "\t\t"
                  << transition[3] << std::endl;
    }
    std::cout << std::endl;
}

Automaat parse::Union(Automaat een, Automaat twee){
    std::cout<<"komt in UNION"<< std::endl;

    int startState = state++;
    int acceptState = state++;

    een.push_back({startState, '$', een.front()[0], twee.front()[0]}); // connect new startState to startState of een
    twee.push_back({startState, '$', twee.front()[0], 0}); // connect new startState to startState of twee

    een.push_back({een.back()[2], '$', acceptState, 0}); // connect new acceptingState to acceptingState of een
    twee.push_back({twee.back()[2], '$', acceptState, 0}); // connect new acceptingState to acceptingState of twee

    Automaat result = een;

    for (const auto& transition : twee){
        result.push_back(transition);
    }

return result;

}

Automaat parse::Expr(){
    std::cout<<"komt in EXPR"<< std::endl;
    // Automaat Aut;
    Automaat Aut1 = Term();
    
    if (huidigeLetter == '|' ){ 
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
        Automaat Aut2 = Expr(); // recursie!

        Aut1 = Union(Aut1, Aut2);
    }


    return Aut1;// union van Aut1 en Aut2;
} // Expr

Automaat parse::Concat(Automaat een, Automaat twee){
    std::cout<<"komt in CONCAT"<< std::endl;
    een.push_back({een.back()[2], '$', twee.front()[0], 0}); // connect acceptingState of een to startState of twee

    Automaat result = een;

    for (const auto& transition : twee){
        result.push_back(transition);
    }

    return result;

    

}

Automaat parse::Term(){
    std::cout<<"komt in TERM"<< std::endl;
    Automaat Aut1 = Fact(); // bijv letter
    
    if (huidigeLetter == '(' || isLetter(huidigeLetter)){
        Automaat Aut2 = Term(); // recursie!
        Aut1 = Concat(Aut1, Aut2);
    }

    
    
    return Aut1; // concatenatie van Aut1 en Aut2;
} // Term

Automaat parse::Star(Automaat een){
    std::cout<<"komt in STAR"<< std::endl;
    int startState = state++;
    int acceptState = state++;

    een.push_back({startState, '$', een.front()[0], 0}); // startState to startState of een

    een.push_back({een.back()[2], '$', een.front()[0], 0}); // acceptState of een to startState of een
    een.push_back({startState, '$', acceptState, 0}); // startState to finalstate



    return een;

}


Automaat parse::Fact(){
    std::cout<<"komt in FACT"<< std::endl;
    Automaat Aut1;

    if (huidigeLetter == '('){ 
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
        std::cout<<expressie[huidigpos] << std::endl;
        Aut1 = Expr();

        if (huidigeLetter == ')'){
            huidigpos++;
            huidigeLetter = expressie[huidigpos]; // lees volgende letter
        } else{
            // error;
        }
    } else if(isLetter(huidigeLetter)){  // letter opslaan 
        std::cout<< huidigpos << std::endl;
        std::cout<<expressie[huidigpos] << std::endl;
        Aut1.push_back({state, huidigeLetter, state+1, 0}); //tak met huidigeLetter;
        state++;
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
    } else{
        // throw std::runtime_error("Ingevoerde expressie is onjuist!");
    }

    if (huidigeLetter == '*'){ // eventueel while?
        Aut1 = Star(Aut1);
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
    }
    
    return Aut1;
} // Fact