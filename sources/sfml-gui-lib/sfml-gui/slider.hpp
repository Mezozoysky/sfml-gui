#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <algorithm>

#include <stdarg.h>
#include <sstream>


namespace sfml_gui
{

enum Selected : unsigned char
{
    SELECTED_THIS,
    SELECTED_SOMETHING_ELSE,
    SELECTED_NOTHING
};

// T is type of value used by slider
// LEN is how many sliders you want
template <typename T, int LEN>
class Slider
{
public:
    Slider(sf::Color const & frontColor,
           sf::Color const & textColor,
           float sliderSize,
           sf::Font const & font,
           std::string const& text,
           ...)
    : mFrontColor(sf::Color(frontColor.r - 40.0f, frontColor.g - 40.0f, frontColor.b - 40.0f))
    , mTitle(text, font, 13)
    {
        // Visual / Graphical initialization
        for(int i = 0; i < LEN; i++)
        {
            mBackground[i].setSize(sf::Vector2f(sliderSize, 15.0f));
            mBackground[i].setFillColor(mFrontColor);

            mBar[i].setSize(sf::Vector2f(0.0f, 10.0f));
            mBar[i].setFillColor(sf::Color(mFrontColor.r + 55, mFrontColor.g + 55, mFrontColor.b + 55));

            mSlider[i].setSize(sf::Vector2f(10.0f, 15.0f));
            mSlider[i].setFillColor(frontColor);

            // Other slider stuff initialization
            mValue[i] = 0.0f;
        }

        // Minimum and maximum value initialization
        va_list values;

        va_start(values, text);

        // Unfortunately this only supports int min / max
        // so you can't have a minimum like 2.5
        for(int i = 0; i < LEN; i++)
        {
            mMinValues[i] = va_arg(values, int);
        }
        for(int i = 0; i < LEN; i++)
        {
            mMaxValues[i] = va_arg(values, int);
        }

        va_end(values);

        // Text / Font initialization
        mTitle.setFillColor(textColor);
        for(int i = 0; i < LEN; i++)
        {
            mTextValue[i].setString(std::to_string(mMinValues[i]));
            mTextValue[i].setFont(font);
            mTextValue[i].setCharacterSize(13);
            mTextValue[i].setFillColor(textColor);
        }
    }

    ~Slider()
    {

    }

    void update(sf::RectangleShape const & pid, int slot, sf::RenderWindow const& window, T * value)
    {
        for(int i = 0; i < LEN; i++)
        {
            // Positioning / Resizing the slider
            mBackground[i].setPosition(
                pid.getGlobalBounds().left + 10.0f + (mBackground[i].getSize().x + 10.0f) * i,
                pid.getGlobalBounds().top + slot * 20.0f
                );
            // Checks if the position of mBackground has changed,
            // so it doesn't need to update positions every frame
            if (mOldSliderBackgroundPosition[i] != mBackground[i].getPosition())
            {
                mSlider[i].setPosition((mBackground[i].getSize().x - mSlider[i].getSize().x) * mValue[i]
                                           + mBackground[i].getPosition().x,
                                       mBackground[i].getPosition().y);
                mBar[i].setPosition(mBackground[i].getPosition().x + 3.0f,
                                    mBackground[i].getPosition().y + 2.0f);
                mBar[i].setSize({mSlider[i].getPosition().x - mBackground[i].getPosition().x, 10.0f});

                mTextValue[i].setPosition(mBackground[i].getPosition().x + mBackground[i].getSize().x / 2,
                                          mBackground[i].getPosition().y);
                mOldSliderBackgroundPosition[i] = mBackground[i].getPosition();
            }
        }

        mTitle.setPosition(mBackground[LEN - 1].getPosition().x + mBackground[LEN - 1].getSize().x + 10.0f,
                           mBackground->getPosition().y);

        if(mInitFlag)
        {
            for(int i = 0; i < LEN; i++)
            {
                updateValue(value);
            }
            mInitFlag = false;
        }

        // Input stuff
        sf::FloatRect mousePos = {static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), sf::Vector2f(1, 1)};

