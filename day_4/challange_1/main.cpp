/*
*   Time for day 4! I just finished day 3 and my brain is walking the line of not working, thusly I apologise in advance for this horrible code.
*   Todays song is breaking the previously establised genre of folk punk. Time for some country!
*
*   Todays song: This Is My Prairie by Corb Lund
*   https://open.spotify.com/track/0eDrgtdlHKtwPqI6JXyoAC
*/

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> toBeAnnounced(std::string l, char separator = ',') {
    std::vector<int> rv;
    std::string buffnr = "";
    for(int i = 0; i < l.length(); i++) {
        if(l[i] != separator) buffnr += l[i];
        else if(buffnr.empty()) {} // do nothing lol
        else {rv.push_back(std::stoi(buffnr)); buffnr = "";}
    }
    return rv;
}

std::vector<std::vector<int>> nBingoBox(std::vector<std::string> content) {
    std::vector<std::vector<int>> rv;
    for(std::string l: content)
        rv.push_back(toBeAnnounced(l, ' '));
    return rv;
}

bool has(std::vector<int> r, int item) {
    bool h = false;
    for(int i: r)
        if(i == item) { h = true; break; }
    return h;
}

int getValue(std::vector<int> v) {
    int tally = 0;
    for(int val: v)
        tally += val;
    return tally;
}

int superDuperUltraGetValueInator(std::vector<std::vector<int>> v) {
    int tally = 0;
    for(std::vector<int> xd: v)
        tally += getValue(xd);
    return tally;
}

int getUnMarked(std::vector<int> nrs, std::vector<std::vector<int>> b) {
    int tally = 0;
    for(std::vector<int> v: b)
        for(int i: v)
            if(!has(nrs, i)) tally += i;
    return tally;
}

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    // I really hate this line but it is what it is
    std::vector<std::vector<std::vector<int>>> bingos;

    std::string line;
    std::vector<int> wNr;
    bool first = true;
    std::vector<std::string> bingoBuffer;
    while(getline(file, line)) {
        if(first) {
            wNr = toBeAnnounced(line);
            first = false;
        } else {
            if(!line.empty()) bingoBuffer.push_back(line + " ");
            else {
                bingos.push_back(nBingoBox(bingoBuffer));
                bingoBuffer.clear();
            }
        }
    }
    //cba
    bingos.push_back(nBingoBox(bingoBuffer));

    std::vector<int> drawnNumbers;
    for(int n: wNr) {
        drawnNumbers.push_back(n);
        for(std::vector<std::vector<int>> b: bingos) {
            bool wonLR = false;
            bool wonTB = false;

            // check L -> R
            for(std::vector<int> row: b){
                bool wonThisRow = true;
                for(int ri: row)
                    if(!has(drawnNumbers, ri)) wonThisRow = false;
                if(wonThisRow) wonLR = true;
            }

            // check top -> bottom
            for(int i = 0; i < 5; i++) {
                bool wonThisRow = true;
                for(int j = 0; j < 5; j++) {
                    if(!has(drawnNumbers, b[j][i])) { wonThisRow = false; }
                }
                if(wonThisRow) wonTB = true;
            }

            if(wonLR || wonTB) {
                int unmarked = getUnMarked(drawnNumbers, b);
                printf("LR: %d TB: %d | winner winner chiucken dinner!!!!! n: %d %d %d\n", wonLR, wonTB, n, unmarked, unmarked * n);
                return 1;
            }
        }
    }
}
