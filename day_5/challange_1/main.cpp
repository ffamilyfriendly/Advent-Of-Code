/*
*   Day 5 less go!!
*   yesterdays song (https://github.com/ffamilyfriendly/Advent-Of-Code/blob/main/day_4/challange_1/main.cpp) was country. Wonder what it is today?
*   
*   Todays song: Jag e fortfarande introvert by Finska Snubben
*   hhttps://open.spotify.com/track/5hk40ctI5N4ZWHY7dX77gL
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

std::pair<std::string, std::string> splitArrow(std::string input) {
    std::pair<std::string, std::string> rv;
    int pos = input.find('-');
    rv.first = input.substr(0, pos-1);
    rv.second = input.substr(pos + 3);
    return rv;
}

std::pair<int, int> getCsvInt(std::string input) {
    std::pair<int, int> rv;
    int pos = input.find(",");
    rv.first = std::stoi(input.substr(0,pos));
    rv.second = std::stoi(input.substr(pos+1));
    return rv;
}

int main(int argc,  char** argv) {
    //std::vector<std::pair<std::pair<int,int>,std::pair<int,int>>> pairs;
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    std::string line;
    std::map<std::string, int> collisions;
    while(getline(file, line)) {
        auto gang = splitArrow(line);
        std::pair<std::pair<int,int>, std::pair<int,int>> t;
        t.first = getCsvInt(gang.first);
        t.second = getCsvInt(gang.second);
        if(!(t.first.first != t.second.first ^ t.first.second != t.second.second)) continue;
        //std::cout << "allow: " << line << std::endl;
        bool lr = t.first.first != t.second.first;

        // this approach makes no sense and will come back and bite me in the ass on pt 2
        if(lr) {
            int to = std::max(t.first.first, t.second.first);
            int from = std::min(t.first.first, t.second.first);
            for(int i = from; i < to+1; i++) {
                std::string pos = std::to_string(i) + "|" + std::to_string(t.second.second);
                //std::cout << "LR:" << pos << std::endl;
                if(!collisions[pos]) collisions[pos] = 0;
                collisions[pos]++;
            }
        } else {
                int to = std::max(t.first.second, t.second.second);
                int from = std::min(t.first.second, t.second.second);
            for(int i = from; i < to+1; i++) {
                std::string pos = std::to_string(t.first.first) + "|" + std::to_string(i);
                //std::cout << "TB:" << pos << std::endl;
                if(!collisions[pos]) collisions[pos] = 0;
                collisions[pos]++;
            }
        }
        //pairs.push_back(t);
    }

    std::cout << collisions.size() << std::endl;

    int tally = 0;
    for(auto it = collisions.begin(); it != collisions.end(); it++)
        if(it->second >= 2) tally++;
    printf("Answer: %d\n",tally);
}
