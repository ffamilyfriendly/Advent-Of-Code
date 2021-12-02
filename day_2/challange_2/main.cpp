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
    int aim = 0;
    std::string line;
    while(getline(file, line)) {
        int sPos = line.find(' ');
        std::string nr = line.substr(sPos);
        int arg = std::stoi(nr);
        if(line[0] == 'f') {
            x += arg;
            y += aim * arg;
        }
        else if(line[0] == 'd')
            aim += arg;
        else aim -= arg;
    }

    printf("location is %d %d! Answer: %d\n", x, y, x * y);
}