        if(window.hasFocus()) // Checks if window has focus so you don't move a slider while not focused
        {
            switch(mCurrentSelected)
            {
                case SELECTED_THIS:
                    mSlider[mCurrentSelectedSlider].setFillColor(sf::Color(mFrontColor.r + 100,
                                                                           mFrontColor.g + 50,
                                                                           mFrontColor.b + 50));
                    mValue[mCurrentSelectedSlider] = (float) (
                        sf::Mouse::getPosition(window).x
                            - mBackground[mCurrentSelectedSlider].getPosition().x
                        ) / (float) mBackground[mCurrentSelectedSlider].getSize().x;

                    // Swap out this clamp code if you want support for c++ versions older than C++17
                    // Clamps mValue to 0 - 1
                    mValue[mCurrentSelectedSlider] = std::clamp(mValue[mCurrentSelectedSlider], 0.0f, 1.0f);
                    updateValue(value);

                    mBar[mCurrentSelectedSlider].setSize(
                        sf::Vector2f(mSlider[mCurrentSelectedSlider].getPosition().x
                            - mBackground[mCurrentSelectedSlider].getPosition().x, // X
                        10.0f) // Y
                        );
                    mSlider[mCurrentSelectedSlider].setPosition(
                        (mBackground[mCurrentSelectedSlider].getSize().x
                            - mSlider[mCurrentSelectedSlider].getSize().x
                        ) * mValue[mCurrentSelectedSlider]
                            + mBackground[mCurrentSelectedSlider].getPosition().x, // X
                        mBackground[mCurrentSelectedSlider].getPosition().y // Y
                        );
                    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        mCurrentSelected = SELECTED_NOTHING;
                    }
                    break;
                case SELECTED_SOMETHING_ELSE:
                    // While selecting something else (e.g., moving a gui)
                    // it will wait for you to let go of lmb,
                    // so you dont move a slider while grabbing something else.
                    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        mCurrentSelected = SELECTED_NOTHING;
                    }
                    break;
                case SELECTED_NOTHING:
                    for(int i = 0; i < LEN; i++)
                    {
                        mSlider[i].setFillColor(sf::Color(mFrontColor.r + 40, mFrontColor.g + 40, mFrontColor.b + 40));
                        // If you haven't selected anything it checks for lmb
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            if(mousePos.intersects(mBackground[i].getGlobalBounds()))
                            {
                                mCurrentSelected = SELECTED_THIS;
                                mCurrentSelectedSlider = i;
                                break;
                            } else
                            {
                                mCurrentSelected = SELECTED_SOMETHING_ELSE;
                            }
                        }
                    }
                    break;
            }
        }
    }

    void draw(sf::RenderWindow & window, int slot, sf::RectangleShape const & pid, T * value)
    {
        update(pid, slot, window, value);

        for(int i = 0; i < LEN; i++)
        {
            window.draw(mBackground[i]);
            window.draw(mBar[i]);
            window.draw(mSlider[i]);

            window.draw(mTextValue[i]);
        }
        window.draw(mTitle);
    }

private:
    void updateValue(T * value)
    {
        for(int i = 0; i < LEN; i++)
        {
            int maximum = mMaxValues[i] - mMinValues[i];
            value[i] = maximum * mValue[i] + mMinValues[i];

            std::stringstream ss;
            ss << value[i];
            mTextValue[i].setString(ss.str());
        }
    }

private:
    sf::RectangleShape mBackground[LEN]; // Background for slider
    sf::RectangleShape mBar[LEN]; // Slider status bar
    sf::RectangleShape mSlider[LEN]; // The slider you grab

    sf::Color mFrontColor; // Color of the gui in use

    sf::Text mTitle; // Text to right of the sliders
    sf::Text mTextValue[LEN]; // Value of slider on the screen

    sf::Vector2f mOldSliderBackgroundPosition[LEN]; // Previous position of mBackground

    float mValue[LEN]; // Current value of slider within a range of 0 - 1

    int mMinValues[LEN];
    int mMaxValues[LEN];

    bool mInitFlag{true};

    Selected mCurrentSelected{SELECTED_NOTHING};
    unsigned char mCurrentSelectedSlider{0}; // Which slider is currently being slid
};

} // namespace sfml_gui
