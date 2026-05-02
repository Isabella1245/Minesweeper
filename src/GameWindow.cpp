#include "include/GameWindow.hpp"
#include <iostream>
#include <cmath>

GameWindow::GameWindow(int w, 
                       int h, 
                       int colCount, 
                       int rowCount, 
                       std::string n, 
                       std::map<std::string, sf::Texture>& mtextures, 
                       Board& mboard,
                       sf::Clock& c,
                       float& time,
                       bool& cr,
                       Leaderboard& mlb)
    : width(w),
      height(h),
      rows(rowCount),
      cols(colCount),
      displayName(n),
      gameEndTime(""),
      textures(mtextures),
      board(mboard),
      running(true),
      digits(mtextures["digits"]),
      displayClock(mtextures["digits"]),
      win(false),
      loss(false),
      debugMode(false),
      pauseMode(false),
      debugBoard(mboard),
      pauseBoard(mboard),
      leaderboardMode(false),
      clock(c),
      currTime(time),
      clockRunning(cr),
      lb(mlb)//you can tell im starting to run out of names for things here
    {
        sprites.emplace("faceButton", sf::Sprite(mtextures["happyFace"]));
        //bounds.emplace("faceButton", sprites.at("faceButton").getLocalBounds());
        //sprites.at("faceButton").setOrigin(bounds.at("faceButton").getCenter());
        sprites.at("faceButton").setPosition(sf::Vector2f(float(colCount*32/2)-32, 32* float(rowCount+0.5))); 
        //sprites.at("faceButton").setPosition(sf::Vector2f(float(colCount*32/2)-32, (32*float(rowCount+0.5))+30));


        sprites.emplace("debugButton", sf::Sprite(mtextures["debug"]));
        //bounds.emplace("debugButton", sprites.at("debugButton").getLocalBounds());
        //sprites.at("debugButton").setOrigin(bounds.at("debugButton").getCenter());
        sprites.at("debugButton").setPosition(sf::Vector2f(float(colCount*32)-304, 32* float(rowCount+0.5)));
        //sprites.at("debugButton").setPosition(sf::Vector2f(float(colCount*32)-304, (32*float(rowCount+0.5))+30));


        sprites.emplace("pause", sf::Sprite(mtextures["pause"]));
        //bounds.emplace("pause", sprites.at("pause").getLocalBounds());
        //sprites.at("pause").setOrigin(bounds.at("pause").getCenter());
        sprites.at("pause").setPosition(sf::Vector2f(float(colCount*32)-240, 32*float(rowCount+0.5)));
        //sprites.at("pause").setPosition(sf::Vector2f(float(colCount*32)-240, (32*float(rowCount+0.5))+30));
        

        sprites.emplace("leaderboard", sf::Sprite(mtextures["leaderboard"]));
        //bounds.emplace("leaderboard", sprites.at("leaderboard").getLocalBounds());
        //sprites.at("leaderboard").setOrigin(bounds.at("leaderboard").getCenter());
        sprites.at("leaderboard").setPosition(sf::Vector2f(float(colCount*32)-176, 32*float(rowCount+0.5)));
        //sprites.at("leaderboard").setPosition(sf::Vector2f(float(colCount*32)-176, (32*float(rowCount+0.5))+30));

        setTileLocations();
    }

//generate the screen separate from the constructor so that it does not appear upon initalization of the program
void GameWindow::generateScreen() {
    window = sf::RenderWindow(sf::VideoMode({unsigned(width), unsigned(height)}), displayName, sf::Style::Titlebar | sf::Style::Close);
}

//change size and display title of the window
void GameWindow::changeSize(int w, int h) {
    width = w;
    height = h;
    window.setSize(sf::Vector2u(unsigned(width), unsigned(height)));
}
void GameWindow::changeName(std::string name) {
    displayName = name;
    window.setTitle(displayName);
}

