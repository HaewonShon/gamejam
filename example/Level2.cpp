/******************************************************************************/
/*!
This level demonstrates how to create your own BaseObject class by deriving
from the engine's Object class. In addition, it also shows how you can add your
own custom Physics logic to enable you full access to Box2D physics. This is
only necessary if you plan to have more than basic collision and physics in your
game.

Controls:
UP:		Circle jumps up
RIGHT:	Circle propels right
LEFT:	Circle propels left
C:		Go to next level
R:		Restart level
*/
/******************************************************************************/
#include "CommonLevel.h"

void Level2::Initialize()
{
    // Set current state
    State::sCurrentState = this;

	/****** There is no update for custom physics ******/

	// Set background color
	m_backgroundColor.r = 255, m_backgroundColor.g = 64,
		m_backgroundColor.b = 0;

	// Set Camera
	// You don't need to do this anymore
	//camera.Initialize(int(State::m_width), int(State::m_height));
	// Set position of the camera
	camera.position.Set(0, 0, 0);

	// Set main font
	// Load the font file to use as a main font
	// and set the default size of it
	mainFont = TTF_OpenFont("font/Default.ttf", 48);

	// *We are not going to use built-in physics world
	m_useBuiltInPhysics = false;

	// Set custom physics world
	b2Vec2 gravity(0.f, -9.8f);
	SetCustomPhysicsWorld(gravity);

	// Set the object's unique name
	ball.SetName("Player");
	// Set the position of the object
	ball.transform.position.Set(0.0f, 100.0f, 0.0f);
	// Set the scale of the object
	ball.transform.SetScale(64, 64);
	// Set the colors r,g,b,a (0~255)
	ball.sprite.color = SDL_Color{ 0, 255, 255, 255 };
	// Connet the address of transform so sprite can use it implicitly
	ball.sprite.LoadImage("texture/circle.png", m_renderer);
	ball.sprite.color.r = ball.sprite.color.g
		= ball.sprite.color.b = 0;

	//* Here we predefine some info to create a body
	// Connect transform to the pointer
	ball.customPhysics.pOwnerTransform = &ball.transform;
	// Set body type (either DYNAMIC or STATIC)
	ball.customPhysics.bodyType = CustomPhysics::DYNAMIC;
	// Set body shape
	ball.customPhysics.bodyShape = CustomPhysics::CIRCLE;
	ball.customPhysics.radius = 32;
	// Allocate body passing world
	ball.customPhysics.AllocateBody(GetCustomPhysicsWorld());
	// Set restitution
	ball.customPhysics.SetRestitution(.75f);

	// Set wall
	wall.SetName("Wall");
	wall.transform.position.Set(0.0f, -100.0f, 0.0f);
	wall.transform.SetScale(256, 32);
	wall.sprite.color = SDL_Color{ 0, 255, 255, 255 };
	wall.sprite.LoadImage("texture/rect.png", m_renderer);
	wall.sprite.color.r = wall.sprite.color.g
		= wall.sprite.color.b = 0X88;

	wall.customPhysics.pOwnerTransform = &wall.transform;
	wall.customPhysics.bodyType = CustomPhysics::STATIC;
	wall.customPhysics.AllocateBody(GetCustomPhysicsWorld());

	// Set text
	text.transform.position.Set(0.f, 200.f, 0.f);
	text.transform.SetScale(1000, 64);
	text.text.SetText(m_renderer, "You can control the ball with "
		"arrow keys(up, right, left).", mainFont);

	// Register the object to the state
	// *You have to add custom physics component
	// to custom physics list manually,
	// by using AddCustomPhysicsComponent function.
    AddComponentToObject(&ball, eComponentTypes::DemoLv2Controller);
    AddObject(&ball);
	AddCustomPhysicsComponent(&ball);
	AddObject(&wall);
	AddCustomPhysicsComponent(&wall);
	AddObject(&text);

    InitializeObjects();
}

void Level2::Update(float dt)
{
    UpdateObjects(dt);
	/******************* State ******************/

	// Move to level1 by pressing 'N' key
	if (m_input->IsTriggered(SDL_SCANCODE_N))
		m_game->Change(LV_Level3);

	// Restart current level by pressing 'R' key
	if (m_input->IsTriggered(SDL_SCANCODE_R))
		m_game->Restart();

	//UpdatePhysics(dt);		// We don't use built-in physics components and world
	UpdateCustomPhysics(dt);	// Update custom physics system here
	Render(dt);
}

void Level2::Close()
{
	// Deallocate custom physics world
	RemoveCustomPhysicsWorld();

	// Wrap up state
	ClearBaseState();
}
