#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include <string>
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
        *
        */
        virtual void handle_events(sf::Event theEvent);

        /**
        *
        */
        virtual void update(void);

        /**
        *
        */
        virtual void update_variable(float elapsedTime);

        /**
        *
        */
        virtual void draw(void);

    protected:

        /**
        *
        */
        virtual void handle_cleanup(void);
}

#endif
