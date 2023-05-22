#include "./excs.hpp"



namespace ConsMenu {
    /*
    Contains the exceptions used.
    */
    namespace MenuExc {
        const char* BaseMenuExc::what() const noexcept {return "Base menu exception.";}

            const char* MenuExit::what() const noexcept {return "Exited from menu.";}

            const char* MenuChExit::what() const noexcept {return "Exited from choice menu.";}

            const char* MenuChInvalidInput::what() const noexcept {return "Invalid choice input.";}

                const char* MenuChInputNotTag::what() const noexcept {return "Input is not a valid tag.";}

                const char* MenuChInputInvalidTag::what() const noexcept {return "Input is not a tag listed in the choices.";}
    };
};