#include "include/Board.hpp"
#include <map>
#include <iostream>
#include <random>

Board::Board(int mcols, int mrows, int mmines)
    : cols(mcols),
      rows(mrows),
      mines(mmines),
      time(0),
      paused(false),
      score(mmines)
    {}

//generate a board and place mines in random locations
void Board::generateBoard(std::map<std::string, sf::Texture>& mtexture) {
    score = mines;
    texture = mtexture;
    board.clear();
    
    //create a default blank board
    for (int i = 0; i < rows; i++) {
        std::vector<Tile> row;
        for (int j = 0; j < cols; j++) {
            Tile tile(mtexture["revealed"], mtexture["revealed"], mtexture["hidden"]);
            row.push_back(tile);
        }
        board.push_back(row);
    }

    //place mines in random locations
    int temp = mines;
    while (temp > 0) {
        int x = randomNum(0, rows-1);
        int y = randomNum(0, cols-1);
        if (!getTile(x, y).getMine()) {
            getTile(x,y).setMine(true);
            getTile(x,y).setTexture(mtexture["mine"],1);
            temp-=1;
        } else {
            continue;
        }
    }

    //after mines are places, calculate adjacent mines for each tile
    calculateAdjMines();
}

//return the 2-D vector attribute of the Board class that represents the board 
std::vector<std::vector<Tile>>& Board::getBoardVec() {
    return board;
}

//return a specific tile on the board
Tile& Board::getTile(int row, int col) {
    return board[row][col];
}

//helper function to generate a random number
int Board::randomNum(int low, int high) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(gen);
}

//return the textures that are used on the board
std::map<std::string, sf::Texture>& Board::getTextures() {
    return texture;
}

//calculates the number of adjacent mines for each mine and then sets the bottom (revealed) layer of the tile 
//to that texture
void Board::calculateAdjMines() {
    //position of all neighbors relative to current tile
    int neighbors[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    //iterate through each tile
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (getTile(r,c).getMine()) {
                continue;
            }
            int count = 0;

            //for each neighbor, calculate absolute position in the grid
            for (auto& n : neighbors) {
                int nr = r + n[0];
                int nc = c + n[1];
            
                //if the position of the neighbor is valid (within the bounds of the board), increase the count if it is a mine
                if ((nr >= 0 && nr < rows) && (nc >= 0 && nc < cols)) {
                    if (getTile(nr, nc).getMine()) {
                        count +=1;
                    }
                }
            }
            getTile(r,c).setAdjMines(count);

            //i lowkey coulda probably used an if-statement but i rarely ever get to use switch case blocks and i think they look cool
            switch (count) {
                case 1:
                    getTile(r,c).setTexture(texture["1"],1);
                    break;
                case 2: 
                    getTile(r,c).setTexture(texture["2"],1);
                    break;
                case 3:
                    getTile(r,c).setTexture(texture["3"],1);
                    break;
                case 4:
                    getTile(r,c).setTexture(texture["4"],1);
                    break;
                case 5:
                    getTile(r,c).setTexture(texture["5"],1);
                    break;
                case 6:
                    getTile(r,c).setTexture(texture["6"],1);
                    break;
                case 7:
                    getTile(r,c).setTexture(texture["7"],1);
                    break;
                case 8:
                    getTile(r,c).setTexture(texture["8"],1);
                    break;
                default:
                    break;
            }
        }
    }
}

//use similar algorithm that calculated adjacent mines to reveal groups of tiles that have no adjacent mines
void Board::revealNeighbors(int r, int c) {
    //the tile this function is first called on will always be valid and will already be revealed

    if (board[r][c].getAdjMines() > 0) {
        return;
    } //if this tile has a number on it, dont reveal any more tiles

    //all the neighboring tiles
    int neighbors[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };

    //for each neighbor
    for (auto& n : neighbors) {
        int nr = r + n[0];
        int nc = c + n[1];

        //if this is a valid tile:
        if ((nr >= 0 && nr < rows) && (nc >= 0 && nc < cols)) {
            //if the tile is not a mine and is not flagged and is not already revealed: reveal it
            if (!board[nr][nc].getMine() && !board[nr][nc].getFlagged() && !board[nr][nc].getRevealed()) {
                board[nr][nc].setRevealed(true);
                //check neighbors
                revealNeighbors(nr, nc);
            }
        }
    }
}

//"score" as in the number of mines left on the board (this goes down as user places more flags)
int Board::getScore() {
    return score;
}
void Board::setScore(int n) {
    score = n;
}

bool Board::checkIfWinner() {
    //a win is defined as when the player reveals all the tiles that are not mines
    int count = 0;
    for (auto& row : board) {
        for (auto& tile : row) {
            if (tile.getRevealed() && !tile.getMine()) { //count all the revealed tiles
                count++;
            }
        }
    }
    //calculate how many non tile mines there are on the board
    int totalTiles = rows*cols;
    int totalNonMines = totalTiles-mines;
    if (count == totalNonMines) {
        return true;
    } else {
        return false;
    }
}