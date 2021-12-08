#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

std::vector<int> csvToFish(std::string input) {
    std::vector<int> rv;
    std::string buff;
    for(int i = 0; i < input.length() + 1; i++)
        if(input[i] == ',' || i == input.length()) { rv.push_back(std::stoi(buff)); buff = ""; }
        else buff += input[i];
    return rv;
}

// every 7 days, new fish
// might be diff days
// new fish spawns with timer of 8, do not count first day

int fishInPeriod(int days, int fish) {
    int tally = 0;
    for(int i = 0; i < days; i++) {
        if(fish == 0) {
            fish = 7;
            tally += 1;
            tally += fishInPeriod(days - i, 9);
        }
        fish -= 1;
    }   

    return tally;
}

int days(std::vector<int> f, int days) {
    int rv = 0;
    for(int fish: f)
        rv += fishInPeriod(days, fish);
    return rv;
}

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    std::vector<int> fishes;
    std::string line;
    while(getline(file, line))
        fishes = csvToFish(line);
    int res = days(fishes, 256);
    printf("there are %d fishes after 80 days\n", res + fishes.size());
}
