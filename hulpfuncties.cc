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

// hulp functie voor wisselen van vectors
void swapVectors(std::vector<int>& a, std::vector<int>& b) {
    std::vector<int> temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

// sorteert automaat op "from state"
void sortAutomaat(Automaat& automaat) {
    for (size_t i = 0; i < automaat.size(); ++i) {
        for (size_t j = i + 1; j < automaat.size(); ++j) {
            if (automaat[j][0] < automaat[i][0]) {
                swapVectors(automaat[i], automaat[j]);
            }
        }
    }
}

// print de automaat
void parse::printAutomaat(Automaat& automaat) const {
    sortAutomaat(automaat);
    automaat.push_back({state, '$', 0, 0});

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
    int startState = state; // nieuwe ingangspunt

    state++;
    int acceptState = state; // nieuwe uitgangspunt

    beginState = startState; // ingangspunt opslaan voor matchen

    Automaat result = een;
    for (const auto& transition : twee) {
        result.push_back(transition);
    }
    //ingangspunt naar ingangspunt van "een" en "twee"
    result.insert(result.begin(), {startState, '$', een.front()[0], twee.front()[0]}); 
    // uitgangspunt "een" naar uitgangspunt
    result.push_back({een.back()[2], '$', acceptState, 0});
    // uitgangspunt "twee" naar uitgangspunt
    result.push_back({twee.back()[2], '$', acceptState, 0});

    return result;
}

Automaat parse::Expr(){
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
        // throw std::runtime_error("Ingevoerde expressie is onjuist!");
        return Aut1;
    }

    return Aut1;// union van Aut1 en Aut2;
} // Expr

Automaat parse::Concat(Automaat een, Automaat twee){
    Automaat result = een;
    Automaat temp;
    // verbind uitgang "een" met ingang "twee"
    if(een.back()[3] != 0){
        result.push_back({een.back()[3], '$', twee.front()[0], 0});
    } else{
        result.push_back({een.back()[2], '$', twee.front()[0], 0}); 

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
        // throw std::runtime_error("Ingevoerde expressie is onjuist!");

    }

    
    
    return Aut1; // concatenatie van Aut1 en Aut2;
} // Term

Automaat parse::Star(Automaat een){
    Automaat result = een;

    state++;
    int startState = state;// nieuwe inganspunt

    state++;
    int acceptState = state; // nieuwe uitgangspunt

    beginState = startState; // ingangspunt oplsaan voor matchen
    
    // uitgang "een" verbinden met ingang "een"
    result.push_back({een.back()[2], '$', een.front()[0], acceptState});
    // ingang verbinden met ingang "een" en uitgang
    result.insert(result.begin(),{startState, '$', een.front()[0], acceptState}); 

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
            // throw std::runtime_error("Ingevoerde expressie is onjuist!");
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

    if (huidigeLetter == '*'){ 
        Aut1 = Star(Aut1);
        if (huidigpos < lengteExpressie ){
            huidigpos++;
            huidigeLetter = expressie[huidigpos]; // lees volgende letter
        } else{
            huidigeLetter = '$';
        }
    }
    
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
    dotFile << "  rankdir=\"LR\";" << std::endl;

    for (const auto& transition : transitions) {
        char character = static_cast<char>(transition[1]);
        if(character == '$'){
            character = ' ';
        }
        if(transition[2 != 0]){
            dotFile << "  \"" << transition[0] << "\" -> \"" << transition[2] << "\"";
        }
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

bool contains(const std::vector<int>& vec, int value) {
    for (int element : vec) {
        if (element == value) {
            return true;
        }
    }
    return false;
}

void parse::FindEpsilon(int path){ // zoekt epsilon-closure
    
    if(path != 0){
        if(!contains(passed, path)){
            passed.push_back(path); // als het is langs geweest, voorkomt oneindige loops
            for(const auto automaat : Aut){
                if(automaat[0] == path && automaat[1] == '$'){
                    if(path == Aut.back()[0]){
                        onthoudE.push_back(path);
                    }
                    FindEpsilon(int(automaat[2]));
                    if(automaat[3] != '0'){
                        FindEpsilon(int(automaat[3]));
                    }
                }else if(automaat[0] == path){
                    onthoudE.push_back(path);
                }
            }
        }
    }
}

int parse::findSymbol(int path, char symbol){ // zoekt of er een pad naar matchende symbol is

    for(const auto automaat : Aut){
        if(automaat[0] == path && automaat[1] == symbol){ 
            return automaat[2];
        }
    }
    
    return 0;
}
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void parse::callMatch(std::string match){
    
    std::vector<int> onthoudS;
    for(const auto automaat : Aut){
        if(automaat[0] == beginState && automaat[1] == '$'){
            passed.clear();
            FindEpsilon(beginState); // als automaton begint met een lambda
        }else{
            onthoudS.push_back(beginState); // als automaton begint met een character

        }
    }

    for(int index = 0; index < int(match.length()); index++){ // gaat eerst lambda closer, daarna matchende symbol
        for(const int i : onthoudE){
            int a = findSymbol(i, match[index]);
            if(a != 0 ){
                onthoudS.push_back(a);
            }
        }
        onthoudE.clear();
        for(const int j : onthoudS){
            passed.clear();
            FindEpsilon(j);
        }
        onthoudS.clear();
    }

    bubbleSort(onthoudE);

    if(onthoudE.back() == Aut.back()[0]){
        std::cout << "match" << std::endl;
    }else{
        std::cout << "geen match" << std::endl;
    }

}
