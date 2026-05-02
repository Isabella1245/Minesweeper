#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include <map>

class VisualClock {
    private:
        sf::Texture& texture;
        sf::FloatRect bounds;
        std::vector<sf::Sprite> digitsm1;
        std::vector<sf::Sprite> digitsm2;
        std::vector<sf::Sprite> digitss1;
        std::vector<sf::Sprite> digitss2;
        int offset;
    public:
        VisualClock(sf::Texture& inputTexture);
        void setPosition(sf::Vector2f, int index, std::string place);
        sf::Sprite getDigitm1(int index);
        sf::Sprite getDigitm2(int index);
        sf::Sprite getDigits1(int index);
        sf::Sprite getDigits2(int index);
};