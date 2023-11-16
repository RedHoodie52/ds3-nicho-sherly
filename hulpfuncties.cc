#include <iostream>
#include "hulpfuncties.h"

bool isLetter(char letter){
    if(letter >= 'a' || letter <= 'z'){
        return true;
    }

    return false;
}

void parse::CallExpr(std::string formule){
    expressie = formule;
    lengteExpressie = expressie.size();
    huidigpos = 0;

}

Automaat parse::Union(Automaat een, Automaat twee){


}

Automaat parse::Expr(){
    // Automaat Aut;
    Automaat Aut1 = Term();
    
    if (huidigeLetter == '|' ){ 
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
        Automaat Aut2 = Expr(); // recursie!
    }


    return Aut1;// plus van Aut1 en Aut2;
} // Expr

Automaat parse::Concat(Automaat een, Automaat twee){
    Automaat drie;

    

}

Automaat parse::Term(){
    Automaat Aut1 = Fact(); // bijv letter
    
    if (huidigeLetter == '(' || isLetter(huidigeLetter)){
        Automaat Aut2 = Term(); // recursie!
        Aut1 = Concat(Aut1, Aut2);
    }

    
    
    return Aut1; // concatenatie van Aut1 en Aut2;
} // Term

Automaat parse::Star(Automaat een, Automaat twee){
    // begin state is final state
    // of 

}


Automaat parse::Fact(){
    Automaat Aut1;

    if (huidigeLetter == '('){ 
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
        Aut1 = Expr();

        if (huidigeLetter == ')'){
            huidigpos++;
            huidigeLetter = expressie[huidigpos]; // lees volgende letter
        } else{
            // error;
        }
    } else if(isLetter(huidigeLetter)){  // letter opslaan 
        Aut1.push_back({state, huidigeLetter, state+1, 0}); //tak met huidigeLetter;
        state++;
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
    } else{
        // Error!
    }

    if (huidigeLetter == '*'){ // eventueel while?
        // pas ster toe op Aut;
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter
    }
    
    return Aut1;
} // Fact