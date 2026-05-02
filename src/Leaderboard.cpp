#include "include/Leaderboard.hpp"
#include <sstream>
#include <iostream>

//this represents the actual leaderboard object, not the leaderboard window, which was done separately
Leaderboard::Leaderboard(std::map<int, std::vector<std::string>>& map) 
    : leaderboard(map),
      currTime(0),
      currName(""),
      lastInsertedPlace(-1)
    {}

//leaderboard is stored in a map with a number representing place and then a
//vector of strings which should be in the format "time", "name"
std::map<int, std::vector<std::string>>& Leaderboard::getLeaderboard() {
    return leaderboard;
}

//takes in a map to set as the leaderboard attribute
void Leaderboard::setLeaderboard(std::map<int, std::vector<std::string>>& board) {
    leaderboard = board;
}

//set the current time (not a time on the leaderboard, but the most recent game time to compare with the rest of the leaderboard)
void Leaderboard::setCurrTime(float time) {
    currTime = time;
}

//set the name of the current player
void Leaderboard::setCurrName(std::string name) {
    currName = name;
}

//get the place of the last inserted time/name (useful for checking where the player is put so that i can distinguish the most recent game played)
int Leaderboard::getLastInsertedPlace() {
    return lastInsertedPlace;
}

//this will compare the current time to all the times on the leaderboard and if the current time beats any of those times
//then it will insert the time, name into the proper place on the board.
void Leaderboard::update() {
    lastInsertedPlace = -1;
    //save the previous places in their own vectors and create a new one
    std::vector<std::string>next, temp;

    //convert currTime to each digit and then make strings (same as the one in gameWindow) (actually imma just copy it here)
    int currMin = static_cast<int>(currTime/60);
    int currSec = static_cast<int>(currTime)%60;
    std::string currMins;
    std::string currSecs;

    if (currMin < 10) {
        currMins = "0" + std::to_string(currMin);
    } else {
        currMins = std::to_string(currMin);
    }

    if (currSec < 10) {
        currSecs = "0" + std::to_string(currSec);
    } else {
        currSecs = std::to_string(currSec);
    }

    std::string strCurrTime = currMins + ":" + currSecs;
    next = {strCurrTime, currName};

    //starting with the current first place, compare the time and insert in between if needed
    for (int i = 1; i < 6; i++) {
        std::string prevTime = leaderboard.at(i)[0];
        std::stringstream ss(prevTime);

        std::string strprevMin, strprevSec;
        std::getline(ss, strprevMin, ':');
        std::getline(ss, strprevSec, ':');
        int prevMin = stoi(strprevMin);
        int prevSec = stoi(strprevSec);

        if (currMin < prevMin) {
            //current time is less than next time (insert and shift the rest down)
            temp = leaderboard[i];
            leaderboard[i] = next;
            next = temp;
            if (lastInsertedPlace == -1) {
                lastInsertedPlace = i;
            }
        } else if (currSec < prevSec && currMin == prevMin) {
            //current time is less than next time (insert and shift the rest down)
            temp = leaderboard.at(i);
            leaderboard[i] = next;
            next = temp;
            if (lastInsertedPlace == -1) {
                lastInsertedPlace = i;
            }
        } else {
            //current time is not less than next time (dont change the leaderboard)
            //move on to next place
            continue;
        }
    }
}