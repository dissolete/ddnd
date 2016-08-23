#ifndef DDNDAPP_HPP
#define DDNDAPP_HPP

#include "CRApp.hpp"
#include "CRTileMapManager.hpp"
#include "CRGroupManager.hpp"
#include "PlayState.hpp"
#include "SplashState.hpp"

class DDNDApp : public CRE::App
{
    public:
        ///////////////
        // VARIABLES //
        ///////////////

        /// The GroupManager to handle entities
        CRE::GroupManager _groupManager;

        /// The TileMapManager to handle tilemaps
        CRE::TileMapManager _tileMapManager;

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
