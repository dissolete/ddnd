#include "PlayState.hpp"

PlayState::PlayState(std::string stateID, CRE::App & theApp):
    CRE::State(stateID, theApp)
{
}

PlayState::~PlayState()
{
}

void PlayState::init()
{
    // Initialize parent state
    CRE::State::init();
}

void PlayState::reinit()
{
}

void PlayState::pause()
{
    // Pause parent state
    CRE::State::pause();
}

void PlayState::resume()
{
    CRE::State::resume();
}

void PlayState::handle_events(sf::Event theEvent)
{

}

void PlayState::update()
{

}

void PlayState::update_variable()
{

}

void PlayState::handle_cleanup()
{

}
