#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include <sfml-gui/config.hpp>
#include "text.hpp"
#include "checkbox.hpp"
#include "slider.hpp"
#include "button.hpp"
#include "listbox.hpp"

namespace sfml_gui
{

class Gui
{
private:
	struct Id {
		sf::RectangleShape pid;
		sf::RectangleShape topBar;
	};

public:
	Gui(std::string title,
        sf::Vector2f size,
        sf::Vector2f position,
        sf::Color backgroundColor,
		sf::Color topBarColor,
        sf::Color textColor);

	sf::RectangleShape const & getGui();
	sf::Color const & getGuiColor();
    sf::Font& getFont();

	void draw(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);

private:
	sf::RectangleShape mBackground;
	sf::RectangleShape mTopBar;
	sf::Text mWindowText;
	sf::Font mFont;
	int mElementCount{0};
	bool mFlag{true};

	bool mIsSelected{false}; // Whether the gui is selected
	float mMouseOffsetX{0.0f}; // X offset relative to the mouse
};


} // namespace sfml_gui
