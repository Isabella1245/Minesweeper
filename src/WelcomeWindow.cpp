#include "include/WelcomeWindow.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

//because the font is loaded from a file, i don't want to initialize it in the constructor or anywhere else in the class,
//so for all the windows, I'll probably have a sf::Font& as a parameter because its pointless to load a new one every time anyways
WelcomeWindow::WelcomeWindow(int w, int h, std::string n, sf::Font& globalFont, Leaderboard& mlb) 
    : width(w),
      height(h), 
      displayName(n),
      window(sf::VideoMode({unsigned(w), unsigned(h)}), n, sf::Style::Titlebar | sf::Style::Close),
      welcomeText(globalFont, "WELCOME TO MINESWEEPER!", 24),
      enterNameText(globalFont, "Enter your name:", 20),
      nameText(globalFont, userName, 18),
      lb(mlb)
      { //initialize all attributes of the game window and append all text to the text attributes list for displaying
        font = globalFont;

        wtbounds = welcomeText.getLocalBounds();
        welcomeText.setOrigin(wtbounds.getCenter());
        welcomeText.setPosition(sf::Vector2f(float(width/2), float(height/2)-150));
        
        entbounds = enterNameText.getLocalBounds();
        enterNameText.setOrigin(entbounds.getCenter());
        enterNameText.setPosition(sf::Vector2f(float(width/2), float(height/2)-75));

        ntbounds = nameText.getLocalBounds();
        nameText.setOrigin(ntbounds.getCenter());
        nameText.setFillColor(sf::Color::Yellow);
        nameText.setPosition(sf::Vector2f(float(width/2), float(height/2)-45));

        textAttributes.push_back(welcomeText); //index 0
        textAttributes.push_back(enterNameText); //index 1
        textAttributes.push_back(nameText); //index 2
      }

//change the dimensions of the sf::RenderWindow
void WelcomeWindow::changeSize(int w, int h) {
    width = w;
    height = h;
    window.setSize(sf::Vector2u(width, height));
}
//change the display name of the sf::RenderWindow
void WelcomeWindow::changeName(std::string name) {
    displayName = name;
    window.setTitle(displayName);
}
//return the sf::RenderWindow object
sf::RenderWindow& WelcomeWindow::getWindow() {
    return window;
}
//unique to the welcome screen, all username handling will go through this class; returns the users namae
std::string WelcomeWindow::getUserName() {
    return userName;
}
//handles drawing everything to the window (the welcome window only has text attributes, so this works simply)
//also lowkey handle recentering the text every time the user makes a change
void WelcomeWindow::displayAttributes(std::vector<sf::Text>& attributes) {
    ntbounds = nameText.getLocalBounds();
    nameText.setOrigin(ntbounds.getCenter());
    nameText.setPosition(sf::Vector2f(float(width/2), float(height/2)-45));
    nameText.setString(userName + "|");
    attributes[2] = nameText;

    for (auto item : attributes) {
        window.draw(item);
    }
}

