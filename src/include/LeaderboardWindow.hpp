#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include "ScreenState.hpp"
#include "Leaderboard.hpp"

class LeaderboardWindow {
    Leaderboard& leaderboard;
    std::string currName;
    sf::Font font;
    sf::RenderWindow window;
    int width;
    int height;
    std::string displayName;
    sf::Text titleText;
    sf::FloatRect bounds;
    bool returnFromLeaderboard;
    //std::vector<sf::Text> textAttributes;
    sf::Text display;
    // sf::Text second;
    // sf::Text third;
    // sf::Text fourth;
    // sf::Text fifth;
    //current time;
    public:
        LeaderboardWindow(int w, int h, std::string n, sf::Font& f, Leaderboard& board);
        void generateScreen();
        void changeSize(int w, int h);
        void changeName(std::string name);
        ScreenState run();
        void displayAttributes();
        sf::RenderWindow& getWindow();
        bool getReturn();
};