#include "CommonLevel.h"
#include "DemoUIButton.h"
#include "ChangeStateCommand.h"
#include "CreateArchetype.h"
#include "Color.h"

void MainMenu::Initialize()
{
    // Set current state
    State::sCurrentState = this;

	m_backgroundColor = Color::SKY;

	// Set Camera
	// You don't need to do this anymore
	//camera.Initialize(int(State::m_width), int(State::m_height));
	// Set position of the camera
	camera.position.Set(0, 0, 0);

	// Set main font
	// Load the font file to use as a main font
	// and set the default size of it
	mainFont = TTF_OpenFont("font/Default.ttf", 48);

    // Set background image
    background.SetName("Background");
    //float scale = (m_width > m_height ? m_width : m_height);
    background.transform.position.Set(0, 0, 0.f);
    background.transform.SetScale(1.f, 1.f);
    background.sprite.LoadImage("texture/Backdrop3.png", m_renderer);
    background.sprite.isHud = true;
    AddComponentToObject(&background, eComponentTypes::DemoRescale);
    AddObject(&background);

    // Set title text
    CreateHudText(titleText, "Title", 0, 200.f, 650.f, 130.f, mainFont, "GAM150 Demo", Color::WHITE);

    // basic start button create and initialize
    DemoUIButton* button = CreateUIButton(basicStartButton, "BasicStartButton", 0, 40.f, 256.f, 40.f, 
                            "StartGame.png", "StartGameHover.png", eCommandTypes::ChangeStateCommand);
    dynamic_cast<ChangeStateCommand*>(button->mButtonEvent)->mChangeLevel = LV_Level1;
    // Set basic demo text
    CreateHudText(basicText, "Basic", -300.f, 40.f, 230.f, 40.f, mainFont, "Basic Demo", Color::BLACK);

    // topdown start button
    button = CreateUIButton(topdownStartButton, "TopdownStartButton", 0, -40.f, 256.f, 40.f,
                            "StartGame.png", "StartGameHover.png", eCommandTypes::ChangeStateCommand);
    dynamic_cast<ChangeStateCommand*>(button->mButtonEvent)->mChangeLevel = LV_LevelTopdown;
    // Set topdown text
    CreateHudText(topdownText, "Topdown", -300.f, -40.f, 230.f, 40.f, mainFont, "Topdown", Color::BLACK);

    // platformer start button create and initialize
    button = CreateUIButton(platformerStartButton, "PlatformerStartButton", 0, -120.f, 256.f, 40.f,
                            "StartGame.png", "StartGameHover.png", eCommandTypes::ChangeStateCommand);
    dynamic_cast<ChangeStateCommand*>(button->mButtonEvent)->mChangeLevel = LV_LevelPlatformer;
    // Set platformer text
    CreateHudText(platformerText, "Platformer", -300.f, -120.f, 230.f, 40.f, mainFont, "Platformer", Color::BLACK);


    // exit Button button create and initialize
    
    button = CreateUIButton(exitButton, "ExitButton", 0, -200.f, 256.f, 40.f,
                            "ExitGame.png", "ExitGameHover.png", eCommandTypes::QuitCommand);
    
    
    InitializeObjects();
}

void MainMenu::Update(float dt)
{
	/******************* State ******************/

    UpdateObjects(dt);

	// Must be one of the last functions called at the end of State Update
	UpdatePhysics(dt);
	Render(dt);
}

void MainMenu::Close()
{
	// Wrap up state
	ClearBaseState();
}