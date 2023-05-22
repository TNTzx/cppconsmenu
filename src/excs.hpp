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
};