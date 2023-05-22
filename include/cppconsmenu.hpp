#pragma once


#include <exception>
#include <string>

#include "cpputils.hpp"



namespace ConsMenu {
    /*
    Contains the exceptions used.
    */
    namespace MenuExc {
        class BaseMenuExc : public std::exception {
            public:
                const char* what() const noexcept override;
        };


            //Raised whenever all the menus are exited.
            class MenuExit : public BaseMenuExc {
                public:
                    const char* what() const noexcept override;
            };

            class MenuChExit : public BaseMenuExc {
                public:
                    const char* what() const noexcept override;
            };


            class MenuChInvalidInput : public BaseMenuExc {
                public:
                    const char* what() const noexcept override;
            };

                class MenuChInputNotTag : public MenuChInvalidInput {
                    public:
                        const char* what() const noexcept override;
                };

                class MenuChInputInvalidTag : public MenuChInvalidInput {
                    public:
                        const char* what() const noexcept override;
                };
    };



    /*
    Represents a screen. This is something that is displayed to the console.
    */
    class Screen {
        public:
            // Shows the screen.
            virtual void show();
    };



    class Menu : public Screen {
        /*
        Represents a screen for user input to move to other screens.
        */
        public:
            bool is_main_menu = false;

            // The title of the menu.
            std::string title;
            Console::Color::SpecStyle title_specstyle = Console::Color::SpecStyle(false, Console::Color::white, Console::Color::black, true);

            // The description of the menu.
            std::string desc;
            Console::Color::SpecStyle desc_specstyle = Console::Color::SpecStyle();

            // The style of the border.
            std::string border = "+---==---";
            Console::Color::SpecStyle border_specstyle = Console::Color::SpecStyle(false, Console::Color::blue, Console::Color::black);

            // The base color used in the menu.
            Console::Color::GenStyle base_color;



            /*
            Draws the borders found above and below the title and description.
            */
            void show_border();


            /*
            Shows the header, which includes the title, description, and borders.
            */
            void show_header();

            /*
            Draws the rest of the menu. Should be overridden.
            */
            virtual void show() override;
    };



    /*
    Represents a choice presented in a ChoiceMenu.
    */
    class Choice {
        public:
            std::string description = "This is the default description.";
            std::unique_ptr<Screen> screen;

            Choice(std::string _description);
    };


;
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

            SelectMenu();

            /*
            Adds the opening and closing brackets to a tag.
            Ex. "x" -> "[x]"
            */
            std::string add_style_to_tag(const std::string& tag);

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
