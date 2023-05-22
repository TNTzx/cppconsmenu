#ifndef MENU_CHOICE
#define MENU_CHOICE



#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <memory>

#include "cppconsmenu.hpp"

#include "cpputils.hpp"



namespace ConsMenu {
    Choice::Choice(std::string _description) {
        this->description = _description;
    }



    SelectResult::SelectResult(short int _row, int _width, int _result) {
        this->row = _row;
        this->width = _width;
        this->result = _result;
    };



    SelectMenu::SelectMenu() : Menu() {};

    std::string SelectMenu::add_style_to_tag(const std::string& tag) {
        return this->tag_open_br + tag + this->tag_close_br;
    };

    std::string SelectMenu::get_default_choices_display() {
        std::string back_tag_display = !this->is_main_menu ?
            (add_style_to_tag(this->back_tag) + " Go back to previous menu.\n")
            : "";

        return back_tag_display + (add_style_to_tag(this->exit_tag) + " Exit the program.");
    };

    std::vector<std::string> SelectMenu::get_choices_display() {
        std::vector<std::string> display_strs;
        for (size_t idx = 0; idx < this->choices.size(); idx++) {
            std::string choice = this->choices[idx]->description;
            std::string idx_str = std::to_string(idx + 1);
            display_strs.push_back(add_style_to_tag(idx_str) + " " + choice);
        };
        return display_strs;
    };

    SelectResult SelectMenu::ask_response(bool show_invalid) {
        Console::clear_console();
        Menu::show_header();


        if (show_invalid) {
            Console::Color::SpecStyle error_specstyle = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::light_red, true);
            std::cout << error_specstyle.get_str() << "Invalid input, please try again." << Console::Color::SpecStyle().get_str()
                << std::endl << std::endl;
        }


        std::string base_color_str = Console::Color::SpecStyle().get_str();
        base_color_str += Console::Color::SpecStyle::from_genstyle(this->base_color).get_str();

        std::cout << std::endl
            << this->choice_text << std::endl
            << std::endl
            << std::endl
            << Console::Color::SpecStyle(false, Console::Color::red, Console::Color::black, false, true).get_str()
                << this->get_default_choices_display() << std::endl
            << base_color_str;


        std::vector<short int> option_poss;
        std::vector<std::string> choices_display = this->get_choices_display();
        for (std::string choice_display : choices_display) {
            option_poss.push_back(Console::Cursor::get_pos().Y);
            std::cout << choice_display << std::endl;
        };

        option_poss.push_back(Console::Cursor::get_pos().Y);

        std::cout
            << std::endl
            << std::endl
            << Console::Color::SpecStyle(false, Console::Color::light_green, Console::Color::black, true).get_str()
                << "[]> " << this->typing_color.get_str();


        std::string response;
        Console::flush_streams();
        std::cin >> response;

        if ((response == this->back_tag) && (!this->is_main_menu)) {
            throw MenuExc::MenuChExit();
        } else if (response == this->exit_tag) {
            throw MenuExc::MenuExit();
        };


        std::cout << Console::Color::SpecStyle().get_str();

        if (!StrUtils::is_number(response)) {
            throw MenuExc::MenuChInputNotTag();
        };

        int choice_idx = std::stoi(response) - 1;
        if (((choice_idx + 1) > choices.size()) || (choice_idx < 0)) {
            throw MenuExc::MenuChInputInvalidTag();
        };

        int row = option_poss[choice_idx];
        int next_row = option_poss[choice_idx + 1];
        return SelectResult(row, next_row - row, choice_idx);
    };

    SelectResult SelectMenu::ask_response_loop() {
        Console::clear_console();
        bool invalid = false;

        while (true) {
            try {
                return ask_response(invalid);
            } catch (MenuExc::MenuChInvalidInput) {
                Console::clear_console();
                invalid = true;
            };
        };
    };

    void SelectMenu::show() {
        while (true) {
            Console::clear_console();
            SelectResult response;
            try {
                response = this->ask_response_loop();
                Console::flush_streams();
            } catch (MenuExc::MenuChExit) {
                Console::flush_streams();

                Console::Color::SpecStyle pixel_specstyle = Console::Color::SpecStyle(
                    false,
                    Console::Color::red,
                    Console::Color::black,
                    true
                );

                Console::Anim::CornerPixelate(0.1, pixel_specstyle).run();
                sleep(1);
                break;
            } catch (MenuExc::MenuExit exc) {
                Console::flush_streams();

                Console::Color::SpecStyle pixel_specstyle = Console::Color::SpecStyle(
                    false,
                    Console::Color::red,
                    Console::Color::red,
                    true
                );

                Console::Anim::CornerPixelate(0.5, pixel_specstyle).run();
                sleep(1);
                throw exc;
            };


            Console::Color::SpecStyle bar_specstyle = Console::Color::SpecStyle(
                false,
                Console::Color::green,
                Console::Color::black,
                true
            );
            Console::Anim::BarHighlight(0.5, response.row, response.width - 1, "=", bar_specstyle).run();

            sleep(1);

            Console::Color::SpecStyle wipe_specstyle = Console::Color::SpecStyle(
                false,
                Console::Color::light_green,
                Console::Color::blue,
                true
            );
            Console::Anim::WipeScreen(0.02, "███", wipe_specstyle, true).run();


            sleep(1);

            Console::clear_console();
            this->choices[response.result]->screen->show();
        }
    }
    std::string SelectMenu::back_tag = "x";
    std::string SelectMenu::exit_tag = "xx";
    std::string SelectMenu::tag_open_br = "[";
    std::string SelectMenu::tag_close_br = "]:";
};



#endif