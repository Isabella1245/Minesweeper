#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include <map>
#include "ScreenState.hpp"
#include "Board.hpp"
#include "Digits.hpp"
#include "VisualClock.hpp"
#include "Leaderboard.hpp"

class GameWindow {
    private:
        sf::RenderWindow window;
        int width;
        int height;
        int rows;
        int cols;
        bool running;
        std::string displayName;
        std::string gameEndTime;
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Sprite> sprites;
        std::map<std::string, sf::FloatRect> bounds;
        Board& board;
        Digits digits;
        VisualClock displayClock;
        bool win;
        bool loss;
        bool debugMode;
        bool pauseMode;
        bool leaderboardMode;
        Board debugBoard;
        Board pauseBoard;
        sf::Clock clock;
        float currTime;
        bool clockRunning;
        Leaderboard& lb;
    public:
        GameWindow(int w, 
                   int h, 
                   int colCount, 
                   int rowCount, 
                   std::string n, 
                   std::map<std::string, sf::Texture>& mtextures, 
                   Board& mboard,
                   sf::Clock& c,
                   float& time,
                   bool& clockrunning,
                   Leaderboard& mlb
                );

        void changeSize(int w, int h);
        void changeName(std::string name);
        ScreenState run(bool justReturnedFromLB);
        void displayAttributes(std::map<std::string, sf::Sprite>& sprites, bool p);
        sf::RenderWindow& getWindow();
        void generateScreen();
        void setTexture(sf::Sprite& sprite, sf::Texture& texture);
        void setTileLocations();
        void displayScore(int score);
        void displayTime(float time);
        void debug(Board& b);
        void pause(Board& b);
        void setPauseState(bool paused);
        bool getPauseState();
        void setClockState(bool running);
        void setLeaderboardState(bool lbm);
        bool getWin();
        bool getLoss();
};