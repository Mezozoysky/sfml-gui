#include "text.hpp"

namespace sfml_gui
{

Text::Text(std::string const & text, sf::Color const & color)
{
    mFont.loadFromFile("fonts/cour.ttf");
    mText.setCharacterSize(13);
    mText.setFillColor(color);
    mText.setFont(mFont);
    mText.setString(text);
    mFlag = false;
}

sf::Text Text::getText()
{
    return mText;
}

void Text::draw(sf::RenderWindow & window, int slot, sf::RectangleShape const & pid)
{
    window.draw(mText);
    update(slot, pid);
}

void Text::update(int slot, sf::RectangleShape const & background)
{
    mPosition = sf::Vector2f(background.getGlobalBounds().left + 10.0f,
                             background.getGlobalBounds().top + slot * 20.0f);
    mText.setPosition(mPosition);
}

} // namespace sfml_gui
