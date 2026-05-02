#include "include/LeaderboardWindow.hpp"
#include <iostream>

LeaderboardWindow::LeaderboardWindow(int w,
                                     int h,
                                     std::string n,
                                     sf::Font& f,
                                     Leaderboard& board)
    : width(w),
      height(h),
      font(f),
      leaderboard(board),
      titleText(f, "LEADERBOARD", 20),
      display(f, "", 18),
      returnFromLeaderboard(false)
    {
        titleText.setFillColor(sf::Color::White);
        bounds = titleText.getLocalBounds();
        titleText.setOrigin(bounds.getCenter());
        titleText.setPosition(sf::Vector2f(float(width/2), float(height/2)-120));

        auto& lb = leaderboard.getLeaderboard();
        std::string text;

        for (int i = 1; i <= 5; i++) {
            text += std::to_string(i) + ".    " + lb[i][0] + "    " + lb[i][1] + "\n\n";
        }

        display.setString(text);

        display.setFillColor(sf::Color::White);
        bounds = display.getLocalBounds();
        display.setOrigin(bounds.getCenter());
        display.setPosition(sf::Vector2f(float(width/2), float(height/2)+20));
    }

//generate the screen outside the constructor to prevent it from opening on startup
//focus to the leaderboard so the user cant interact with the game screen while the leaderboard screen is active
void LeaderboardWindow::generateScreen() {
    window = sf::RenderWindow(sf::VideoMode({unsigned(width), unsigned(height)}), displayName, sf::Style::Titlebar | sf::Style::Close);
    bool ok = window.setActive(true);
    window.requestFocus();
}

void LeaderboardWindow::changeSize(int w, int h) {
    width = w;
    height = h;
    window.setSize(sf::Vector2u(unsigned(width), unsigned(height)));
}

//the display title on the window
void LeaderboardWindow::changeName(std::string n) {
    displayName = n;
    window.setTitle(displayName);
}

//this will return true if the user closes the leaderboard
bool LeaderboardWindow::getReturn() {
    return returnFromLeaderboard;
}

//function that displays all visual attributes, to be called periodically
void LeaderboardWindow::displayAttributes() {
    auto& lb = leaderboard.getLeaderboard();
    std::string text;
    int star = leaderboard.getLastInsertedPlace(); //mark the last game played on the leaderboard with a *, if it is on the leaderboard

    for (int i = 1; i <= 5; i++) {
        text += std::to_string(i) + ".    " + lb[i][0] + "    " + lb[i][1];
        if (i == star) {
            text += "*";
        }
        text+="\n\n";
    }

    display.setString(text);

    bounds = display.getLocalBounds();
    display.setOrigin(bounds.getCenter());                
    
    window.draw(titleText);
    window.draw(display);
}

sf::RenderWindow& LeaderboardWindow::getWindow() {
    return window;
}

//this is the loop that runs when the leaderboard screen is active
//will return which screen to go to next when it is done
ScreenState LeaderboardWindow::run() {
\
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) {
                window.close();
                returnFromLeaderboard = true;
                return GAME;
            }

            //prevent user from clicking away from the leaderboard screen
            if (event->is<sf::Event::FocusLost>()) {
                window.requestFocus();
            }

        }
        //this should stay relatively clean
        window.clear(sf::Color::Blue);
        displayAttributes();
        window.display();
    }
    //lowk dont think this return statement is ever reached but this is more of a safety measure than anything
    return EXIT;
}