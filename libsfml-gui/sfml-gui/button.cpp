#include "button.hpp"

namespace sfml_gui
{

Button::Button(sf::RectangleShape const & pid,
               sf::Color const & frontColor,
               float width,
               sf::Color const & textColor,
               std::string const & text,
               std::string const & rightText)
{
    mFont.loadFromFile("fonts/cour.ttf");
    mText.setCharacterSize(13);
    mText.setFillColor(textColor);
    mText.setFont(mFont);
    mText.setString(text);
    mText.setOrigin(mText.getGlobalBounds().width / 2, mText.getGlobalBounds().height / 2);

    mRightText.setCharacterSize(13);
    mRightText.setFillColor(textColor);
    mRightText.setFont(mFont);
    mRightText.setString(rightText);

    mButton.setSize(sf::Vector2f(width, 15.0f));
    mThemeColor = sf::Color(frontColor.r - 40.0f, frontColor.g - 40.0f, frontColor.b - 40.0f);
    mSize = mButton.getSize();
}

void Button::update(sf::RectangleShape pid, int slot, sf::RenderWindow &window)
{
    mPosition = sf::Vector2f(pid.getGlobalBounds().left + 10.0f, pid.getGlobalBounds().top + slot * 20.0f);
    mButton.setPosition(mPosition);

    mTextPosition = sf::Vector2f(mButton.getPosition().x + mButton.getSize().x / 2,
                                 mButton.getPosition().y + 2.0f);
    mText.setPosition(mTextPosition);

    mRightText.setPosition(mButton.getPosition().x + mButton.getSize().x + 10.0f,
                           mButton.getPosition().y);

    if (sf::Mouse::getPosition(window).x >= mButton.getPosition().x
        && sf::Mouse::getPosition(window).x <= mButton.getPosition().x + mButton.getSize().x
        && sf::Mouse::getPosition(window).y >= mButton.getPosition().y
        && sf::Mouse::getPosition(window).y <= mButton.getPosition().y + mButton.getSize().y)
    {
        mButton.setFillColor(sf::Color(mThemeColor.r + 30.0f, mThemeColor.g + 30.0f,
                                       mThemeColor.b + 30.0f));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mButton.setPosition(mPosition.x + 2.0f, mPosition.y + 2.0f);
            mText.setPosition(mTextPosition.x + 2.0f, mTextPosition.y + 2.0f);
        }
    }
    else {
        mButton.setFillColor(mThemeColor);
        mButton.setSize(mSize);
    }
}

void Button::draw(sf::RenderWindow & window, sf::RectangleShape const & pid, int slot)
{
    window.draw(mButton);
    window.draw(mText);
    window.draw(mRightText);
    update(pid, slot, window);
}

bool Button::isClicked(sf::RenderWindow const & window)
{
    if (sf::Mouse::getPosition(window).x >= mButton.getPosition().x
        && sf::Mouse::getPosition(window).x <= mButton.getPosition().x + mButton.getSize().x
        && sf::Mouse::getPosition(window).y >= mButton.getPosition().y
        && sf::Mouse::getPosition(window).y <= mButton.getPosition().y + mButton.getSize().y)
    {
        mButton.setFillColor(sf::Color(mThemeColor.r + 30.0f,
                                       mThemeColor.g + 30.0f,
                                       mThemeColor.b + 30.0f));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mClock.getElapsedTime().asSeconds() >= 0.3f)
        {
            mClock.restart();
            return true;
        }
    }
    return false;
}

} // namespace sfml_gui
