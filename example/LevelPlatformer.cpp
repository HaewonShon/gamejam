#include "CommonLevel.h"
#include "PlatformerContactListener.h"
#include "DemoPlayerController.h"
#include "DemoPlayerAnimation.h"
#include "CommonLevel.h"
#include "DemoCollisionTrigger.h"
#include "DemoChasePlayer.h"
#include "LevelPlatformer.h"
#include "Color.h"
#include "CreateArchetype.h"
#include "DemoCameraLogic.h"

namespace 
{
    Level_ID            nextLevel;
}

void LevelPlatformer::Initialize()
{
    // Set current state
    State::sCurrentState = this;

    // Set background color
    m_backgroundColor = Color::SKY;
    // Set position of the camera
    camera.position.Set(0, 0, 0);
    State::m_pCamera = &camera;

    // Set main font
    // Load the font file to use as a main font
    // and set the default size of it
    mainFont = TTF_OpenFont("font/Default.ttf", 48);

    // Set custom physics world
    b2Vec2 gravity(0.f, -9.8f * 1.2f);
    m_useBuiltInPhysics = false;
    SetCustomPhysicsWorld(gravity);
    SetCustomContactListener(new PlatformerContactListener);

    // Set next level
    nextLevel = LV_MainMenu;


    /*
     * Camera Controller
     */
    cameraController.SetName("CameraController");
    AddComponentToObject(&cameraController, eComponentTypes::DemoCameraLogic);
    AddObject(&cameraController);

    /*
     * Platform
     */
    CreateBody(platform1, "platform1", -1025.f, 625.f, 50.f, 2000.f, 
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::WALLGREY);
    CreateBody(platform2, "platform2", 0.f, -350.f, 2000.f, 50.f,
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::GREEN);
    CreateBody(platform3, "platform3", 1000.f - 25.f, -350.f - 700.f * 0.5f - 25.f, 50.f, 700.f,
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::BROWN);
    CreateBody(platform4, "platform4", 1500.f - 25.f, -350.f - 700.f * 0.5f - 25.f, 50.f, 700.f,
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::BROWN);
    CreateBody(platform5, "platform5", 1225.f, -1075, 550.f, 50.f,
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::BROWN);
    CreateBody(platform6, "platform6", 1950.f, -350.f, 1000.f, 50.f,
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::GREEN);
    CreateBody(platform7, "platform7", 3325.f, 150.f, 800.f, 50.f,
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::GREEN);
    CreateBody(platform8, "platform8", 3750.f, 1125.f, 50.f, 2000.f,
        CustomPhysics::STATIC, CustomPhysics::BOX, Color::WALLGREY);
    CreateBody(bridge, "bridge", 800.f, -350.f + 50.f, 450.f, 50.f,
        CustomPhysics::DYNAMIC, CustomPhysics::BOX, Color::WHITE, "texture/Rock.png");

    // stair platform
    for (int i = 0; i < 5; ++i)
    {
        std::string name = "Stair" + std::to_string(i + 1);
        float height = 150.f + (100.f * i);
        CreateBody    (stairPlatforms[i], name.c_str(),
                                2475.f + (100.f * i),   -350.f + height * 0.5f - 25.f, 
                                100.f, height,
                                CustomPhysics::STATIC, CustomPhysics::BOX, Color::WALLGREY);
    }


    /*
     * Check point
     */
    CreateCheckPoint(checkPoint1, "check1", -500.f, platform2.transform.position.y + platform2.transform.GetHalfScale().y, 64.f, 121.f);
    CreateCheckPoint(checkPoint2, "check2", 500.f, platform2.transform.position.y + platform2.transform.GetHalfScale().y, 64.f, 121.f);
    CreateCheckPoint(checkPoint3, "check3", 1950.f, platform2.transform.position.y + platform2.transform.GetHalfScale().y, 64.f, 121.f);
    CreateCheckPoint(checkPoint4, "check4", 3000.f, platform7.transform.position.y + platform7.transform.GetHalfScale().y, 64.f, 121.f);
    // Set check point 1's position, if this state is not restarted
    if (!m_game->IsRestart())
    {
        DemoPlayerController::sStartPosition.Set(
            checkPoint1.transform.position.x, checkPoint1.transform.position.y);
    }

    /*
     * Damage Trap
     */
    for (int i = 0; i < 9; ++i)
    {
        std::string name = "Spike" + std::to_string(i + 1);
        CreateDamageTrap(spikes[i], name.c_str(), "Player", 
            1025.f + (50.f * i), -1075.f + 50.f, 50.f, 50.f, CustomPhysics::STATIC, true, Color::WHITE, 
            (i % 2 == 0 ? "texture/Spike1.png" : "texture/Spike2.png"));

    }

    /*
     * Health Item
     */
    CreateDamageTrap(item1, "item1", "Player", 520,       -300,   50.f, 50.f,
        CustomPhysics::STATIC, true, Color::WHITE, "texture/Lives.png", -1, false);
    CreateDamageTrap(item2, "item2", "Player", 2100.f,    -300.f, 50.f, 50.f,
        CustomPhysics::STATIC, true, Color::WHITE, "texture/Lives.png", -1, false);
    CreateDamageTrap(item3, "item3", "Player", 2925,      200,    50.f, 50.f,
        CustomPhysics::STATIC, true, Color::WHITE, "texture/Lives.png", -1, false);

    /*
     * Level Clear
     */
    CreatePlatformerLevelClear(levelClear, "LevelClear",
        3625.f, platform7.transform.position.y + platform7.transform.GetHalfScale().y + 128.f * 0.5f,
        64.f, 128.f, nextLevel);

    /*
     * Player
     */
    CreatePlatformerPlayer(player, "Player", 50.f, 50.f);

    // Create enemy
    CreatePlatformerEnemy(enemy1, "Enemy1", "Player", 0, -300.f, 50.f, 50.f, "ToadDinoWalk.png", 3, 12.f, true);
    CreatePlatformerEnemy(enemy2, "Wasp", "Player", 2500.f, 150.f, 50.f, 50.f, "wasp.png", 2, 12.f, false);


    /*
     * Game Over screen
     */
    CreateHudSprite(gameOverScreen, "GameOverScreen", 0, 0, 2560.f, 1920.f, "texture/GameOverScreen.png", false);
   
    InitializeObjects();
}

void LevelPlatformer::Update(float dt)
{
    UpdateObjects(dt);
    // Move to main menu by pressing 'N' key
    if (m_input->IsTriggered(SDL_SCANCODE_N))
        m_game->Change(LV_MainMenu);

    // Must be one of the last functions called at the end of State Update
    UpdateCustomPhysics(dt);

    DemoCameraLogic* cameraLogic;
    cameraController.GetComponent(eComponentTypes::DemoCameraLogic, cameraLogic);
    cameraLogic->SyncCameraWithTarget();

    Render(dt);
}

void LevelPlatformer::Close()
{
    // Deallocate custom physics world
    RemoveCustomPhysicsWorld();

    // Wrap up state
    ClearBaseState();
}

