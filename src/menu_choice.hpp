#pragma once


#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <memory>


#include "cpputils.hpp"
#include "menus.hpp"
#include "excs.hpp"



namespace ConsMenu {
    /*
    Represents a choice presented in a ChoiceMenu.
    */
    class Choice {
        public:
            std::string description = "This is the default description.";
            std::unique_ptr<Screen> screen;

            Choice(std::string _description);
    };



    /*
    Contains the information needed to get the output of the presented choice.
    */
    class SelectResult {
        public:
            // The row number of the choice in the screen.
            short int row = 1;

            // The width of the choice.
            int width = 1;

            // The index of the chosen choice.
            int result = 1;

            SelectResult(short int _row = 1, int _width = 1, int _result = 1);
    };



    class SelectMenu : public Menu {
        public:
            // Represents the choice used to go back to the previous menu, namely, "x".
            static std::string back_tag;

            // Represents the choice used to exit the program, namely, "xx".
            static std::string exit_tag;

            // The opening tag for choices, namely, "[".
            static std::string tag_open_br;

            // The closing tag, namely, "]".
            static std::string tag_close_br;

            // If true, this would hide the exit tag.
            bool is_main_menu = false;

            // The text to display before the choices.
            std::string choice_text = "Please pick an appropriate choice:";

            // The choices itself.
            std::vector<std::unique_ptr<Choice>> choices;

            // The color used when typing the choice.
            Console::Color::SpecStyle typing_color = Console::Color::SpecStyle(false, Console::Color::black, Console::Color::bold_white, true);

            SelectMenu() : Menu();

            /*
            Adds the opening and closing brackets to a tag.
            Ex. "x" -> "[x]"
            */
            std::string add_style_to_tag(std::string &tag);

            /*
            Gets the string to display the default tags, namely the "back" and "exit" tags.
            */
            std::string get_default_choices_display();

            /*
            Gets the string to display the choices.
            */
            std::vector<std::string> get_choices_display();

            /*
            Displays the choices and asks the user for the response.
            Also does an animation after responses.
            */
            SelectResult ask_response(bool show_invalid = false);

            // Asks the user, but with a loop. This catches invalid inputs then asks again.
            SelectResult ask_response_loop();

            void show() override;
    };
    std::string SelectMenu::back_tag = "x";
    std::string SelectMenu::exit_tag = "xx";
    std::string SelectMenu::tag_open_br = "[";
    std::string SelectMenu::tag_close_br = "]:";
};