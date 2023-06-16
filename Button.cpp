#include "Button.h"

Label::Label(double _x, double _y, string _text)
    : x(_x), y(_y), text(_text)
{
    None.loadFromFile("Exo2-VariableFont_wght.ttf");

    TXT.setFont(None);
    TXT.setCharacterSize(16);
    TXT.setFillColor(Color::White);
    TXT.setPosition(x, y);
}

void Label::setText(const string& _text)
{
    text = _text;
}

void Label::setText(const std::string& _text, int n)
{
    text = _text + to_string(n);
}

Text Label::displayText()
{
    TXT.setString(text);
    return TXT;
}

void Label::setColor(const sf::Color& color)
{
    TXT.setFillColor(color);
}

void Label::setFontSize(unsigned int size)
{
    TXT.setCharacterSize(size);
}


Button::Button(double _x, double _y, double _width, double _height, string _text)
    : Label(_x, _y, _text)
{
    None.loadFromFile("Exo2-VariableFont_wght.ttf");

    width = _width;
    height = _height;
    text = _text;
    TXT.setFont(None);
    TXT.setCharacterSize(16);
    TXT.setFillColor(Color::White);
    TXT.setPosition(x, y + 5);

    BOX.setSize(Vector2f(width, height));
    BOX.setPosition(x, y);
    BOX.setFillColor(sf::Color(133, 133, 133));
    BOX.setOutlineThickness(2);
    BOX.setOutlineColor(Color(66, 66, 66));
}

bool Button::select(Vector2i _mouse)
{
    return ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height));
}

RectangleShape Button::displayButton()
{
    return BOX;
}

Vector2f Button::getPosition()
{
    return Vector2f(x, y);
}

Vector2f Button::getSize()
{
    return Vector2f(width, height);
}

void Button::setPosition(double _x, double _y)
{
    x = _x;
    y = _y;
    BOX.setPosition(x, y);
}

void Button::setScale(double _width, double _height)
{
    width = _width;
    height = _height;
    BOX.setSize(sf::Vector2f(width, height));
}

void Button::setSize(double _width, double _height)
{
    width = _width;
    height = _height;
    BOX.setSize(sf::Vector2f(width, height));
}