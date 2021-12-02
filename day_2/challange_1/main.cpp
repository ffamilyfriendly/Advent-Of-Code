/*
*   Right, day two. This also means music recomendation number two!
*   last time (https://github.com/ffamilyfriendly/Advent-Of-Code/blob/main/day_1/challange_1/main.cpp) 
*   it was mischief brew and I intend to keep it that way today too!
*   
*   Todays song: When It Rains
*   https://open.spotify.com/track/75oC69tZF2ZFx6hErzresj
*/

#include <iostream>
#include <fstream>

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    int x = 0;
    int y = 0;
    std::string line;
    while(getline(file, line)) {
        int sPos = line.find(' ');
        std::string nr = line.substr(sPos);
        if(line[0] == 'f')
            x += std::stoi(nr);
        else if(line[0] == 'd')
            y += std::stoi(nr);
        else y -= std::stoi(nr);
    }

    printf("location is %d %d! Answer: %d\n", x, y, x * y);
}