//handles displaying all sprites (tiles/buttons/timer/score)
void GameWindow::displayAttributes(std::map<std::string, sf::Sprite>& msprites, bool pause) {
    setTileLocations(); //because tiles change textures all the time in the game, i have set tile locations running to make sure they dont mysteriously move
    for (auto iter = msprites.begin(); iter != msprites.end(); iter++) {
        window.draw(iter->second); //drawing all button sprites on the screen
    }

    //handles which layers of each tile is displayed based on game mode
    //Layer Chart:
    //0- plain revealed tile
    //1- either a mine, number (adjacent mines), or another plain revealed tile
    //2- hidden tile
    //3- flag
    if (!debugMode && !pauseMode && !pause) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                window.draw(board.getTile(r,c).getSprite()[0]);
                window.draw(board.getTile(r,c).getSprite()[1]);
                if (!board.getTile(r,c).getRevealed()) {
                    window.draw(board.getTile(r,c).getSprite()[2]);
                }
                if (board.getTile(r,c).getFlagged()) {
                    window.draw(board.getTile(r,c).getSprite()[3]);
                }
            }
        }
    //debug mode and pause mode have their own "boards"
    //debug displays all revealed tiles and marks which tiles are mines
    //pause is all hidden tiles
    } else if (debugMode && !pauseMode) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                window.draw(debugBoard.getTile(r,c).getSprite()[0]); //revealed tile
                window.draw(debugBoard.getTile(r,c).getSprite()[1]); //mine or revealed tile
            }
        }
    } else if (pauseMode || pause) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                window.draw(pauseBoard.getTile(r,c).getSprite()[0]); //hidden tile
            }
        }
    }

    displayScore(board.getScore()); //update score
    displayTime(currTime); //update time
}

//get window object
sf::RenderWindow& GameWindow::getWindow() {
    return window;
}

//set the texture to a certain sprite
void GameWindow::setTexture(sf::Sprite& sprite, sf::Texture& texture) {
    sprite.setTexture(texture);
}

//set default locations for all tiles on the board
void GameWindow::setTileLocations() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            board.getTile(r,c).setPosition(float(c*32), float(r*32));
            debugBoard.getTile(r,c).setPosition(float(c*32), float(r*32));
            pauseBoard.getTile(r,c).setPosition(float(c*32), float(r*32));
        }
    }
}

//display the score (number of mines left on the board)
void GameWindow::displayScore(int score) {
    //first split score into 3 digits
    int hundreds = (std::abs(score)/100) %10;
    int tens = (std::abs(score)/10) %10;
    int ones = std::abs(score) %10;

    if (score < 0) {
        hundreds = 10; //index of the minus sign in the digits vector
    }

    //location of each digit on the screen
    sf::Vector2f hundredsPos(float(12), 32*float(rows+0.5)+16);
    sf::Vector2f tensPos(float(33), 32*float(rows+0.5)+16);
    sf::Vector2f onesPos(float(33+21), 32*float(rows+0.5)+16);

    //set position of each digit
    digits.setPosition(hundredsPos, hundreds, "hundreds");
    digits.setPosition(tensPos, tens, "tens");
    digits.setPosition(onesPos, ones, "ones");

    //display on screen the current digit
    window.draw(digits.getDigith(hundreds));
    window.draw(digits.getDigitt(tens));
    window.draw(digits.getDigito(ones));
}

//similar to display score
void GameWindow::displayTime(float time) {
    //get the current time
    int min = static_cast<int>(currTime/60);
    int sec = static_cast<int>(currTime)%60;

    //split into 4 digits (2 for min and 2 for sec)
    int mt = (std::abs(min)/10) %10;
    int mo = std::abs(min) %10;

    int st = (std::abs(sec)/10) %10;
    int so = std::abs(sec) %10;

    //set position of each digit
    sf::Vector2f mtpos(float(cols*32)-97, 32*float(rows+0.5)+16);
    sf::Vector2f mopos(float(cols*32)-97+21, 32*float(rows+0.5)+16);
    sf::Vector2f stpos(float(cols*32)-54, 32*float(rows+0.5)+16);
    sf::Vector2f sopos(float(cols*32)-54+21, 32*float(rows+0.5)+16);

    displayClock.setPosition(mtpos, mt, "m1");
    displayClock.setPosition(mopos, mo, "m2");
    displayClock.setPosition(stpos, st, "s1");
    displayClock.setPosition(sopos, so, "s2");

    //display digits on screen
    window.draw(displayClock.getDigitm1(mt));
    window.draw(displayClock.getDigitm2(mo));
    window.draw(displayClock.getDigits1(st));
    window.draw(displayClock.getDigits2(so));
}

