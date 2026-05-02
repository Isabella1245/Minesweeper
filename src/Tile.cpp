#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include <map>
#include "include/Tile.hpp"

Tile::Tile(sf::Texture& bottomLayer, sf::Texture& middleLayer, sf::Texture& topLayer) 
    : mine(false),
      flagged(false),
      revealed(false),
      adjMines(0),
      sprite({sf::Sprite(bottomLayer), sf::Sprite(middleLayer), sf::Sprite(topLayer)})
    {
        bound = sprite[0].getLocalBounds(); //was originally going to use to position tiles based on their origin but it was easier to do it based on the default top left corner
    }

//get attributes associated with each tile
bool Tile::getMine() { //whether or not the tile has a mine
    return mine;
}
bool Tile::getFlagged() { //user toggles the flagged state
    return flagged;
}
bool Tile::getRevealed() { //whether or not the tile is revealed
    return revealed;
}
int Tile::getAdjMines() { //number of adjacent mines
    return adjMines;
}
std::vector<sf::Sprite>& Tile::getSprite() { //return the layers of the sprite textures
    return sprite;
}

//change attributes of a tile
void Tile::setTexture(sf::Texture& texture, int layer) { //set one of the texture layer of a tile
    sprite[layer].setTexture(texture);
}

void Tile::setMine(bool m) { //toggle whether or not the tile has a mine
    mine = m;
}

void Tile::setFlagged(bool f) { //toggle flag
    flagged = f;
}

void Tile::setRevealed(bool r) { //toggle reveal
    revealed = r;
}

void Tile::setAdjMines(int a) { //set the number of adjacent mines
    adjMines = a;
}

void Tile::setPosition(float x, float y) { //set the position of the entire tile (based on top left corner)
    for (auto& s : sprite) {
        s.setPosition(sf::Vector2f(x, y));
    }
}