// right, this probably calls for a recursive function for each bit field. Let's do that
// actually scratch above. By simply keeping the intTupple array we already know what number will be most common in each bitpos
// Scratch above too. This challange took me way too long because I'm dumb and didnt read. My problem was keeping the values for the most
// common number from the first itteration, which became wrong after the first itteration as elements were removed and thus the numbers became
// wrong. Lesson to next time: read the fucking challange, dumb swede

#include <iostream>
#include <fstream>
#include <vector>
#include <array>

struct intTupple {
    int zero;
    int one;
};

#define WIDTH 12


std::array<intTupple, WIDTH> getMostCommon(std::vector<std::string> v) {
    std::array<intTupple, WIDTH> rv;
    for(int i = 0; i < WIDTH; i++) {
        intTupple a;
        a.one = 0;
        a.zero = 0;
        rv[i] = a;
    }
    intTupple rates[WIDTH];
    for(std::string line: v) {
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == '0')
                rv[i].zero++;
            else
                rv[i].one++;
        }
    }

    return rv;
}

int doMagicThing(std::vector<std::string> vec, bool mode, int pos = 0) {
    std::vector<std::string> remaining;


    std::array<intTupple, WIDTH> rates = getMostCommon(vec);


    //std::cout << "###" << rates[pos].one << "|" << rates[pos].zero << std::endl;
    for(std::string l: vec) {
        char hasToMatch = '0';
        if(!mode) {
            if((rates[pos].one >= rates[pos].zero)) hasToMatch = '1';
        } else {
            if(rates[pos].one < rates[pos].zero) hasToMatch = '1';
        }

        //std::cout << mode << "|[" << pos << "] " << l << "(" << hasToMatch << ")" << std::endl;
        if(mode && pos == 8) printf("%s\n", l.c_str());
        if(l[pos] == hasToMatch) {
            remaining.push_back(l);
            if(pos == WIDTH - 1) printf("found %s!!!!\n", l.c_str());
        };
    }

    if(remaining.size() == 0) {
        printf("failed. Mode: %d. Pos: %d\n", mode, pos);
        return -1;
    }

    if(remaining.size() == 1) {
        //std::cout << "[" << mode << "]" << "found" << remaining.at(0) << std::endl;;
        return std::stoi(remaining.at(0), 0, 2);
    }
    else return doMagicThing(remaining, mode, pos+1);
};

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while(getline(file, line))
        lines.push_back(line);

    int co = doMagicThing(lines, false);
    int oxy = doMagicThing(lines, true);

    printf("co: %d, oxy: %d\nAnswer: %d\n", co, oxy, co * oxy);
}
