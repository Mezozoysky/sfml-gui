#include "gui.hpp"

namespace sfml_gui
{

Gui::Gui(std::string title,
         sf::Vector2f size,
         sf::Vector2f position,
         sf::Color backgroundColor,
         sf::Color topBarColor,
         sf::Color textColor)
{
    mBackground.setSize(size);
    mBackground.setFillColor(backgroundColor);
    mBackground.setPosition(position);
    mBackground.setOrigin(mBackground.getSize() / 2.0f);
    mTopBar.setPosition(sf::Vector2f(mBackground.getGlobalBounds().left, mBackground.getGlobalBounds().top));
    mTopBar.setOrigin(mTopBar.getSize() / 2.0f);
    mTopBar.setFillColor(topBarColor);
    mTopBar.setSize(sf::Vector2f(mBackground.getSize().x, 20.0f));

    //mWindowText.setColor(sf::Color(0, 0, 0));
    mFont.loadFromFile("fonts/cour.ttf");
    mWindowText.setFont(mFont);
    mWindowText.setFillColor(textColor);
    mWindowText.setCharacterSize(13);
    mWindowText.setPosition(sf::Vector2f(mBackground.getGlobalBounds().left + 8.0f, mBackground.getGlobalBounds().top + 2.0f));
    mWindowText.setString(title);
}

sf::RectangleShape const & Gui::getGui()
{
    return mBackground;
}

sf::Color const & Gui::getGuiColor()
{
    return mTopBar.getFillColor();
}

sf::Font& Gui::getFont()
{
    return mFont;
}

void Gui::draw(sf::RenderWindow& window)
{
    window.draw(mBackground);
    window.draw(mTopBar);
    window.draw(mWindowText);
}

void Gui::update(sf::RenderWindow& window)
{
    if(window.hasFocus()) // Checks if the window has focus to prevent moving the gui while not focused
    {
        // If gui isn't selected it checks for left clicks
        // If gui is selected it checks for when you let go of lmb
        if (mIsSelected)
        {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                mIsSelected = false;
            }
        }
        else
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (sf::Mouse::getPosition(window).x >= mTopBar.getPosition().x
                    && sf::Mouse::getPosition(window).x <= mTopBar.getPosition().x + mTopBar.getSize().x
                    && sf::Mouse::getPosition(window).y >= mTopBar.getPosition().y
                    && sf::Mouse::getPosition(window).y <= mTopBar.getPosition().y + mTopBar.getSize().y)
                {
                    mIsSelected = true;
                    mMouseOffsetX = sf::Mouse::getPosition(window).x - mBackground.getPosition().x;
                }
            }
        }

        // If gui is selected it updates it's position
        if (mIsSelected)
        {
            mBackground.setPosition(sf::Mouse::getPosition(window).x
                                        + mBackground.getSize().x / sf::Mouse::getPosition(window).x
                                        - mMouseOffsetX,
                                    sf::Mouse::getPosition(window).y
                                        + mBackground.getSize().y / 2.0f
                                        - 10.0f);

            mTopBar.setPosition(sf::Vector2f(mBackground.getGlobalBounds().left,
                                             mBackground.getGlobalBounds().top));
            mWindowText.setPosition(sf::Vector2f(mBackground.getGlobalBounds().left + 8.0f,
                                                 mBackground.getGlobalBounds().top + 2.0f));
        }
    }
}

} // namespace sfml_gui
