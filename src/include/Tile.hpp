#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include <map>

class Tile {
    private:
        bool mine;
        bool flagged;
        bool revealed;
        int adjMines;
        std::map<std::string, sf::Texture> textures;
        std::vector<sf::Sprite> sprite;
        sf::FloatRect bound;
    public:
        Tile(sf::Texture& bottomLayer, sf::Texture& middleLayer, sf::Texture& topLayer);
        bool getMine();
        bool getFlagged();
        bool getRevealed();
        int getAdjMines();
        std::vector<sf::Sprite>& getSprite();
        void setTexture(sf::Texture& texture, int layer);
        void setMine(bool m);
        void setFlagged(bool f);
        void setRevealed(bool r);
        void setAdjMines(int n);
        void setPosition(float x, float y);
};