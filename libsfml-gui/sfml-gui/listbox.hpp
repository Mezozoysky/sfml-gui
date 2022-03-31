#pragma once

#include <SFML/Graphics.hpp>


namespace sfml_gui
{

class ListBox
{
public:
	ListBox(sf::Color const & frontColor, float width);

	void update(sf::RectangleShape const & background,
                int slot,
                sf::RenderWindow & window,
                int size,
                std::string items[],
                int & selectedItem);
    void draw(sf::RenderWindow & window,
              sf::RectangleShape const & pid,
              int slot,
              int size,
              std::string items[],
              int & selectedItem);

    bool checkHover(sf::RenderWindow const & window, sf::RectangleShape const & object);
	bool checkHoverOppo(sf::RenderWindow const & window, sf::RectangleShape const & object);

private:
	sf::RectangleShape mBackground;
	sf::Vector2f mPosition;

	sf::RectangleShape mDropdown;

	sf::RectangleShape mDropdowns[99];
	sf::Text mDropdownsText[99];
	sf::Font mFont;

	sf::Text mSelectedText;

	sf::Clock mDropdownClock;
	sf::Clock mDropdownClock2;

	std::string mActualSelectedItem;

	sf::RectangleShape mDropdownShape;

	bool mIsInitialized{false};

	bool mIsDropdownActive{false};

	sf::Color mThemeColor;

	sf::Texture mDropdownTexture;
};

} // namespace sfml_gui
