#include <iostream>
#include <string>
#include <vector>

#include "cppconsmenu.hpp"

#include "cpputils.hpp"



namespace ConsMenu {
    void Menu::show_border() {
        Console::Color::SpecStyle base = Console::Color::SpecStyle::from_genstyle(this->base_color);
        std::string new_border = Console::Size::get_fill_hor(this->border, Console::Size::get_size());
        std::cout << this->border_specstyle.get_str() << new_border << base.get_str() << std::endl;
    };

    void Menu::show_header() {
        Console::Color::SpecStyle base = Console::Color::SpecStyle::from_genstyle(this->base_color);

        this->show_border();
        std::cout
            << this->title_specstyle.get_str() << this->title << std::endl
            << this->desc_specstyle.get_str() << this->desc << std::endl;
        this->show_border();
        std::cout << base.get_str() << std::endl;
    };

    void Menu::show() {
        this->base_color.set_console_color();
        this->show_header();
    }
}