#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include <map>

class Digits {
    private:
        sf::Texture& texture;
        sf::FloatRect bounds;
        std::vector<sf::Sprite> digitsh;
        std::vector<sf::Sprite> digitst;
        std::vector<sf::Sprite> digitso;
        int offset;
    public:
        Digits(sf::Texture& inputTexture);
        void setPosition(sf::Vector2f, int index, std::string place);
        sf::Sprite getDigith(int index);
        sf::Sprite getDigitt(int index);
        sf::Sprite getDigito(int index);
};