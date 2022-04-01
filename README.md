## :zap:SFML-GUI:zap:

**A Graphical User Interface Library for SFML written in C++**

<!-- <h1 align="center">:zap:SFML-GUI:zap:</h1> //-->
<!-- <h2 align="center"> A Graphical User Interface Library for SFML written in C++ </h2> //-->

![DEMO IMAGE](/demoimages/sfml-demoimage.png/)

This Project is heavily inspired by Dear imgui, if you like this project i highly recommend checking out imgui.
https://github.com/ocornut/imgui


### Status

This project is currently a W.I.P, but it is fully functional, and will work in your own projects,
All that needs to be added is more widgets.

Currently sfml-gui Supports the following widgets.


Labels | Check Boxes | List Boxes | Sliders | Buttons |
-------|-------------|------------|---------|---------|


### License

SFML-GUI library, source code and examples are distributed under the terms of
[zlib/libpng license](http://opensource.org/licenses/Zlib) as SFML itself.


### Code example

The Following code showcases how some widgets can be created, and used.

**Code:**

```c++
#include <SFML/Graphics.hpp>
#include <sfml-gui/gui.hpp>
#include <SFML/Window/Event.hpp>

using sfml_gui::Gui;
using sfml_gui::Text;
using sfml_gui::CheckBox;
using sfml_gui::Slider;
using sfml_gui::ListBox;
using sfml_gui::Button;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML GUI works!");

    Gui uiWin{
        "UI Window 0",
        {600.f, 400.f}, {400.f, 200.f},
        {64, 64, 64, 255}, {64, 128, 64}, {255, 255, 255}
    };
    CheckBox check{uiWin.getGuiColor(), "Checkbox 0", {255, 255, 255}};
    Slider<int, 1> slider{uiWin.getGuiColor(), {255, 255, 255}, 150.f, uiWin.getFont(), "Slider 0", 0, 150};
    ListBox list(uiWin.getGuiColor(), 150);

    int selectedItem{1};
    std::vector<std::string> items{ "option 1", "option 2", "option 3" };

    bool checkValue{true};
    int sliderValue{0};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(56, 56, 56));
        uiWin.update(window);
        uiWin.draw(window);
        check.draw(window, 1, uiWin.getGui(), checkValue);
        slider.draw(window, 2, uiWin.getGui(), &sliderValue);
        list.draw(window, uiWin.getGui(), 3, items, selectedItem);

        window.display();
    }

    return 0;
}
```

**Output:**

![DEMO IMAGE2](/demoimages/gui-starterimage.PNG/)

### Build

SFML-GUI uses CMake build system to manage build/install/etc.

Type the following inside of **sfml-gui** project root directory within terminal in order to generate project:
```sh
mkdir build # create directory to generate project into
cd build # go to directory just created
cmake .. [CONFIGURE_OPTIONS] #generate sfml-gui project for you IDE/builder within `build` directory
cmake --build . --target all # optionaly build sfml-gui
cmake --build . --target install # optionaly install sfml-gui
```
Where possible **CONFIGURE_OPTIONS** are:
* **`-G<GENERATOR>`**
        Use specified generator -- one of listed by `cmake --help` command
* **`-DCMAKE_BUILD_TYPE=<TYPE_NAME>`**
        Possible type names are: "Release", "Debug", "RelWithDebInfo", "RelSizeMin", default is "Release"
* **`-Dsfml_gui_BUILD_SHARED_LIBS=<TRUE|FALSE>`**
        If TRUE then build sfml-gui as shared library else build as static library
* **`-DCMAKE_INSTALL_PREFIX=<PATH>`**
        Use custom install prefix, default is `/usr/local` on Linux/MacOSX and something like
        `C:\Program Files\sfml-gui` on Windows I guess
* **`-DSFML_DIR=<PATH>`**
        Use custom SFML installation/build-tree, `PATH` directory must contain `SFMLConfig.cmake` file
* **`-Dsfml_gui_BUILD_DEMO=<TRUE|FALSE>`**
        If TRUE then build demo application, default is TRUE

### Setup own project with SFML-GUI

#### Include sfml-gui as subproject. The easy way

Copy `sfml-gui` project root directory under `<your-project-root>/dependencies` directory and
add the following into your project CMakeLists.txt before defining depending targets:

```cmake
add_subdirectory(dependencies/sfml-gui)
```

And add the `sfml-gui::libsfml-gui` target into list of libraries your project's target links against:
```cmake
target_link_libraries(MyTarget PRIVATE sfml-gui::libsfml-gui)
```

#### Import sfml-gui targets via CMake config. The universal way

Add the following into your CMake project before defining dependent targets:
```cmake
find_package(sfml-gui 0.1 CONFIG REQUIRED
    COMPONENTS libsfml-gui)
```

And add the `sfml-gui::libsfml-gui` target into list of libraries your project's target links against:
```cmake
target_link_libraries(MyTarget PRIVATE sfml-gui::libsfml-gui)
```
If isn't `sfml-gui` installed system-wide then you should provide the path to sfml-gui config directory via `set(sfml-gui_DIR <PATH-TO-SFML-CONFIG>)` inside your project or via CMake command line option `-Dsfml-gui_DIR=<PATH-TO-SFML-GUI-CONFIG>` where `PATH-TO-SFML-GUI-CONFIG` must containt `sfml-gui-config.cmake` file.

### Known Issues

1. Listboxes overlap over widgets. the overlapped widgets still detect collision whilst being underneath the listbox.
