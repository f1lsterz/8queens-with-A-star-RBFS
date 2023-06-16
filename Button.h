#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "constants.h"

using namespace constants;
using namespace std;
using namespace sf;

class Label {
protected:
    double x;               // X-coordinate of the label's position
    double y;               // Y-coordinate of the label's position
    std::string text;       // Text content of the label
    sf::Text TXT;           // SFML Text object for rendering the label
    sf::Font None;          // SFML Font object for the label's text

public:
    Label(double _x = 0, double _y = 0, std::string _text = "");
    // Constructor for the Label class. Initializes the label's position (x, y) and text content (_text).

    void setText(const std::string&);
    // Sets the text content of the label to the specified string.

    void setText(const std::string&, int);
    // Sets the text content of the label and the font size simultaneously.

    void setColor(const sf::Color&);
    // Sets the color of the label's text.

    void setFontSize(unsigned int);
    // Sets the font size of the label's text.

    sf::Text displayText();
    // Returns the SFML Text object for rendering the label's text.
};

class Button : public Label {
private:
    double width;           // Width of the button
    double height;          // Height of the button
    RectangleShape BOX;     // SFML RectangleShape object for rendering the button

public:
    Button(double _x = 0, double _y = 0, double _width = 100, double _height = 50, std::string _text = "Кнопка");
    // Constructor for the Button class. Initializes the button's position (x, y), dimensions (width, height), and text content (_text).

    bool select(Vector2i);
    // Checks if the button is selected (clicked) based on the provided mouse position.

    RectangleShape displayButton();
    // Returns the SFML RectangleShape object for rendering the button.

    Vector2f getPosition();
    // Returns the position (x, y) of the button.

    Vector2f getSize();
    // Returns the dimensions (width, height) of the button.

    void setPosition(double, double);
    // Sets the position (x, y) of the button.

    void setScale(double, double);
    // Sets the scale of the button.

    void setSize(double, double);
    // Sets the dimensions (width, height) of the button.
};