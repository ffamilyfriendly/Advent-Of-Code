/*
*   I'm doing this one day later, was busy yesterday.
*   Todays song is from a different artist than yesterday (https://github.com/ffamilyfriendly/Advent-Of-Code/blob/main/day_2/challange_1/main.cpp) just to spice it up a bit
*   
*   Todays song: Welcome to Slime City by Harley Poe
*   https://open.spotify.com/track/3C8TtSfNGMMihlumnySXkT
*/

#include <iostream>
#include <fstream>

struct intTupple {
    int zero;
    int one;
};

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    intTupple rates[12];
    std::string line;
    while(getline(file, line)) {
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == '0')
                rates[i].zero++;
            else
                rates[i].one++;
        }
    }

    // actually treating the bin number as a string is likely going to give me issues in part 2
    std::string gamma;
    std::string epsilon;

    for(int i = 0; i < 12; i++) {
        if(rates[i].one > rates[i].zero) {
            gamma += '1';
            epsilon += '0';
        } else {
            epsilon += '1';
            gamma += '0';
        }
    }

    int decGamma = std::stoi(gamma, 0, 2);
    int decEpsilon = std::stoi(epsilon, 0, 2);

    printf("gamma: %s (%d) epsilon: %s (%d)\nAnswer: %d\n", gamma.c_str(), decGamma , epsilon.c_str(), decEpsilon, decGamma * decEpsilon);
}
