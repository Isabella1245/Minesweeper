#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "include/WelcomeWindow.hpp"
#include "include/ScreenState.hpp"
#include "include/GameWindow.hpp"
#include "include/Board.hpp"
#include "include/LeaderboardWindow.hpp"
#include "include/Leaderboard.hpp"

//helper to load all the textures
void loadTextures(std::map<std::string, sf::Texture>& gameTextures, std::map<std::string, sf::Texture>& mineTextures) {
    sf::Texture tex;
    bool okg = tex.loadFromFile("files/images/face_happy.png");
    gameTextures.emplace("happyFace", tex);
    okg = tex.loadFromFile("files/images/debug.png");
    gameTextures.emplace("debug", tex);
    okg = tex.loadFromFile("files/images/pause.png");
    gameTextures.emplace("pause", tex);
    okg = tex.loadFromFile("files/images/leaderboard.png");
    gameTextures.emplace("leaderboard", tex);
    okg = tex.loadFromFile("files/images/play.png");
    gameTextures.emplace("play", tex);
    okg = tex.loadFromFile("files/images/face_lose.png");
    gameTextures.emplace("loseFace", tex);
    okg = tex.loadFromFile("files/images/face_win.png");
    gameTextures.emplace("winFace", tex);
    okg = tex.loadFromFile("files/images/digits.png");
    gameTextures.emplace("digits", tex);
    if (!okg) {
        std::cout << "one or more textures failed to load." << std::endl;
    }

    bool okm = tex.loadFromFile("files/images/flag.png");
    mineTextures.emplace("flag", tex);
    okm = tex.loadFromFile("files/images/mine.png");
    mineTextures.emplace("mine", tex);
    okm = tex.loadFromFile("files/images/tile_hidden.png");
    mineTextures.emplace("hidden", tex);
    okm = tex.loadFromFile("files/images/tile_revealed.png");
    mineTextures.emplace("revealed", tex);

    okm = tex.loadFromFile("files/images/number_1.png");
    mineTextures.emplace("1", tex);
    okm = tex.loadFromFile("files/images/number_2.png");
    mineTextures.emplace("2", tex);
    okm = tex.loadFromFile("files/images/number_3.png");
    mineTextures.emplace("3", tex);
    okm = tex.loadFromFile("files/images/number_4.png");
    mineTextures.emplace("4", tex);
    okm = tex.loadFromFile("files/images/number_5.png");
    mineTextures.emplace("5", tex);
    okm = tex.loadFromFile("files/images/number_6.png");
    mineTextures.emplace("6", tex);
    okm = tex.loadFromFile("files/images/number_7.png");
    mineTextures.emplace("7", tex);
    okm = tex.loadFromFile("files/images/number_8.png");
    mineTextures.emplace("8", tex);
}

//read the leaderboard txt file and return a leaderboard object
Leaderboard loadLeaderboard(const std::string& filename) {
    std::ifstream file(filename);
    std::map<int, std::vector<std::string>> map;
    std::vector<std::string> data;
    if (!file.is_open()) {
        std::cerr << "FAILED to open leaderboard.txt\n";
    }
    std::string line;
    int place = 1;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, time;

        std::getline(ss, time, ',');
        std::getline(ss, name, ',');
        data.clear();
        data.push_back(time);
        data.push_back(name);
        map.emplace(place, data);
        place++;
    }
    
    return Leaderboard(map);
}

//write the current leaderboard object to the leadboard txt file
void writeLeaderboard(Leaderboard& lb) {
    std::ofstream file("files/leaderboard.txt");
    for (auto iter = lb.getLeaderboard().begin(); iter != lb.getLeaderboard().end(); iter++) {
        std::string line;
        line = (iter->second)[0] + "," + (iter->second)[1];
        file << line << "\n";
    }
}

//load the configuration settings from cfg file
bool loadConfig(const std::string& filename, std::vector<int>& cfg) {
    std::ifstream config(filename);
    if (!config.is_open()) {
        std::cerr << "FAILED to open config.cfg\n";
        return false;
    }
    int a = 0, b = 0, c = 0;
    config >> a >> b >> c;
    cfg.push_back(a);
    cfg.push_back(b);
    cfg.push_back(c);
    return true;
}

int main() {
    std::vector<int> cfg = {}; //colCount, rowCount, mineCount
    std::string configPath = "files/config.cfg";
    sf::Font font("files/font.ttf");

    std::map<std::string, sf::Texture> gameTextures;
    std::map<std::string, sf::Texture> mineTextures;

    sf::Clock gameClock;
    float elapsedTime = 0;
    bool clockRunning = false;
    bool running = true;

    loadConfig(configPath, cfg); //load config
    loadTextures(gameTextures, mineTextures); //load all image files
    Leaderboard leaderboard = loadLeaderboard("files/leaderboard.txt"); //load leaderboard file

    //screen dimensions
    int welwidth, welheight, gamewidth, gameheight, leadwidth, leadheight;
    welwidth= cfg[0] * 32;
    welheight = (cfg[1] * 32) + 100;
    gamewidth = cfg[0] * 32;
    gameheight = (cfg[1] * 32) + 100;
    leadwidth = cfg[0] * 16;
    leadheight = (cfg[1] * 16) + 50;

    //create all windows here
    WelcomeWindow welcomeWindow(welwidth, welheight, "Minesweeper", font, leaderboard);
    Board board(cfg[0], cfg[1], cfg[2]);
    board.generateBoard(mineTextures);
    GameWindow gameWindow(gamewidth, gameheight, cfg[0], cfg[1], "Minesweeper", gameTextures, board, gameClock, elapsedTime, clockRunning, leaderboard);
    bool initialized = false;
    LeaderboardWindow leaderboardWindow(leadwidth, leadheight, "Minesweeper", font, leaderboard);
    
    //start of game 
    ScreenState state = WELCOME;

    while (running) {
        switch (state) {
            case WELCOME: //if the current Screen state is WELCOME, the welcome screen should run
                state = welcomeWindow.run();
                break;
            case GAME: //if the current Screen state is GAME, the game screen should generate, and then run
                if (!initialized) {
                    gameWindow.generateScreen();
                    initialized = true;
                }
                //when the game window starts, if returning from the leaderboard screen, don't restart the clock
                //if its not coming from the leaderboard screen, that means a new game is starting, and the clock should reset
                if (leaderboardWindow.getReturn()) {
                    state = gameWindow.run(true);
                } else {
                    state = gameWindow.run(false);
                }
                break;
            case LEADERBOARD: //if the current Screen state is LEADERBOARD, the leaderboard screen should generate, and then run
                //update the leaderboard.txt file whenever the leaderboard is toggled
                writeLeaderboard(leaderboard);
                leaderboardWindow.generateScreen();
                state = leaderboardWindow.run();
                if (!gameWindow.getWin() && !gameWindow.getLoss() && !gameWindow.getPauseState()) {
                    gameWindow.setClockState(true); //if the game is running (not win/loss/paused), the clock should continue to run
                }
                gameWindow.setPauseState(false); //unpause when done
                gameWindow.setLeaderboardState(false); //turn off leaderboard mode when done
                //leaderboard will always return to the GAME state
                break;
            case EXIT: //if the user exits out of the welcome or game screen, the game ends
                writeLeaderboard(leaderboard); //update the leaderboard.txt file
                running = false;
                break;
        };
    }
    return 0;
}