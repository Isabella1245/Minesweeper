#pragma once
#include <vector>
#include <string>
#include <map>

struct Leaderboard {
    private:
        std::map<int, std::vector<std::string>> leaderboard;
        float currTime;
        std::string currName;
        int lastInsertedPlace;
    public:
        Leaderboard(std::map<int, std::vector<std::string>>& map);
        std::map<int, std::vector<std::string>>& getLeaderboard();
        void setLeaderboard(std::map<int, std::vector<std::string>>& board);
        void setCurrTime(float time);
        void setCurrName(std::string name);
        void update();
        int getLastInsertedPlace();
};