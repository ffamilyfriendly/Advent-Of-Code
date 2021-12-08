// part 1 ez
// part 2 should just be the the avg pos
// I flunked this but it worked

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> csvToInt(std::string input) {
    std::vector<int> rv;
    std::string buff;
    for(int i = 0; i < input.length() + 1; i++)
        if(input[i] == ',' || i == input.length()) { rv.push_back(std::stoi(buff)); buff = ""; }
        else buff += input[i];
    return rv;
}

int getAvg(std::vector<int> s) {
    int tally = 0;
    for(int i: s) {
        tally += i;
    }

    return tally / s.size();
}

int balls(int s) {
    int tally = 0;
    for(int i = 0; i < s; i++)
        tally += i + 1;
    return tally;
}

int fuelUsage(std::vector<int> crabs, int pos) {
    int tally = 0;
    for(int i: crabs) {
        int moved = std::abs(pos - i);
        tally += balls(moved);
    }
        //tally += std::abs(pos - i) +;
    return tally;
}

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    std::vector<int> crabs;
    std::string line;
    while(getline(file, line))
        crabs = csvToInt(line);
    int pos1 = getAvg(crabs);
    int pos2 = pos1 + 1;
    // 101082923 too high
    printf("moving to position would cost %d fuel \n", std::min(fuelUsage(crabs, pos1),fuelUsage(crabs, pos2)));
}
