#include "DDNDApp.hpp"

DDNDApp::DDNDApp(const std::string theTitle, int windowWidth, int windowHeight):
    CRE::App(theTitle, windowWidth, windowHeight)
{}

DDNDApp::~DDNDApp(){}

void DDNDApp:init_asset_handlers(void)
{
    // Set default font for the textmanager
    _textManager.set_font("resources/arial.ttf");

    // Load tilemaps
    
}

void TestApp::init_screen_factory(void)
{
    // Prevent new events from being created by holding down a key
    _window.setKeyRepeatEnabled(false);

    // Add game states here
    _stateManager.add_active_state(new(std::nothrow) CRE::SplashState(*this));
}

void TestApp::handle_cleanup()
{
    // Destroy anything that was allocated in this class here
}
