#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CRCore.hpp"

class PlayState : public CRE::State
{
    public:

        /**
        *
        */
        PlayState(std::string stateID, CRE::App & theApp);

        /**
        *
        */
        ~PlayState();

        /**
        *
        */
        virtual void init();

        /**
        *
        */
        virtual void reinit();

        /**
        *
        */
        virtual void pause();

        /**
        *
        */
        virtual void resume();

        /**
        * Handle any input events here. Pretty self explanatory
        */
        virtual void handle_events(sf::Event theEvent);

        /**
        * Updates the state. Big boy update function. This can be called
        * more than once per frame and is done so by the App class.
        */
        virtual void update(void);

        /**
        * Update any variables that may need to know how long it has been
        * since the last draw call.
        * @param[in] elapsedTime since last draw call.
        */
        virtual void update_variable(float elapsedTime);

        /**
        * Called by App class at the end of each frame after all updates.
        * Draw anything needed in this function. Window is refreshed
        * automatically by the App class.
        */
        virtual void draw(void);

    protected:

        /**
        * Called by the StateManager when this state gets destroyed.
        * If there is anything dynamically allocated in this state,
        * properly clean up in this function.
        */
        virtual void handle_cleanup(void);

    private:

        /**
        * Determines if the view must be moved based on the mouse position
        * and moves it accordingly. Function is private because this state
        * should be the only thing that calls this function.
        */
        void update_view(float);

        /// How fast the camera moves is elapsedTimeSinceLastFrame * CAMERA_MOVE_SPEED
        const float CAMERA_MOVE_SPEED = 500;

        /// The number of pixels away from the edge of the screen the mouse
        /// has to be in order for the camera to move
        const float CAMERA_MOVE_MARGIN = 10;

        /// The grid that is displayed on top of everything
        sf::Sprite _grid;

        /// The texture used by the Grid sprite
        sf::Texture _gridTexture;

        /// This state's tilemap manager handles the tilemaps for the game
        CRE::TileMapManager _tileMapManager;

        /// The view that determines what is shown to the screen
        sf::View _theView;

        /// Used to control the speed of the camera movement
        /// See: definition of update_view for demonstration of use
        float _timeWhenCameraMoved;
};

#endif