//generate the debugged board for the current game
void GameWindow::debug(Board& b) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            debugBoard.getTile(r,c).getSprite().clear();
            debugBoard.getTile(r,c).getSprite().push_back(sf::Sprite(debugBoard.getTextures()["hidden"]));
            if (b.getTile(r,c).getMine()) {
                debugBoard.getTile(r,c).getSprite().push_back(sf::Sprite(debugBoard.getTextures()["mine"]));
            } else {
                debugBoard.getTile(r,c).getSprite().push_back(sf::Sprite(debugBoard.getTextures()["hidden"]));
            }
        }
    }
}

//generate the paused board for the current game
void GameWindow::pause(Board& b) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            pauseBoard.getTile(r,c).getSprite().clear();
            pauseBoard.getTile(r,c).getSprite().push_back(sf::Sprite(debugBoard.getTextures()["revealed"]));
        }
    }
}

//toggle pause
void GameWindow::setPauseState(bool paused) {
    pauseMode = paused;
}

//toggle clock
void GameWindow::setClockState(bool run) {
    clockRunning = run;
}

//toggle leaderboard mode
void GameWindow::setLeaderboardState(bool lbs) {
    leaderboardMode = lbs;
}

//self explanatory?
bool GameWindow::getWin() {
    return win;
}
bool GameWindow::getLoss() {
    return loss;
}
bool GameWindow::getPauseState() {
    return pauseMode;
}

