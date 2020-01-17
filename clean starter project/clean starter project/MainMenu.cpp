#include "CommonLevel.h"
#include "DemoUIButton.h"

const SDL_Color WHITE = { 255, 255, 255, 255 };
const SDL_Color MAROON = { 128, 0, 0, 255 };

void MainMenu::Initialize()
{
    State::sCurrentState = this;
	m_backgroundColor = MAROON;

	// Set Camera
	// You don't need to do this anymore
	//camera.Initialize(int(State::m_width), int(State::m_height));
	// Set position of the camera
	camera.position.Set(0, 0, 0);

	// Set main font
	// Load the font file to use as a main font
	// and set the default size of it
	mainFont = TTF_OpenFont("font/Default.ttf", 48);

	CreateAndRegisterHudText(&titleText, "Main Menu", "Title");
	titleText.transform.position.Set(0.f, 200.f, 0.f);

	CreateAndRegisterHudText(&instructionsText, "Press C to go to next level", "Instructions");
	instructionsText.transform.position.Set(0.f, -200.f, 0.f);


    CreateExitButton();
    InitializeObjects();
}

void MainMenu::Update(float dt)
{
	/******************* State ******************/
    UpdateObjects(dt);

	// Pause current state and move to pause state
	if (m_input->IsTriggered(SDL_SCANCODE_P))
		m_game->Pause();

	// Must be one of the last functions called at the end of State Update
	UpdatePhysics(dt);
	Render(dt);
}

void MainMenu::Close()
{
	// Wrap up state
	ClearBaseState();
}

void MainMenu::CreateAndRegisterHudText(Object *textObject, const char *textContents, const char *id)
{
	// Set the object's name
	textObject->SetName(id);

	// Set the scale of the object
	textObject->transform.SetScale(650, 130);

	// Set the text to render out
	textObject->text.SetText(State::m_renderer, textContents, mainFont);

	// Set the colors r,g,b,a (0~255)
	textObject->text.color = WHITE;

	// Set either if the object to be hud or not
	textObject->text.isHud = true;

	// Register the object to the state
	AddObject(textObject);
}

void MainMenu::CreateExitButton()
{
    // Set exit button
    exitButton.SetName("ExitButton");

    /*
    * Transform
    */
    // Set the position of the object
    exitButton.transform.position.Set(0, 0, 0.f);
    // Set the scale of the object
    exitButton.transform.SetScale(256.f, 40.f);


    /*
    * Sprite
    */
    // Set the image of sprite
    exitButton.sprite.LoadImage("texture/ExitGame.png", State::m_renderer);
    // Set either if the object to be hud or not
    exitButton.sprite.isHud = true;

    /*
    * Component
    */
    // Add component to the object
    DemoUIButton* button = dynamic_cast<DemoUIButton*>(AddComponentToObject(&exitButton, eComponentTypes::DemoUIButton));
    // Set component's information
    button->mDefaultSpriteFile = "texture/ExitGame.png";
    button->mHoveredSpriteFile = "texture/ExitGameHover.png";
    // Add command to the component
    button->mButtonEvent = CreateCommand(eCommandTypes::QuitCommand);

    // Register the object to the state
    AddObject(&exitButton);
}
