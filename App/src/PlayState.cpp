#include "PlayState.hpp"

PlayState::PlayState(std::string stateID, CRE::App & theApp):
    CRE::State(stateID, theApp),
    _grid(),
    _gridTexture(),
    _theView(),
    _timeWhenCameraMoved(0.f)
{
}

PlayState::~PlayState()
{
}

void PlayState::init()
{
    // Initialize parent state
    CRE::State::init();

    // Load grid
    if(not _gridTexture.loadFromFile("Resources/Grid.png"))
    {
        _theApp.quit(CRE::STATUS_ASSET_COULDNT_BE_LOADED);
    }
    else
    {
        _grid.setTexture(_gridTexture);
    }

    // Load tilemaps
    _tileMapManager.load_new_tilemap("TestTileMap", "Resources/TileMaps/testTileMap.tmx");

    // Intitialize the view
    _theView.reset(sf::FloatRect(0, 0, _theApp._windowWidth, _theApp._windowHeight));
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
    if(theEvent.type == sf::Event::Resized)
    {
        sf::FloatRect visibleArea(0, 0, theEvent.size.width, theEvent.size.height);
        _theView.reset(visibleArea);
    }
}

void PlayState::update()
{

}

void PlayState::update_variable(float elapsedTime)
{
    // Update the view if needed
    update_view(elapsedTime);
}

void PlayState::draw()
{
    // Set view
    _theApp._window.setView(_theView);

    // Clear the screen with black before drawing
    _theApp._window.clear(sf::Color::Black);

    // Draw layers
    _tileMapManager.get_active().draw_layers(0, 0, _theApp._window);

    // Draw the grid, requires that the view is reset
    //_theApp._window.setView(_theApp._window.getDefaultView());
    //_theApp._window.draw(_grid);

    // App auto-refreshes window
}

void PlayState::handle_cleanup()
{

}

void PlayState::update_view(float elapsedTime)
{
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(_theApp._window);

    // Get info about the view
    sf::Vector2f viewCenter = _theView.getCenter();
    sf::Vector2u viewSize = _theApp._window.getSize();

    // Calculate offset to move based on elapsed time since last frame
    float deltaX = elapsedTime * CAMERA_MOVE_SPEED;

    // Get the current active tilemap being rendered to the screen
    CRE::TileMap &activeMap = _tileMapManager.get_active();

    // Check if the mouse has moved into the margin to move the camera
    if(mousePixelPos.x < CAMERA_MOVE_MARGIN)
        viewCenter.x -= deltaX;
    else if(mousePixelPos.x > viewSize.x - CAMERA_MOVE_MARGIN)
        viewCenter.x += deltaX;
    if(mousePixelPos.y < CAMERA_MOVE_MARGIN)
        viewCenter.y -= deltaX;
    else if(mousePixelPos.y > viewSize.y - CAMERA_MOVE_MARGIN)
        viewCenter.y += deltaX;

    // Can the tilemap fit inside the window currently?
    if(_theApp._window.getSize().x < activeMap.get_width() and
        _theApp._window.getSize().y < activeMap.get_height())
    {
        // If the tilemap CAN fit inside the window, then check if the
        // camera has moved too far (IE the camera has moved off the
        // edges of the tilemap). Move the camera back if it has.
        if(viewCenter.x < viewSize.x / 2)
            viewCenter.x += (viewSize.x / 2) - viewCenter.x;
        else if(viewCenter.x > activeMap.get_width() - viewSize.x / 2)
            viewCenter.x -= viewCenter.x - (activeMap.get_width() - viewSize.x / 2);
        if(viewCenter.y < viewSize.y / 2)
            viewCenter.y += viewSize.y / 2 - viewCenter.y;
        else if(viewCenter.y > activeMap.get_height() - viewSize.y / 2)
            viewCenter.y -= viewCenter.y - (activeMap.get_height() - viewSize.y / 2);
    }
    
    // Set the new viewCenter if it was changed
    _theView.setCenter(viewCenter);
}
