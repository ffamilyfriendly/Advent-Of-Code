// part 1 ez

#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

std::vector<int> csvToInt(std::string input) {
    std::vector<int> rv;
    std::string buff;
    for(int i = 0; i < input.length() + 1; i++)
        if(input[i] == ',' || i == input.length()) { rv.push_back(std::stoi(buff)); buff = ""; }
        else buff += input[i];
    return rv;
}

int getMedian(std::vector<int> s) {
    std::sort(s.begin(), s.end());
    return s[s.size() / 2];
}

int fuelUsage(std::vector<int> crabs, int pos) {
    int tally = 0;
    for(int i: crabs)
        tally += std::abs(pos - i);
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
    //int pos = getMedian(crabs);

    printf("%d \n", fuelUsage(crabs, getMedian(crabs)));
}
