#include "include/Digits.hpp"
#include <iostream>

//this class is used to display the score on the screen
//an image containing all digits 0-9 and also the - sign was given,
//so I have to split the image and use only sections of it for each number
Digits::Digits(sf::Texture& mtexture)
    : texture(mtexture),
      offset(21) //width of each digit is 21 px
    {
        int width = offset;
        int height = texture.getSize().y;

        //there are 11 characters
        for (int i = 0; i < 11; i++) {
            sf::Sprite sprite(mtexture);
            sprite.setTextureRect(sf::Rect<int>(sf::Vector2i(i*offset, 0), sf::Vector2i(width, height)));

            //im going to use 3 groups of sprites because 3 characters/digits will be displayed on the screen at a time
            //i did this separately because a score like 011 will require 2 different sprites with the character "1"
            digitsh.push_back(sprite);
            digitst.push_back(sprite);
            digitso.push_back(sprite);
        }
    }

//set the position of a digit on the screen
//index is the specific digit (0-9 or -)
//place is if this is the hundreds, tens, or ones place, and it will correspond to the 3 groups of sprites
void Digits::setPosition(sf::Vector2f pos, int index, std::string place) {
    if (place == "hundreds") {
        digitsh[index].setPosition(pos);
    } else if (place == "tens") {
        digitst[index].setPosition(pos);
    } else if (place == "ones") {
        digitso[index].setPosition(pos);
    } else {
        //std::cout << "please enter valid input (hundreds, tens, or ones)" << std::endl;
    }
    
}

//return the sprite object of a specified character from the hundreds group
sf::Sprite Digits::getDigith(int index) {
    return digitsh[index];
}

//return the sprite object of a specified character from the tens group
sf::Sprite Digits::getDigitt(int index) {
    return digitst[index];
}

//return the sprite object of a specified character from the ones group
sf::Sprite Digits::getDigito(int index) {
    return digitso[index];
}