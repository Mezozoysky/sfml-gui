#include "listbox.hpp"

namespace sfml_gui
{

ListBox::ListBox(sf::Color const & frontColor, float width)
{

    mFont.loadFromFile("fonts/cour.ttf");
    mDropdownTexture.loadFromFile("images/dropdown.png");

    mBackground.setSize(sf::Vector2f(width, 15.0f));
    mBackground.setFillColor(sf::Color(frontColor.r - 40u, frontColor.g - 40u, frontColor.b - 40u));

    mDropdown.setSize({15.f, mBackground.getSize().y});
    mDropdownShape.setSize(sf::Vector2f(15, mBackground.getSize().y));
    mDropdownShape.setTexture(&mDropdownTexture);
    mDropdown.setFillColor(sf::Color( frontColor.r - 10.0f, frontColor.g - 10.0f, frontColor.b - 10.0f));

    mThemeColor = sf::Color(frontColor.r - 40.0f, frontColor.g - 40.0f, frontColor.b - 40.0f);
}

void ListBox::update(sf::RectangleShape const & background,
                     int slot,
                     sf::RenderWindow & window,
                     int size,
                     std::string items[],
                     int & selectedItem)
{
    mPosition = sf::Vector2f(background.getGlobalBounds().left + 10.0f, background.getGlobalBounds().top + slot * 20.0f);
    mBackground.setPosition(mPosition);
    mDropdown.setPosition(mBackground.getGlobalBounds().left + mBackground.getSize().x - mDropdown.getSize().x, mBackground.getPosition().y);
    mDropdownShape.setPosition(mBackground.getGlobalBounds().left + mBackground.getSize().x - mDropdown.getSize().x, mBackground.getPosition().y);

    if (!mIsInitialized) {
        for (int i = 0; i <= size; i++) {

            mDropdowns[i].setSize(mBackground.getSize());
            mDropdowns[i].setFillColor(sf::Color(mThemeColor.r - 60.0f, mThemeColor.g - 60.0f, mThemeColor.b - 60.0f));
            mDropdownsText[i].setCharacterSize(12);
            mDropdownsText[i].setFillColor(sf::Color(255, 255, 255));
            mDropdownsText[i].setFont(mFont);
            mDropdownsText[i].setString(items[i]);
            mSelectedText.setCharacterSize(13);
            mSelectedText.setFillColor(sf::Color(255, 255, 255));
            mSelectedText.setFont(mFont);
            mSelectedText.setString(mActualSelectedItem);
        }
        mIsInitialized = true;
    }

    mSelectedText.setPosition(mBackground.getPosition().x + 5.0f, mBackground.getPosition().y - 2.0f);
    mSelectedText.setString(mActualSelectedItem);
    for (int i = 0; i <= size; i++) {
        if (i == 0)
        {
            mDropdowns[0].setPosition(mBackground.getPosition().x, mBackground.getPosition().y + 15);
        }
        mDropdowns[i].setPosition(mBackground.getPosition().x, mBackground.getPosition().y + i * 15 + 15);
        mDropdownsText[i].setPosition(mDropdowns[i].getPosition().x + 10.0f, mDropdowns[i].getPosition().y - 1.0f);

        if (checkHover(window, mDropdowns[i])) {
            mDropdowns[i].setFillColor(sf::Color(mThemeColor.r - 30.0f, mThemeColor.g - 30.0f, mThemeColor.b - 30.0f));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mActualSelectedItem = items[i];
                selectedItem = i + 1;
                mIsDropdownActive = false;
            }
        }
        else {
            mDropdowns[i].setFillColor(sf::Color(mThemeColor.r - 60.0f, mThemeColor.g - 60.0f, mThemeColor.b - 60.0f));
        }

    }


    if (checkHover(window, mDropdown))
    {
        mDropdown.setFillColor(sf::Color(mThemeColor.r + 60.0f,
                                               mThemeColor.g + 60.0f,
                                               mThemeColor.b + 60.0f));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mDropdownClock.getElapsedTime().asSeconds() >= 0.2f)
        {
            mDropdownClock.restart();
            mDropdownClock2.restart();
            mIsDropdownActive = !mIsDropdownActive;
        }
    }
    else
    {
        mDropdown.setFillColor(sf::Color(mThemeColor.r + 30.0f,
                                               mThemeColor.g + 30.0f,
                                               mThemeColor.b + 30.0f));
    }


}


void ListBox::draw(sf::RenderWindow & window,
                   sf::RectangleShape const & pid,
                   int slot,
                   int size,
                   std::string items[],
                   int & selectedItem)
{
    window.draw(mBackground);
    window.draw(mDropdown);
    window.draw(mDropdownShape);
    if (mIsDropdownActive) {
        for (int i = 0; i <= size; i++) {
            window.draw(mDropdowns[i]);
            window.draw(mDropdownsText[i]);
        }
    }
    window.draw(mSelectedText);
    update(pid, slot, window, size, items, selectedItem);
}

    bool ListBox::checkHover(sf::RenderWindow const & window, sf::RectangleShape const & object)
	{
		if (sf::Mouse::getPosition(window).x >= object.getPosition().x
            && sf::Mouse::getPosition(window).x <= object.getPosition().x + object.getSize().x
            && sf::Mouse::getPosition(window).y >= object.getPosition().y
            && sf::Mouse::getPosition(window).y <= object.getPosition().y + object.getSize().y)
        {
			return true;
        }
		else
        {
			return false;
        }
	}

	bool ListBox::checkHoverOppo(sf::RenderWindow const & window, sf::RectangleShape const & object)
	{
		if (sf::Mouse::getPosition(window).x > object.getPosition().x + object.getSize().x
            || sf::Mouse::getPosition(window).x < object.getPosition().x
            || sf::Mouse::getPosition(window).y > object.getPosition().y + object.getSize().y
            || sf::Mouse::getPosition(window).y < object.getPosition().y)
        {
			return true;
        }
		else
        {
			return false;
        }
	}

} // namespace sfml_gui
