// Hello! If you reading this and arent me (or just me in the future) I'm just a friendly reminder that mischeif brew is good
// https://open.spotify.com/track/1gaLJnwwY9aEM55ZuSr4Ta?si=gTMgRuOBTzK4QWVlZsfWHA
// or https://www.youtube.com/watch?v=KKclBgisCMA

#include "../../lib/header.h"
#include <fstream>
#include <chrono>

#define DEBUG false

struct instruction {
    int argument;
    int hasBeenRan = false;
    string opcode;
};

vector<instruction> stack;

console::Console *c = new console::Console();

/* aight part 2 seems to be a lot harder. Now we are able to "repair" the code by ignoring one jmp instruction
 * or by changing one nop to a jmp.
 * This can be solved by doing smarty pants logic but do i look smart? no, for I am text
*/

int getLoopValue(vector<instruction> stackInstance) {
    int thisAccumalator = 0;
    int hasBeenRan[stackInstance.size()] = {0};

    for(int i = 0; i < stackInstance.size(); i++) {
        
        if(hasBeenRan[i] > 2) {
            thisAccumalator = 0;
            break;
        }

        hasBeenRan[i]++;

        if(stackInstance[i].opcode == "acc") {
            thisAccumalator += stackInstance[i].argument; //perform mad mafs on accumulator
        } else if(stackInstance[i].opcode == "jmp") {
            i += stackInstance[i].argument-1; //move to stack index - 1 since for loop adds one every loop
        }
    }

    return thisAccumalator;
}

int main(int argc,  char** argv) {
    auto t1 = chrono::high_resolution_clock::now();
    int accumulator = 0;

    fstream input; 
    #if DEBUG
        input.open("debuginput.txt");
    #else
        input.open("input.txt");
    #endif

    if(!input || !input.is_open()) {
        perror("could not open input");
        exit(EXIT_FAILURE);
    }

    string line;

    while(getline(input,line)) {
        instruction lineInstruction;
        lineInstruction.argument = atoi(line.substr(4).c_str());
        lineInstruction.opcode = line.substr(0,3);
        stack.push_back(lineInstruction);
    }

    //Removed the clog. Function now runns at around 4ms which is acceptable I'd say
    for(int i = 0; i < stack.size(); i++) {
        int loopVal = 0;

        string oldInstruct = stack[i].opcode;

        if(stack[i].opcode == "nop") stack[i].opcode = "jmp";
        else if(stack[i].opcode == "jmp") stack[i].opcode = "nop";
        else continue;


        loopVal = getLoopValue(stack);

        stack[i].opcode = oldInstruct;

        if(loopVal != 0) {
            accumulator = loopVal;
            break;
        }
    } 
    auto t2 = chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

    c->log("accumulator is " + to_string(accumulator) + " | execution took " + to_string(duration) + "ms");
    
}