//handles running the welcome screen
//when it is done, returns the state of the game (the screen that should be displayed next)
//for the welcome screen, it is simple (will always either be EXIT or GAME)
ScreenState WelcomeWindow::run() {
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return EXIT;
            }

            //handles all keyboard input
            if (event->is<sf::Event::KeyPressed>()) {
                auto key = event->getIf<sf::Event::KeyPressed>()->code;

                //the enter key should take the user to the game screen if the user has inputted a username,
                //otherwise, it should do nothing
                if (key == sf::Keyboard::Key::Enter) {
                    if (userName.size() >=1) {
                        lb.setCurrName(userName);
                        window.close();
                        return GAME;
                    }
                } //user can delete characters from their username
                if (userName.size() >= 1 && key == sf::Keyboard::Key::Backspace) {
                    userName.pop_back();
                }
                //max username length is 10 characters
                if (userName.size() < 10) {
                    //this genuinely handles each letter individually
                    //I hate sfml for this theres gotta be a better way to do this vrochacho
                    if (key == sf::Keyboard::Key::A) {
                        if (userName.size() == 0) {
                        userName.append("A");
                        } else {
                        userName.append("a");
                        }
                    } else if (key == sf::Keyboard::Key::B) {
                        if (userName.size() == 0) {
                        userName.append("B");
                        } else {
                        userName.append("b");
                        }
                    } else if (key == sf::Keyboard::Key::C) {
                        if (userName.size() == 0) {
                        userName.append("C");
                        } else {
                        userName.append("c");
                        }
                    } else if (key == sf::Keyboard::Key::D) {
                        if (userName.size() == 0) {
                        userName.append("D");
                        } else {
                        userName.append("d");
                        }
                    } else if (key == sf::Keyboard::Key::E) {
                        if (userName.size() == 0) {
                        userName.append("E");
                        } else {
                        userName.append("e");
                        }
                    } else if (key == sf::Keyboard::Key::F) {
                        if (userName.size() == 0) {
                        userName.append("F");
                        } else {
                        userName.append("f");
                        }
                    } else if (key == sf::Keyboard::Key::G) {
                        if (userName.size() == 0) {
                        userName.append("G");
                        } else {
                        userName.append("g");
                        }
                    } else if (key == sf::Keyboard::Key::H) {
                        if (userName.size() == 0) {
                        userName.append("H");
                        } else {
                        userName.append("h");
                        }
                    } else if (key == sf::Keyboard::Key::I) {
                        if (userName.size() == 0) {
                        userName.append("I");
                        } else {
                        userName.append("i");
                        }
                    } else if (key == sf::Keyboard::Key::J) {
                        if (userName.size() == 0) {
                        userName.append("J");
                        } else {
                        userName.append("j");
                        }
                    } else if (key == sf::Keyboard::Key::K) {
                        if (userName.size() == 0) {
                        userName.append("K");
                        } else {
                        userName.append("k");
                        }
                    } else if (key == sf::Keyboard::Key::L) {
                        if (userName.size() == 0) {
                        userName.append("L");
                        } else {
                        userName.append("l");
                        }
                    } else if (key == sf::Keyboard::Key::M) {
                        if (userName.size() == 0) {
                        userName.append("M");
                        } else {
                        userName.append("m");
                        }
                    } else if (key == sf::Keyboard::Key::N) {
                        if (userName.size() == 0) {
                        userName.append("N");
                        } else {
                        userName.append("n");
                        }
                    } else if (key == sf::Keyboard::Key::O) {
                        if (userName.size() == 0) {
                        userName.append("O");
                        } else {
                        userName.append("o");
                        }
                    } else if (key == sf::Keyboard::Key::P) {
                        if (userName.size() == 0) {
                        userName.append("P");
                        } else {
                        userName.append("p");
                        }
                    } else if (key == sf::Keyboard::Key::Q) {
                        if (userName.size() == 0) {
                        userName.append("Q");
                        } else {
                        userName.append("q");
                        }
                    } else if (key == sf::Keyboard::Key::R) {
                        if (userName.size() == 0) {
                        userName.append("R");
                        } else {
                        userName.append("r");
                        }
                    } else if (key == sf::Keyboard::Key::S) {
                        if (userName.size() == 0) {
                        userName.append("S");
                        } else {
                        userName.append("s");
                        }
                    } else if (key == sf::Keyboard::Key::T) {
                        if (userName.size() == 0) {
                        userName.append("T");
                        } else {
                        userName.append("t");
                        }
                    } else if (key == sf::Keyboard::Key::U) {
                        if (userName.size() == 0) {
                        userName.append("U");
                        } else {
                        userName.append("u");
                        }
                    } else if (key == sf::Keyboard::Key::V) {
                        if (userName.size() == 0) {
                        userName.append("V");
                        } else {
                        userName.append("v");
                        }
                    } else if (key == sf::Keyboard::Key::W) {
                        if (userName.size() == 0) {
                        userName.append("W");
                        } else {
                        userName.append("w");
                        }
                    } else if (key == sf::Keyboard::Key::X) {
                        if (userName.size() == 0) {
                        userName.append("X");
                        } else {
                        userName.append("x");
                        }
                    } else if (key == sf::Keyboard::Key::Y) {
                        if (userName.size() == 0) {
                        userName.append("Y");
                        } else {
                        userName.append("y");
                        }
                    } else if (key == sf::Keyboard::Key::Z) {
                        if (userName.size() == 0) {
                        userName.append("Z");
                        } else {
                        userName.append("z");
                        }
                    } 
                }
            
            }
        }
        //this should stay relatively clean
        window.clear(sf::Color::Blue);
        displayAttributes(textAttributes);
        window.display();
    }
    //lowk dont think this return statement is ever reached but this is more of a safety measure than anything
    return EXIT;
}