#include <SFML/Graphics.hpp>
#include <sfml-gui/gui.hpp>

#include <string>
#include <sstream>

/*
this file shouldn't be used if you want to use the library, main.cpp is only for testing purposes, and gives me a way to test
and imagine what the GUI would work like in a real games enviroment.

All that said, if you want to test the library feel free to use my main.cpp, although you could create your own.
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    gui GUI("test window 1", sf::Vector2f(600, 400), sf::Vector2f(720, 350), sf::Color(41, 39, 39, 128), sf::Color(124, 222, 162), sf::Color(46, 45, 46));
    text Text1(GUI.getGUI(), "test text 1", sf::Color(255, 255, 255), window);
    text Text2(GUI.getGUI(), "Text Number 2!", sf::Color(255, 255, 255), window);
    CheckBox checkBox1(GUI.getGUIColor(), "Checkbox Test 1", sf::Color(255, 255, 255));

    Slider<int, 1> slider1(GUI.getGUIColor().getFillColor(), sf::Color(255, 255, 255), 200, GUI.getFont(), "Slider Test INT!", 10, 15);
    Slider<float, 1> slider2(GUI.getGUIColor().getFillColor(), sf::Color(255, 255, 255), 300, GUI.getFont(), "", 0, 1280);

    Slider<int, 3> sliderInt3(GUI.getGUIColor().getFillColor(), sf::Color(255, 255, 255), 100, GUI.getFont(), "slider int 3!", 0, 0, 60, 1280, 720, 400);
    Slider<int, 3> sliderInt3Color(GUI.getGUIColor().getFillColor(), sf::Color(255, 255, 255), 173, GUI.getFont(), "", 0, 0, 0, 255, 255, 255);

    Slider<float, 3> sliderFloat3(GUI.getGUIColor().getFillColor(), sf::Color(255, 255, 255), 173, GUI.getFont(), "", 0, 0, 60, 1280, 720, 400);

    Slider<float, 2> sliderFloat2(GUI.getGUIColor().getFillColor(), sf::Color(255, 255, 255), 200, GUI.getFont(), "", 0, 0, 1280, 720);

    // Button button(GUI.getGUI(), GUI.getGUIColor(), 140.0f, sf::Color(255, 255, 255), "Test", "Right Text!");

    ListBox listbox(GUI.getGUIColor(), 200);


    bool checktest = false;
    int lulw = 30;
    float bruh = 15;

    int int3Test[3] = {15, 15, 15};

    int testColor[3] = {0, 0, 0};

    float float3Test[3] = {0, 0, 0};

    bool clicked = false;

    float slider2Test[2] {0, 0};

    int selectedItem = 1;
    std::string items[]{ "option 1", "option 2", "option 3" };

    //test text
    sf::Font font; font.loadFromFile("fonts/cour.ttf"); sf::Text text; text.setCharacterSize(20);
    text.setFont(font); text.setFillColor(sf::Color::Black);

    text.setPosition(sf::Vector2f(50.0f, 50.0f));

    sf::Text text2; text2.setCharacterSize(20);
    text2.setFont(font); text2.setFillColor(sf::Color::Black);
    text2.setPosition(sf::Vector2f(50.0f, 100.0f));


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
        text2.setString(actual_text_float);

        // if (button.isButtonClicked(window))
        // {
        //     clicked = !clicked;
        // }
        if (clicked) { test.setFillColor(sf::Color::Blue); }
        if (!clicked) { test.setFillColor(sf::Color::Yellow); }

        window.clear(sf::Color(56, 56, 56));
        window.draw(testfloat);
        GUI.UPDATE_GUI(window);
        if (checktest && selectedItem == 2) {
            window.draw(test);
        }
        GUI.DRAW_GUI(window);
        if (checktest) {
            Text2.Draw(window, 10, GUI.getGUI());
        }

        // button.Draw(window, GUI.getGUI(), GUI.getGUIColor(), 9);

        Text1.Draw(window, 1, GUI.getGUI());
        window.draw(text);
        window.draw(text2);
        slider1.draw(window, 2, GUI.getGUI(), &lulw);
        slider2.draw(window, 3, GUI.getGUI(), &bruh);

        sliderInt3.draw(window, 4, GUI.getGUI(), int3Test);
        sliderInt3Color.draw(window, 5, GUI.getGUI(), testColor);
        sliderFloat3.draw(window, 6, GUI.getGUI(), float3Test);

        sliderFloat2.draw(window, 7, GUI.getGUI(), slider2Test);
        checkBox1.Draw(window, 8, GUI.getGUI(), checktest);

        listbox.Draw(window, GUI.getGUI(), 11, 2, items, selectedItem);

        window.display();
    }

    return 0;
}
