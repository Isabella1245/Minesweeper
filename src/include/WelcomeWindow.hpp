#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include "ScreenState.hpp"
#include "Leaderboard.hpp"

class WelcomeWindow {
    private:
        sf::RenderWindow window;
        int width;
        int height;
        std::string displayName;
        std::string userName = "";
        std::vector<sf::Text> textAttributes;
        sf::Font font;
        sf::Text welcomeText;
        sf::FloatRect wtbounds;
        sf::Text enterNameText;
        sf::FloatRect entbounds;
        sf::Text nameText;
        sf::FloatRect ntbounds;
        Leaderboard& lb;
    public:
        WelcomeWindow(int w, int h, std::string n, sf::Font& font, Leaderboard& mlb);
        void changeSize(int w, int h);
        void changeName(std::string name);
        ScreenState run();
        void displayAttributes(std::vector<sf::Text>& attributes);
        sf::RenderWindow& getWindow();
        std::string getUserName();
};