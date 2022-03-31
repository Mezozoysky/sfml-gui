#include "checkbox.hpp"

namespace sfml_gui
{

CheckBox::CheckBox(sf::Color const & frontColor,
                   std::string const & title,
                   sf::Color const & textColor)
{
    //init text for the checkbox
    mFont.loadFromFile("fonts/cour.ttf");
    mText.setCharacterSize(13);
    mText.setFillColor(textColor);
    mText.setFont(mFont);
    mText.setString(title);

    mBackground.setSize(sf::Vector2f(15.0f, 15.0f));
    mBackground.setFillColor(sf::Color(frontColor.r - 40.0f, frontColor.g - 40.0f, frontColor.b - 40.0f));
    mThemeColor = sf::Color(frontColor.r - 40, frontColor.g - 40, frontColor.b - 40);
    mCheckTexture.loadFromFile("images/checkmark.png");
    mCheck.setSize(mBackground.getSize());
    mCheck.setTexture(&mCheckTexture);

    mTimer.restart();

}

void CheckBox::update(int slot, sf::RectangleShape const & background, sf::RenderWindow & window)
{
    sf::Vector2f mPosition;
    mPosition = sf::Vector2f(background.getGlobalBounds().left + 10.0f, background.getGlobalBounds().top + slot * 20.0f);
    mBackground.setPosition(mPosition);
    mCheck.setPosition(mPosition);


    if (sf::Mouse::getPosition(window).x >= mBackground.getPosition().x &&
        sf::Mouse::getPosition(window).x <= mBackground.getPosition().x + mBackground.getSize().x &&
        sf::Mouse::getPosition(window).y >= mBackground.getPosition().y &&
        sf::Mouse::getPosition(window).y <= mBackground.getPosition().y + mBackground.getSize().y)
    {
        mBackground.setFillColor(sf::Color(mThemeColor.r + 30, mThemeColor.g + 30, mThemeColor.b + 30));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (mTimer.getElapsedTime().asSeconds() >= 0.2f) {
                mActivateFlag = true;
                mIsActivated = !mIsActivated;
                mTimer.restart();
            }
        }
    }
    else
        mBackground.setFillColor(mThemeColor);


    //update position for text

    mText.setPosition(sf::Vector2f(mPosition.x + 20.f, mPosition.y - 2.f));
}

void CheckBox::draw(sf::RenderWindow & window, int slot, sf::RectangleShape const & pid, bool & BOOLEAN)
{
    window.draw(mBackground);
    window.draw(mText);

    if (mActivateFlag) {
        BOOLEAN = !BOOLEAN;
        mActivateFlag = false;
    }

    if (mIsActivated) {
        window.draw(mCheck);
    }

    update(slot, pid, window);
}

} // namespace sfml_gui
