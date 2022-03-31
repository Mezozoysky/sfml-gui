#pragma once

#include <SFML/Graphics.hpp>


namespace sfml_gui
{

class Button
{

public:
	Button(sf::RectangleShape const & pid,
           sf::Color const & frontColor,
           float width,
           sf::Color const & textColor,
           std::string const & text,
           std::string const & rightText);

	void update(sf::RectangleShape pid, int slot, sf::RenderWindow &window);
	void draw(sf::RenderWindow & window, sf::RectangleShape const & pid, int slot);

	bool isClicked(sf::RenderWindow const & window);

private:
	sf::RectangleShape mButton;

	bool mIsClicked{false};
	sf::Vector2f mPosition;
	sf::Vector2f mTextPosition;

	sf::Color mThemeColor;
	sf::Vector2f mSize;
	sf::Clock mClock;
	sf::Clock mClockAnim;
	sf::Text mText;
	sf::Text mRightText;
	sf::Font mFont;
};

} // namespace sfml_gui
