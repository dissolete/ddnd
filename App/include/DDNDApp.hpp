#ifndef DDNDAPP_HPP
#define DDNDAPP_HPP

#include "CRApp.hpp"
#include "CRTileMapManager.hpp"
#include "CRGroupManager.hpp"

class DDNDApp : public App
{
    public:
        ///////////////
        // VARIABLES //
        ///////////////

        /// The GroupManager to handle entities
        CRE::GroupManager _groups;

        /// The TileMapManager to handle tilemaps
        CRE::TileMapManager _tilemaps;

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
