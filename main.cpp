#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <unordered_map>
using namespace std;

string stoneIteration(const string& stoneString) {

    unsigned long long stoneNumber = stoll(stoneString);

    //check for all applicable rules
    if (stoneNumber == 0) {
        return "1";
    }
    if (stoneString.length() % 2 == 0) {
        string firstHalfOfStone = stoneString.substr(0,stoneString.length() / 2);
        string secondHalfOfStone = stoneString.substr(stoneString.length() / 2);

        int amountOfLeadingZeroes = 0;

        while (secondHalfOfStone[amountOfLeadingZeroes] == '0' &&
            amountOfLeadingZeroes < secondHalfOfStone.length() - 1) {

            amountOfLeadingZeroes++;
        }
        secondHalfOfStone = secondHalfOfStone.substr(amountOfLeadingZeroes);

        stringstream result;
        result << firstHalfOfStone << " " << secondHalfOfStone;
        return result.str();
    }
    return to_string(stoneNumber * 2024);
}



struct PairHash {
    template <class T1, class T2>
    size_t operator() (const pair<T1,T2> &pair) const {
        return hash<T1>()(pair.first) ^ hash<T2>()(pair.second) << 1;
    }
};

unordered_map<pair<string,int>, long long, PairHash> cache;

long long amountOfStonesAfterBlink(string& stone, int blinksLeft) {

    if (cache.find({stone, blinksLeft}) != cache.end()) {
        return cache[{stone, blinksLeft}];
    }

    if (blinksLeft == 0) {
        return 1;
    }

    string stonesAfterBlink = stoneIteration(stone);

    stonesAfterBlink.append(" ");

    int stonePos = 0;

    long long result = 0;

    for (int i = 0; i < stonesAfterBlink.length(); i++) {

        if (stonesAfterBlink[i] == ' ') {

            string stone = stonesAfterBlink.substr(stonePos, i - stonePos);

            result += amountOfStonesAfterBlink(stone, blinksLeft - 1);

            stonePos = i+1;

        }
    }

    cache[{stone, blinksLeft}] = result;

    return result;
}



int main() {

    ifstream f;
    f.open("../input.txt");

    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 0;
    }

    string stones;
    getline(f,stones);

    f.close();

    // Append Blank so that every stone is between two blanks
    stones = stones.append(" ");

    int amountOfBlinks = 75;

    int stonePos = 0;

    long long result = 0;

    for (int i = 0; i < stones.length(); i++) {

        if (stones[i] == ' ') {

            string stone = stones.substr(stonePos, i - stonePos);

            result += amountOfStonesAfterBlink(stone, amountOfBlinks);

            stonePos = i+1;

        }
    }

    cout << result << endl;

    return 0;

}
