#include "LevelTopdown.h"
#include "Game.h"
#include "Color.h"
#include "TopdownContactListener.h"
#include "DemoReposition.h"
#include "CreateArchetype.h"

void LevelTopdown::Initialize()
{
    // Set current state
    State::sCurrentState = this;

    // Set background color
    m_backgroundColor = Color::BLACK;
    // Set position of the camera
    camera.position.Set(0, 0, 0);
    State::m_pCamera = &camera;

    // Set main font
    // Load the font file to use as a main font
    // and set the default size of it
    mainFont = TTF_OpenFont("font/Default.ttf", 48);

    // Set custom physics world
    b2Vec2 gravity(0.f, 0.f);
    m_useBuiltInPhysics = false;
    SetCustomPhysicsWorld(gravity);
    SetCustomContactListener(new TopdownContactListener);

    /*
     * Player
     */
    CreateTopdownPlayer(player, "Player", 58.f, 44.f);

    /*
     * Enemy Spwaner
     */
    enemySpawner.SetName("EnemySpawner");
    // Set the position of the object
    enemySpawner.transform.position.SetZero();
    // Set the scale of the object
    enemySpawner.transform.SetScale(10, 10);
    AddComponentToObject(&enemySpawner, eComponentTypes::DemoEnemySpawner);
    AddObject(&enemySpawner);


    /*
     * Game over Screen
     */
    CreateHudSprite(gameOverScreen, "GameOverScreen", 0, 0, 2560.f, 1920.f, "texture/GameOverScreen.png", false);

    /*
     * Score
     */
    CreateHudText(score, "Score", 100.f, -30.f, 100.f, 50.f, mainFont, "0", Color::WHITE);
    DemoReposition* reposition = dynamic_cast<DemoReposition*>(
        AddComponentToObject(&score, eComponentTypes::DemoReposition));
    reposition->SetBase(DemoRepositionBase::TopLeft);

    /*
     * Initialize all objects
     */
    InitializeObjects();
}

void LevelTopdown::Update(float dt)
{
    UpdateObjects(dt);
    // Move to main menu by pressing 'N' key
    if (m_input->IsTriggered(SDL_SCANCODE_N))
        m_game->Change(LV_MainMenu);


    if (m_input->IsTriggered(SDL_SCANCODE_R))
        m_game->Restart();


    // Must be one of the last functions called at the end of State Update
    UpdateCustomPhysics(dt);
    Render(dt);
}

void LevelTopdown::Close()
{
    // Deallocate custom physics world
    RemoveCustomPhysicsWorld();

    // Wrap up state
    ClearBaseState();
}
