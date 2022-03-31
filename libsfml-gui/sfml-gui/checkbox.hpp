#pragma once

#include <SFML/Graphics.hpp>


namespace sfml_gui
{

class CheckBox
{
public:

	CheckBox(sf::Color const & frontColor,
             std::string const & title,
             sf::Color const & textColor);

	void update(int slot, sf::RectangleShape const & background, sf::RenderWindow & window);
	void draw(sf::RenderWindow & window, int slot, sf::RectangleShape const & pid, bool & BOOLEAN);


private:
	sf::RectangleShape mBackground;
	sf::Vector2f mPosition;


	sf::RectangleShape mCheck;
	sf::Texture mCheckTexture;
	sf::Clock mTimer;

	bool mActivateFlag{false};

	sf::Text mText;
	sf::Font mFont;

	sf::Color mThemeColor;

	bool mIsActivated{false};

};

} // namespace sfml_gui
