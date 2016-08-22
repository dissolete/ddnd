#include "DDNDApp.hpp"

DDNDApp::DDNDApp(const std::string theTitle, int windowWidth, int windowHeight):
    CRE::App(theTitle, windowWidth, windowHeight),
    _groupManager(),
    _tileMapManager()
{}

DDNDApp::~DDNDApp(){}

void DDNDApp::init_asset_handlers(void)
{
    // Set default font for the textmanager
    _textManager.set_font("Resources/arial.ttf");
}

void DDNDApp::init_screen_factory(void)
{
    // Prevent new events from being created by holding down a key
    _window.setKeyRepeatEnabled(false);

    // Add game states here
    _stateManager.add_active_state(new(std::nothrow) PlayState("PlayState", *this));
    _stateManager.add_active_state(new(std::nothrow) CRE::SplashState(*this));
}

void DDNDApp::handle_cleanup()
{
    // Destroy anything that was allocated in this class here
}
