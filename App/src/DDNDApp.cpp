#include "DDNDApp.hpp"

DDNDApp::DDNDApp(const std::string theTitle, int windowWidth, int windowHeight):
    CRE::App(theTitle, windowWidth, windowHeight),
    _groups(),
    _tilemaps()
{}

DDNDApp::~DDNDApp(){}

void DDNDApp::init_asset_handlers(void)
{
    // Set default font for the textmanager
    _textManager.set_font("resources/arial.ttf");

    // Load tilemaps

}

void DDNDApp::init_screen_factory(void)
{
    // Prevent new events from being created by holding down a key
    _window.setKeyRepeatEnabled(false);

    // Add game states here
    _stateManager.add_active_state(new(std::nothrow) CRE::SplashState(*this));
    _stateManager.add_active_state(new(std::nothrow) PlayState("PlayState", *this));
}

void DDNDApp::handle_cleanup()
{
    // Destroy anything that was allocated in this class here
}
