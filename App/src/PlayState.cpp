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
    // Update the view if needed
    update_view();
}

void PlayState::update_variable(float elaspedTime)
{

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

void PlayState::update_view()
{
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(_theApp._window);

    // Get info about the view
    sf::Vector2f viewCenter = _theView.getCenter();
    sf::Vector2u viewSize = _theApp._window.getSize();

    /* TODO: The logic in this function can possibly be rearranged to
    speed things up. For example, instead of starting the if statement off
    with a check to see if it's been enough time to move the camera, first
    check if the mouse is in the the CAMERA_MOVE_MARGIN. Since it is more
    likely that the mouse is not in the margin, there may be less function
    calls on average each time this update_view function is called if the
    logic is rearranged.

    EX: (psuedocode)
    if mouse is in margin: <-- This is most likely to fail, 1 if statement checked, skipping the below
        if camera is okay to move: <-- skipped on average
            specifically check which margin the mouse is in: <-- skipped on average
                adjust camera
            check if the tilemap can fit:
                readjust camera as needed

    Current:
    if camera is okay to move: <-- More likely to succeed
        specifically check which margin the mouse is in: <-- Resulting in these if statements being called more on average
            adjust camera
        check if tilemap can fit: <-- Tested more on average
            readjust camera as needed

    The EX code might be a little messier, but should run faster. The question
    is, is it really worth the speed change?
    */
    if(CRE::State::get_elapsed_time() - _timeWhenCameraMoved > 1 / CAMERA_MOVE_SPEED)
    {
        _timeWhenCameraMoved = CRE::State::get_elapsed_time();

        if(mousePixelPos.x < CAMERA_MOVE_MARGIN)
            viewCenter.x -= CAMERA_MOVE_PIXELS;
        else if(mousePixelPos.x > viewSize.x - CAMERA_MOVE_MARGIN)
            viewCenter.x += CAMERA_MOVE_PIXELS;
        if(mousePixelPos.y < CAMERA_MOVE_MARGIN)
            viewCenter.y -= CAMERA_MOVE_PIXELS;
        else if(mousePixelPos.y > viewSize.y - CAMERA_MOVE_MARGIN)
            viewCenter.y += CAMERA_MOVE_PIXELS;


        // UNCOMMENT/COMMENT BELOW THIS IF YOU DO/DO NOT WANT THE VIEW TO MOVE
        // OUTSIDE THE BOUNDS OF THE TILEMAP

        // DONT try readjusting theView if the tilemap is not large enough
        // to fit the window otherwise crazy shit happens. This if statement
        // checks to see if the tilemap can fit the current windowsize
        if(_theApp._window.getSize().x < _tileMapManager.get_active().get_width()
            and _theApp._window.getSize().y < _tileMapManager.get_active().get_height())
        {
            // Test if the view has moved outside the bounds of the tilemap, if it has
            // then move it back
            if(viewCenter.x < viewSize.x / 2)
                viewCenter.x += CAMERA_MOVE_PIXELS;
            else if(viewCenter.x > _tileMapManager.get_active().get_width() - viewSize.x / 2)
                viewCenter.x -= CAMERA_MOVE_PIXELS;
            if(viewCenter.y < viewSize.y / 2)
                viewCenter.y += CAMERA_MOVE_PIXELS;
            else if(viewCenter.y > _tileMapManager.get_active().get_height() - viewSize.y / 2)
                viewCenter.y -= CAMERA_MOVE_PIXELS;
        }
    }

    // Set the new viewCenter if it was changed
    _theView.setCenter(viewCenter);
}
