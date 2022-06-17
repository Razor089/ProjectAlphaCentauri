#include "MainMenuState.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"
#include "InputHandler.hpp"
#include <iostream>

void MainMenuState::Enter(StateMachine *sm)
{
    TextureManager::Instance()->LoadTexture("graphic/interface_3_source/parts_w_effect/001.png", "FirstLayerMenu");
    TextureManager::Instance()->LoadTexture("graphic/interface_3_source/parts_w_effect/004.png", "SecondLayerMenu");

    GUIEntity *background = new GUIEntity("Space_1");
    GUIEntity *first_layer = new GUIEntity("FirstLayerMenu");
    GUIEntity *second_layer = new GUIEntity("SecondLayerMenu");

    background->SetPosition(Vector(WIDTH/2,HEIGHT/2));
    background->SetNumFrames(1);
    background->SetOriginSize(2048,2048);
    background->SetSize(WIDTH, WIDTH);

    first_layer->SetPosition(Vector(WIDTH/2 + 100, HEIGHT/2));
    first_layer->SetNumFrames(1);
    first_layer->SetOriginSize(2048, 2048);
    first_layer->SetSize(HEIGHT, HEIGHT);
    
    second_layer->SetPosition(Vector(WIDTH/2 + 100, HEIGHT/2));
    second_layer->SetNumFrames(1);
    second_layer->SetOriginSize(2048, 2048);
    second_layer->SetSize(HEIGHT, HEIGHT);

    m_list_gui_objects.push_back(background);
    m_list_gui_objects.push_back(first_layer);
    m_list_gui_objects.push_back(second_layer);
}

void MainMenuState::Update(StateMachine *sm)
{
    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Engine::Instance()->IsRunning = false;
    }
}

void MainMenuState::Execute(StateMachine *sm)
{
    for(std::vector<GUIEntity *>::iterator it = m_list_gui_objects.begin(); it != m_list_gui_objects.end(); ++it)
   {
        (*it)->Draw();
    }
}

void MainMenuState::Exit(StateMachine *sm)
{

}