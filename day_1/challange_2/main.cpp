#include <iostream>
#include <fstream>
#include <limits>
#include <vector>

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    std::string line;
    std::vector<int> data;
    while(getline(file, line))
        data.push_back(std::stoi(line));
    
    int last = std::numeric_limits<int>::max();
    int times = 0;

    for(int i = 0; i < data.size() - 2; i++) {
        int thisWindow = data.at(i) + data.at(i + 1) + data.at(i + 2);
        if(thisWindow > last)
            times++;
        last = thisWindow;
    }
    printf("result is %d times!\n", times);
}
