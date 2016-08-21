#ifndef DDNDAPP_HPP
#define DDNDAPP_HPP

#include "CRApp.hpp"

class DDNDApp : public App
{
    public:
        ///////////////
        // VARIABLES //
        ///////////////
        GroupManager _groups;

        /**
        *
        */
        DDNDApp(const std::string theTile = "DDND", int windowWidth = 800,
                    int windowHeight = 600);

        /**
        *
        */
        ~DDNDApp();

    protected:

        /**
        *
        */
        virtual void init_asset_handlers(void);

        /**
        *
        */
        virtual void init_screen_factory(void);

        /**
        *
        */
        virtual void handle_cleanup(void);
};

#endif
