#include "MainMenuState.hpp"
#include "TextureManager.hpp"
#include "Engine.hpp"
#include "InputHandler.hpp"
#include "MessageHandler.hpp"
#include "GUIButton.hpp"
#include "ActionManager.hpp"
#include "ActionExit.hpp"
#include "ActionNewGame.hpp"
#include "GUIAnimatedBackground.hpp"
#include "SoundManager.hpp"
#include <iostream>
#include <time.h>

void MainMenuState::Enter(StateMachine *sm)
{
    TextureManager::Instance()->LoadTexture("graphic/interface_3_source/parts_w_effect/001.png", "FirstLayerMenu");
    TextureManager::Instance()->LoadTexture("graphic/interface_3_source/parts_w_effect/004.png", "SecondLayerMenu");
    TextureManager::Instance()->LoadTexture("graphic/background_1.jpg", "Space_1");
    TextureManager::Instance()->LoadTexture("graphic/Button_1.png", "Button");
    TextureManager::Instance()->LoadTexture("graphic/Button_Selected.png", "Button_Selected");
    TextureManager::Instance()->LoadTexture("graphic/Button_Clicked.png", "Button_Clicked");

    MessageHandler::Instance()->LoadFont("font/Andromeda.ttf", 32, "Andromeda");
    MessageHandler::Instance()->LoadFont("font/Omegacentauri.ttf", 32, "Centauri");
    MessageHandler::Instance()->LoadFont("font/ExonRegular.otf", 20, "DetailFont");

    SoundManager::Instance()->LoadSound("sounds/BR/music/Atmospheric_Rise.ogg", "Music");
    SoundManager::Instance()->PlaySound("Music");

    ActionManager::Instance()->RegisterAction("ActionExit", new ActionExit());
    ActionManager::Instance()->RegisterAction("ActionNewGame", new ActionNewGame());

    GUIAnimatedBackground *background = new GUIAnimatedBackground("Space_1");
    GUIEntity *first_layer = new GUIEntity("FirstLayerMenu");
    GUIEntity *second_layer = new GUIEntity("SecondLayerMenu");

    GUIButton *new_game_button = new GUIButton("Button", "NEW GAME");
    GUIButton *exit_button = new GUIButton("Button", "Exit");
    new_game_button->SetPosition(Vector(WIDTH/2, 200));
    new_game_button->SetOriginSize(1112, 354);
    new_game_button->SetSize(250, 70);
    new_game_button->SetAction(ActionManager::Instance()->GetAction("ActionNewGame"));

    exit_button->SetPosition(Vector(WIDTH/2, 280));
    exit_button->SetOriginSize(1112, 354);
    exit_button->SetSize(250, 70);
    exit_button->SetAction(ActionManager::Instance()->GetAction("ActionExit"));

    background->SetPosition(Vector(WIDTH/2,HEIGHT/2));
    background->SetAnimated(true);
    background->SetTextSize(WIDTH, HEIGHT);
    background->SetOriginPos(0,0);
    background->SetSize(WIDTH, HEIGHT);

    first_layer->SetPosition(Vector(WIDTH/2 + 100, HEIGHT/2));
    first_layer->SetOriginSize(2048, 2048);
    first_layer->SetSize(HEIGHT, HEIGHT);
    
    second_layer->SetPosition(Vector(WIDTH/2 + 100, HEIGHT/2));
    second_layer->SetOriginSize(2048, 2048);
    second_layer->SetSize(HEIGHT, HEIGHT);

    m_list_gui_objects.push_back(background);
    m_list_gui_objects.push_back(first_layer);
    m_list_gui_objects.push_back(second_layer);
    m_list_gui_objects.push_back(new_game_button);
    m_list_gui_objects.push_back(exit_button);
}

void MainMenuState::Update(StateMachine *sm)
{
    if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Engine::Instance()->IsRunning = false;
    }
    
    for(std::vector<GUIEntity *>::iterator it = m_list_gui_objects.begin(); it != m_list_gui_objects.end(); ++it)
    {
        (*it)->Update();
    }
}

void MainMenuState::Execute(StateMachine *sm)
{
    for(std::vector<GUIEntity *>::iterator it = m_list_gui_objects.begin(); it != m_list_gui_objects.end(); ++it)
    {
        (*it)->Draw();
    }
    MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), "Version 0.1", "DetailFont", Vector(WIDTH-80, 10), CORNER);
    MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), "A game by NAUTILUS SOFTWARE", "DetailFont", Vector(20, HEIGHT - 30), CORNER);
    MessageHandler::Instance()->PrintText(Engine::Instance()->GetRenderer(), "SDL Project", "Centauri", Vector(WIDTH/2 - 70, 85), CENTER);
}

void MainMenuState::Exit(StateMachine *sm)
{

}