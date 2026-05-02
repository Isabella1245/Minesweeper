#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <vector>
#include <map>
#include "Tile.hpp"

class Board {
    private:
        int cols;
        int rows;
        int mines;
        int time;
        int score;
        bool paused;
        std::vector<std::vector<Tile>> board;
        std::map<std::string, sf::Texture> texture;
        int randomNum(int low, int high);
    public:
        Board(int mcols, int mrows, int mmines);
        void generateBoard(std::map<std::string, sf::Texture>& mtexture);
        std::vector<std::vector<Tile>>& getBoardVec();
        Tile& getTile(int row, int col);
        std::map<std::string, sf::Texture>& getTextures();
        void calculateAdjMines();
        void revealNeighbors(int r, int c);
        int getScore();
        void setScore(int n);
        bool checkIfWinner();
};