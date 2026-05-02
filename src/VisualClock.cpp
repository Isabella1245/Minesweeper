#include "include/VisualClock.hpp"
#include <iostream>

//class that represents the visual part of the clock on the screen (similar structure to Digits.cpp)
VisualClock::VisualClock(sf::Texture& mtexture)
    : texture(mtexture),
      offset(21)
    {
        int width = offset;
        int height = texture.getSize().y;

        for (int i = 0; i < 11; i++) {
            sf::Sprite sprite(mtexture);
            sprite.setTextureRect(sf::Rect<int>(sf::Vector2i(i*offset, 0), sf::Vector2i(width, height)));
            //this one will have 4 layers, because works with 00:00 4 digits, 2 for minutes and 2 for seconds
            digitsm1.push_back(sprite);
            digitsm2.push_back(sprite);
            digitss1.push_back(sprite);
            digitss2.push_back(sprite);
        }
    }

void VisualClock::setPosition(sf::Vector2f pos, int index, std::string place) { //set the position of a certain digit on the clock
    if (place == "m1") {
        digitsm1[index].setPosition(pos);
    } else if (place == "m2") {
        digitsm2[index].setPosition(pos);
    } else if (place == "s1") {
        digitss1[index].setPosition(pos);
    } else if (place == "s2") {
        digitss2[index].setPosition(pos);
    } else {
        std::cout << "please enter valid input (m1, m2, s1, s2)" << std::endl;
    }
}

//get the sprite for a certain digit
sf::Sprite VisualClock::getDigitm1(int index) {
    return digitsm1[index];
}
sf::Sprite VisualClock::getDigitm2(int index) {
    return digitsm2[index];
}
sf::Sprite VisualClock::getDigits1(int index) {
    return digitss1[index];
}
sf::Sprite VisualClock::getDigits2(int index) {
    return digitss2[index];
}