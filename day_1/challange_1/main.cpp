/*
*   Last year (https://github.com/ffamilyfriendly/Advent-Of-Code_2020) I wrote all challanges in c++ and will continue doing that this year.
*   Another tradition from last year was for me to include a link to some horrible song that I unironically enjoy as a sort of "recomendation" for
*   the non-existing readers of this comment.
*
*   Todays song is "Away with Purity" by mischief brew
*    https://open.spotify.com/track/72f8i0NFYdfmXU4qL7G7Bc?si=e34c591a3fe549d5
*/

#include <iostream>
#include <fstream>
#include <limits>

int main(int argc,  char** argv) {
    std::fstream file;
    file.open("input.txt", std::ios::in);
    if(!file || !file.is_open()) {
        printf("skill issue. File not found\n");
        return 1;
    }

    std::string line;
    int last = std::numeric_limits<int>::max();
    int times = 0;
    while(getline(file, line)) {
        int thisline = std::stoi(line);
        if(thisline > last)
            times++;
        last = thisline;
    }
    printf("result is %d times!\n", times);
}
