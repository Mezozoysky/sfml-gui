#include <SFML/Graphics.hpp>
#include <sfml-gui/gui.hpp>

#include <string>
#include <sstream>

/*
this file shouldn't be used if you want to use the library, main.cpp is only for testing purposes, and gives me a way to test
and imagine what the gui would work like in a real games enviroment.

All that said, if you want to test the library feel free to use my main.cpp, although you could create your own.
*/

using sfml_gui::Gui;
using sfml_gui::Text;
using sfml_gui::CheckBox;
using sfml_gui::Slider;
using sfml_gui::ListBox;
using sfml_gui::Button;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    //===================================================================
    Gui uiWin{
        "UI Window 0",
        {600.f, 400.f}, {400.f, 200.f},
        {64, 64, 64, 255}, {64, 128, 64}, {255, 255, 255}
    };
    CheckBox check{uiWin.getGuiColor(), "Checkbox 0", {255, 255, 255}};
    Slider<int, 1> slider{uiWin.getGuiColor(), {255, 255, 255}, 150.f, uiWin.getFont(), "Slider 0", 0, 150};
    ListBox list(uiWin.getGuiColor(), 150);
    //===================================================================

    Gui gui("test window 1", sf::Vector2f(600, 400), sf::Vector2f(720, 350), sf::Color(41, 39, 39, 128), sf::Color(124, 222, 162), sf::Color(46, 45, 46));
    Text text1("test text 1", sf::Color(255, 255, 255));
    Text text2("Text Number 2!", sf::Color(255, 255, 255));
    CheckBox checkBox1(gui.getGuiColor(), "Checkbox Test 1", sf::Color(255, 255, 255));

    Slider<int, 1> slider1(/*gui.getGuiColor()*/{182, 64, 182},
                           {255, 255, 255},
                           200,
                           gui.getFont(),
                           "Slider Test INT!",
                           10,
                           15);
    Slider<float, 1> slider2(gui.getGuiColor(),
                             sf::Color(255, 255, 255),
                             300,
                             gui.getFont(),
                             "",
                             0,
                             1280);

    Slider<int, 3> sliderInt3(gui.getGuiColor(),
                              sf::Color(255, 255, 255),
                              100,
                              gui.getFont(),
                              "slider int 3!",
                              0,
                              0,
                              60,
                              1280,
                              720,
                              400);
    Slider<int, 3> sliderInt3Color(gui.getGuiColor(),
                                   sf::Color(255, 255, 255),
                                   173,
                                   gui.getFont(),
                                   "",
                                   0,
                                   0,
                                   0,
                                   255,
                                   255,
                                   255);

    Slider<float, 3> sliderFloat3(gui.getGuiColor(), sf::Color(255, 255, 255), 173, gui.getFont(), "", 0, 0, 60, 1280, 720, 400);

    Slider<float, 2> sliderFloat2(gui.getGuiColor(), sf::Color(255, 255, 255), 200, gui.getFont(), "", 0, 0, 1280, 720);

    Button button(gui.getGui(), gui.getGuiColor(), 140.f, sf::Color(255, 255, 255), "Test", "Right Text!");

    ListBox listbox(gui.getGuiColor(), 200);


    bool checktest = false;
    int lulw = 30;
    float bruh = 15;

    int int3Test[3] = {15, 15, 15};

    int testColor[3] = {0, 0, 0};

    float float3Test[3] = {0, 0, 0};

    bool clicked = false;

    float slider2Test[2] {0, 0};

    std::vector<std::string> items{ "option 1", "option 2", "option 3" };
    int selectedItem = 1;

    bool checkValue{true};
    int sliderValue{0};

    //test text
    sf::Font font; font.loadFromFile("fonts/cour.ttf"); sf::Text text; text.setCharacterSize(20);
    text.setFont(font); text.setFillColor(sf::Color::Black);

    text.setPosition(sf::Vector2f(50.0f, 50.0f));

    sf::Text sftext2 = text2.getText();
    sftext2.setCharacterSize(20);
    sftext2.setFont(font); sftext2.setFillColor(sf::Color::Black);
    sftext2.setPosition(sf::Vector2f(50.0f, 100.0f));


    sf::RectangleShape test;
    test.setPosition(sf::Vector2f(200, 200));
    test.setSize(sf::Vector2f(200, 200));

    sf::RectangleShape testfloat;
    testfloat.setPosition(sf::Vector2f(600, 200));
    testfloat.setSize(sf::Vector2f(200, 200));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        test.setSize(sf::Vector2f(lulw, 200));

        testfloat.setPosition(int3Test[0], int3Test[1]);
        testfloat.setFillColor(sf::Color(testColor[0], testColor[1], testColor[2]));

        test.setPosition(sf::Vector2f(slider2Test[0], slider2Test[1]));

        std::stringstream ss;
        ss << "Variable LULW = " << lulw;
        std::string actual_text = ss.str();
        text.setString(actual_text);


        std::stringstream ss2;
        ss2 << "Variable bruh = " << bruh;
        std::string actual_text_float = ss2.str();
        sftext2.setString(actual_text_float);

        if (button.isClicked(window))
        {
            clicked = !clicked;
        }
        if (clicked) { test.setFillColor(sf::Color::Blue); }
        if (!clicked) { test.setFillColor(sf::Color::Yellow); }

        window.clear(sf::Color(56, 56, 56));
        window.draw(testfloat);
        gui.update(window);
        if (checktest && selectedItem == 2) {
            window.draw(test);
        }
        gui.draw(window);
        if (checktest) {
            text2.draw(window, 10, gui.getGui());
        }
        button.draw(window, gui.getGui(), 9);

        text1.draw(window, 1, gui.getGui());
        window.draw(text);
        window.draw(sftext2);
        slider1.draw(window, 2, gui.getGui(), &lulw);
        slider2.draw(window, 3, gui.getGui(), &bruh);

        sliderInt3.draw(window, 4, gui.getGui(), int3Test);
        sliderInt3Color.draw(window, 5, gui.getGui(), testColor);
        sliderFloat3.draw(window, 6, gui.getGui(), float3Test);

        sliderFloat2.draw(window, 7, gui.getGui(), slider2Test);
        checkBox1.draw(window, 8, gui.getGui(), checktest);

        listbox.draw(window, gui.getGui(), 11, items, selectedItem);

        uiWin.update(window);
        uiWin.draw(window);
        check.draw(window, 1, uiWin.getGui(), checkValue);
        slider.draw(window, 2, uiWin.getGui(), &sliderValue);
        list.draw(window, uiWin.getGui(), 3, items, selectedItem);

        window.display();
    }

    return 0;
}
