#pragma once

#include <SFML/Graphics.hpp>


namespace sfml_gui
{

class Text
{
public:
	Text(std::string const & text, sf::Color const & color);

	sf::Text getText();

    void draw(sf::RenderWindow & window, int slot, sf::RectangleShape const & pid);

protected:
    void update(int slot, sf::RectangleShape const & background);

private:
	sf::Text mText;
	sf::Font mFont;
	sf::Vector2f mPosition;
	bool mFlag{true};
};

} // namespace sfml_gui
