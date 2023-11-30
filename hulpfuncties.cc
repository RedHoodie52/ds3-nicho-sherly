#include <iostream>
#include "hulpfuncties.h"

bool isLetter(char letter){
    if(letter >= 'a' && letter <= 'z'){
        return true;
    }

    return false;
}

void parse::CallExpr(std::string formule){
    state = 1;
    Aut.clear();
    expressie = formule;
    lengteExpressie = expressie.size();
    huidigpos = 0;
    huidigeLetter = expressie[huidigpos];
    beginState = 1;

    
    Aut = Expr();

    printAutomaat(Aut);

}

// Custom function to swap two vectors
void swapVectors(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// Custom sorting function to sort Automaat based on the first element of each vector
void sortAutomaat(Automaat& automaat) {
    for (size_t i = 0; i < automaat.size(); ++i) {
        for (size_t j = i + 1; j < automaat.size(); ++j) {
            if (automaat[j][0] < automaat[i][0]) {
                swapVectors(automaat[i], automaat[j]);
            }
        }
    }
}
void parse::printAutomaat(Automaat& automaat) const {
    sortAutomaat(automaat);

    std::cout << "From State\tSymbol\tTo State 1\tTo State 2" << std::endl;
    for (const auto& transition : automaat) {
        std::cout << transition[0] << "\t\t";

        char character = static_cast<char>(transition[1]);
                
        std::cout << character << "\t\t";
        std::cout << transition[2] << "\t\t"
                  << transition[3] << std::endl;
    }
    std::cout << std::endl;
}

Automaat parse::Union(Automaat een, Automaat twee){
    
    state++;
    int startState = state;
    if (beginState > startState){
        beginState = startState;
    }
    state++;
    int acceptState = state;


    Automaat result = een;

    for (const auto& transition : twee) {
        result.push_back(transition);
    }
    result.insert(result.begin(), {startState, '$', een.front()[0], twee.front()[0]});
    // result.push_back({startState, '$', een.front()[0], twee.front()[0]}); // connect new startState to startState of een and twee

    result.push_back({een.back()[2], '$', acceptState, 0});

    result.push_back({twee.back()[2], '$', acceptState, 0});

    
    
    return result;

}

Automaat parse::Expr(){
    // Automaat Aut;
    Automaat Aut1 = Term();
    
    if (huidigeLetter == '|' ){ 
        
        if (huidigpos < lengteExpressie){
            huidigpos++;
            huidigeLetter = expressie[huidigpos]; // lees volgende letter
            state++;
            Automaat Aut2 = Expr(); // recursie!
            Aut1 = Union(Aut1, Aut2);
        }
    
    }else {
        // Handle the case where '|' is at the end of the expression
        // throw std::runtime_error("Expected expression after '|'");
        return Aut1;
    }

    return Aut1;// union van Aut1 en Aut2;
} // Expr

Automaat parse::Concat(Automaat een, Automaat twee){
    // printAutomaat(een);
    // printAutomaat(twee);
    Automaat result = een;
    Automaat temp;
    // temp.push_back({een.back()[2], '$', twee.front()[0], 0});
    // printAutomaat(temp);

    if(een.back()[3] != 0){
        result.push_back({een.back()[3], '$', twee.front()[0], 0});
    } else{
        result.push_back({een.back()[2], '$', twee.front()[0], 0}); // connect acceptingState of een to startState of twee

    }

    for (const auto& transition : twee){
        result.push_back(transition);
    }

    return result;

    

}

Automaat parse::Term(){
    Automaat Aut1 = Fact(); // bijv letter
    huidigeLetter = expressie[huidigpos];
    
    if (huidigeLetter == '(' || isLetter(huidigeLetter)){
        
        state++;
        Automaat Aut2 = Term(); // recursie!
        Aut1 = Concat(Aut1, Aut2);

    }else{
        // throw std::runtime_error("Expected a letter after or a '('");

    }

    
    
    return Aut1; // concatenatie van Aut1 en Aut2;
} // Term

Automaat parse::Star(Automaat een){
    Automaat result = een;
    state++;
    int startState = state;

        beginState = startState;
    
    state++;
    int acceptState = state;

    result.push_back({een.back()[2], '$', een.front()[0], acceptState});

    result.insert(result.begin(),{startState, '$', een.front()[0], acceptState}); // acceptState of een to startState of een
    // result.push_back({startState, '$', een.front()[0], acceptState}); // startState to startState of een and acceptstate



    // printAutomaat(result);
    return result;
}


Automaat parse::Fact(){
    Automaat Aut1;

    if (huidigeLetter == '('){ 
        huidigpos++;
        huidigeLetter = expressie[huidigpos]; // lees volgende letter

        Aut1 = Expr();

        if (huidigeLetter == ')'){
            if (huidigpos < lengteExpressie){
            huidigpos++;
            huidigeLetter = expressie[huidigpos]; // lees volgende letter
            } else{
            huidigeLetter = '$';
            }
        } else{
            // error;
        }
    } else if(isLetter(huidigeLetter)){  // letter opslaan 

        Aut1.push_back({state, huidigeLetter, state+1, 0}); //tak met huidigeLetter;
        state++;

        if (huidigpos < lengteExpressie ){
            huidigpos++;
            huidigeLetter = expressie[huidigpos]; // lees volgende letter
        } else{
            huidigeLetter = '$';
        }

    } else{
        // throw std::runtime_error("Ingevoerde expressie is onjuist!");
    }


    if (huidigeLetter == '*'){ // eventueel while?
        Aut1 = Star(Aut1);
        if (huidigpos < lengteExpressie ){
            huidigpos++;
            huidigeLetter = expressie[huidigpos]; // lees volgende letter
        } else{
            huidigeLetter = '$';
        }
    }

    Aut1.push_back({state, '$', 0, 0});
    
    return Aut1;
} // Fact

void parse::printDOT(const std::string& uitvoerNaam){
    std::ofstream dotFile(uitvoerNaam);

    if(!dotFile){
        std::cerr << "Kan niet wegschrijven!" << std::endl;
        return;
    }

    if(!Aut.empty()){
        printHelpDOT(Aut, dotFile);
        dotFile.close();
    } else{
        std::cerr << "Er is geen esxpressie" << std::endl;

    }


}

void parse::printHelpDOT(Automaat transitions, std::ofstream& dotFile){
    dotFile << "digraph StateMachine {" << std::endl;

    for (const auto& transition : transitions) {
        char character = static_cast<char>(transition[1]);
        if(character == '$'){
            character = ' ';
        }
        dotFile << "  \"" << transition[0] << "\" -> \"" << transition[2] << "\"";
        if (transition[3] != 0) {
            dotFile << " [label=\"" <<  character << "\"]" << std::endl;
            dotFile << "  \"" << transition[0] << "\" -> \"" << transition[3] << "\" [label=\"" << character << "\"]" << std::endl;
        } else {
            dotFile << " [label=\"" <<  character << "\"]" << std::endl;
        }
    }

    dotFile << "}" << std::endl;

    dotFile.close();
}

bool parse::calcMatch(std::string match){
    if(Aut.empty()){
        std::cerr << "Geen expressie ingevoerd." << std::endl;
        return false;
    }

    std::cout<< "beginstate:" << beginState << std::endl;
    int currentState = beginState; // Start state of the automaton
    size_t index = 0; // Index to iterate through the input string

    currentSymbol = match[index];

    // checken of de currentstate final state is 
    std::cout << "currentState: " << currentState << std::endl;
    if(currentState == Aut.back()[0]){
        return true;
    } 

    while (index < match.size()) {

        bool transitionFound = false;

   

        for (const auto& transition : Aut) { // check of er een geldige transistion is  

            if (transition[0] == currentState && (transition[1] == currentSymbol || transition[1] == '$')) {

                currentState = transition[2]; // Move to the next state
                for (const auto& nextTransition : Aut) {
                    if (nextTransition[0] == currentState) {
                        currentSymbol = nextTransition[1];
                        break; // Once found, exit the loop
                    }
                }

                transitionFound = true;
                break;
            }
    
        }

        if (!transitionFound) {
            std::cerr << "No valid transition for symbol '" << currentSymbol << "' at state " << currentState << std::endl;
            return false;
        }

        index++;
    }

    // checken of de currentstate final state is 
    std::cout << "currentState: " << currentState << std::endl;
    if(currentState == Aut.back()[0]){
        return true;
    } 
     

    return false;

}


void parse::callMatch(std::string match){
    if (calcMatch(match)){
        std::cout << "match" << std::endl;
    }else{
        std::cout << "geen match" << std::endl;
    }

}