//this is the big one
//brace yourself
ScreenState GameWindow::run(bool justReturnedFromLB) {
    while (window.isOpen())
    {
        //ts is the right spot (had to do a little testing and searching)
        //if the game screen is coming from the leaderboard
        if (justReturnedFromLB && !win && !loss && !debugMode) {
            clock.restart();
            justReturnedFromLB = false;
            //clockRunning = true;
        }
        //add to the current time
        if (clockRunning) {
            currTime += clock.restart().asSeconds();
        } else {
            clock.restart();
        }
        //if all non mine tiles are reveaeld, flag all mines that arent flagged
        if (win) {
            for (auto& row : board.getBoardVec()) {
                for (auto& tile : row) {
                    if (tile.getMine()) {
                        tile.setFlagged(true);
                        tile.getSprite().push_back(sf::Sprite(board.getTextures()["flag"]));
                        board.setScore(0);
                    }
                }
            }
        }
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return EXIT;
            }

            //handles all keyboard input (shouldnt do anything)
            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;
            }

            //all events are handled in here
            if (event->is<sf::Event::MouseButtonPressed>()) {
                //get location of the mouse
                auto localMousePos = event->getIf<sf::Event::MouseButtonPressed>()->position;
                auto mousePos = window.mapPixelToCoords(localMousePos);
                auto button = event->getIf<sf::Event::MouseButtonPressed>()->button;

                //check which mouse button is being pressed
                if (button == sf::Mouse::Button::Left) {
                    //LEFT CLICK

                    //leaderboard button
                    if (sprites.at("leaderboard").getGlobalBounds().contains(mousePos) && !leaderboardMode) {
                        pause(pauseBoard);
                        displayAttributes(sprites, true);
                        clockRunning = false;
                        leaderboardMode = true;

                        //force window display (this is kinda chopped but its working)
                        window.display();
                        return LEADERBOARD;

                    //pause button
                    } else if (sprites.at("pause").getGlobalBounds().contains(mousePos) && !leaderboardMode && !win && !loss) {
                        if (!pauseMode) {
                            setTexture(sprites.at("pause"), textures.at("play"));
                            pause(pauseBoard);
                            pauseMode = true;
                            running = false;
                            clockRunning = false;

                        } else if (pauseMode) {
                            setTexture(sprites.at("pause"), textures.at("pause"));
                            pauseMode = false;
                            running = true;
                            clock.restart();
                            clockRunning = true;
                        }
                    
                    //restart button
                    } else if (sprites.at("faceButton").getGlobalBounds().contains(mousePos) && !leaderboardMode) {
                        debugMode = false;
                        pauseMode = false;
                        board.generateBoard(board.getTextures());
                        setTileLocations();
                        setTexture(sprites.at("faceButton"), textures.at("happyFace"));
                        setTexture(sprites.at("pause"), textures.at("pause"));
                        running = true;
                        win = false;
                        loss = false;
                        currTime = 0;
                        clockRunning = false;

                    //debug button
                    } else if (sprites.at("debugButton").getGlobalBounds().contains(mousePos) && running && !leaderboardMode && !win && !loss) {
                        if (!debugMode) {
                            debug(board);
                            debugMode = true;
                            clockRunning = false;

                        } else if (debugMode) {
                            debugMode = false;
                            clockRunning = true;
                        }

                    //clicking somewhere else on the screen
                    }  else {
                        if (!debugMode && !leaderboardMode && !win && !loss) {
                            int r = 0;
                            for (auto& row : board.getBoardVec()) {
                                int c = 0;
                                for (auto& tile : row) {
                                    //if any tiles are clicked, and the game is in the appropriate state (not paused or debugged or leaderboard)
                                    if (!tile.getRevealed() && tile.getSprite()[2].getGlobalBounds().contains(mousePos) && running && !tile.getFlagged()) {
                                        
                                        if (!clockRunning) {
                                            clock.restart();
                                            clockRunning = true;
                                        }
                                        //reveal tile
                                        tile.setRevealed(true);

                                        //check if its a mine, end the game if it is
                                        if (tile.getMine()) {
                                            clockRunning = false;
                                            loss = true;
                                            sprites.at("faceButton").setTexture(textures.at("loseFace")); //toggle lose face
                                            running = false;
                                            //flagg all mines
                                            for (auto& row : board.getBoardVec()) {
                                                for (auto& tile : row) {
                                                    if (tile.getMine()) {
                                                        tile.setRevealed(true);
                                                        tile.getSprite().push_back(sf::Sprite(board.getTextures()["flag"]));
                                                    }
                                                }
                                            }
                                        } else {
                                            //if its not a mine, reveal all non-mine neighbors
                                            board.revealNeighbors(r, c);
                                        }

                                        //check the board to see if all non mine tiles are revealed, if it is, end the game
                                        if (board.checkIfWinner()) {
                                            sprites.at("faceButton").setTexture(textures["winFace"]);
                                            running = false;
                                            win = true;
                                            clockRunning = false;
                                            lb.setCurrTime(currTime);
                                            lb.update();
                                        }
                                    }
                                    c++;
                                }
                                r++;
                            }
                        }
                    }
                } else if (button == sf::Mouse::Button::Right && !debugMode && !pauseMode && !leaderboardMode && !win && !loss) {
                    //RIGHT CLICK (tiles only, toggles flag state)
                    for (auto& row : board.getBoardVec()) {
                        for (auto& tile : row) {
                            //flag
                            if (tile.getSprite()[2].getGlobalBounds().contains(mousePos) && !tile.getRevealed() && running && !tile.getFlagged()) {
                                if (!clockRunning) {
                                    clock.restart();
                                    clockRunning = true;
                                }
                                tile.setFlagged(true);
                                tile.getSprite().push_back(sf::Sprite(board.getTextures()["flag"]));
                                board.setScore(board.getScore() - 1);

                            //unflag
                            } else if (tile.getSprite()[2].getGlobalBounds().contains(mousePos) && !tile.getRevealed() && running && tile.getFlagged()) {
                                if (!clockRunning) {
                                    clock.restart();
                                    clockRunning = true;
                                }
                                tile.setFlagged(false);
                                tile.getSprite().pop_back();
                                board.setScore(board.getScore() + 1);
                            }
                        }
                    }
                }
            }
        }
        //this should stay relatively clean
        window.clear(sf::Color::White);
        displayAttributes(sprites, false);
        window.display();
    }
    //lowk dont think this return statement is ever reached but this is more of a safety measure than anything
    return EXIT;
}