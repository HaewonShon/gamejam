/******************************************************************************/
/*!
	*This level contains a simple demo for a top-down game.
	With box2d world(physics system), collision and force,
	you can develope 2d top-down game.

	*Instuctions
	1. Make all objects inside the walls move randomly - Enter
	2. Make all objects inside the walls stop - Space
	3. Control the white box - Arrow keys(up, down, left, right)
	4. Rotate the white box - Q, E
	5. Move to next state - C
*/
/******************************************************************************/

#include "CommonLevel.h"
#include "cstdlib"
#include <iostream>
#include "DemoLv1Controller.h"
#include "Color.h"


void Level1::Initialize()
{
    // Set current state
    State::sCurrentState = this;

    // Set background color
	m_backgroundColor = Color::CORAL_RED;

	// Set Camera
	// You don't need to do this anymore
	// camera.Initialize(int(State::m_width), int(State::m_height));
	// Set position of the camera
	camera.position.Set(0, 0, 0);

	// Set main font
	mainFont = TTF_OpenFont("font/Default.ttf", 48);

	// Set physics world
	b2Vec2 gravity(0.f, 0.f);
	SetPhysicsWorld(gravity);
    State::m_physics_vector = GetPhysicsList();

    Component* pComp = AddComponentToObject(&box, eComponentTypes::DemoLv1Controller);
    DemoLv1Controller* controller = dynamic_cast<DemoLv1Controller*>(pComp);
    controller->blackBall = &redBall;
    controller->blueBall = &blueBall;
    controller->redBall = &redBall;
    controller->collisionText = &introTexts[5];
	// Bodies
	BuildAndRegisterBody(blackBall, "blackBall", 0.f, -50.f, Physics::CIRCLE);
	BuildAndRegisterBody(blueBall, "blueBall", -50.f, 0.f, Physics::CIRCLE);
	BuildAndRegisterBody(redBall, "redBall", 50.f, 0.f, Physics::CIRCLE);
	BuildAndRegisterBody(box, "box", 0.f, 50.f, Physics::BOX);

	// Set bodies' color
	blackBall.sprite.color = Color::BLACK;
	blueBall.sprite.color = Color::BLUE;
	redBall.sprite.color = Color::RED;
	box.sprite.color = Color::WHITE;
	
	// Walls
	BuildAndRegisterWall(top, "Top", 0.f, 256.f, 512.f, 32.f);
	BuildAndRegisterWall(bottom, "Bottom", 0.f, -256.f, 512.f, 32.f);
	BuildAndRegisterWall(left, "Left", -256.f, 0.f, 32.f, 512.f);
	BuildAndRegisterWall(right, "Right", 256.f, 0.f, 32.f, 512.f);

	SetIntroTexts();
    InitializeObjects();
}

void Level1::Update(float dt)
{
    UpdateObjects(dt);

	/******************* State ******************/

	// Move to main menu by pressing 'N' key
	if (m_input->IsTriggered(SDL_SCANCODE_N))
		m_game->Change(LV_Level2);


	// Must be one of the last functions called at the end of State Update
	UpdatePhysics(dt);
	Render(dt);
}

void Level1::Close()
{
	// Wrap up state
	ClearBaseState();
}




Object& Level1::BuildAndRegisterWall(Object &wall, const char *name, float positionX, float positionY, float scaleX, float scaleY)
{
	const float POSITION_Z = 0.f;

	wall.SetName(name);

	wall.transform.position.Set(positionX, positionY, POSITION_Z);
	wall.transform.SetScale(scaleX, scaleY);

	wall.sprite.color = Color::GREY;
	wall.sprite.LoadImage("texture/rect.png", m_renderer);

	wall.physics.bodyType = Physics::STATIC;
	wall.physics.GenerateBody(GetPhysicsWorld(), &wall.transform);

	AddObject(&wall);

	return wall;
}

Object& Level1::BuildAndRegisterBody(Object &body, const char *name, float positionX, float positionY, Physics::BodyShape shape)
{
	const float SCALE_X = 64.f;
	const float SCALE_Y = 64.f;
	const float POSITION_Z = 0.f;
	const float RADIUS = 32.f;
	const float RESTITUTION = 1.f;

	body.SetName(name);

	body.transform.position.Set(positionX, positionY, POSITION_Z);
	body.transform.SetScale(SCALE_X, SCALE_Y);
	body.transform.rotation = float(rand() % 360);

	body.sprite.color = Color::BLACK;

	if (shape == Physics::CIRCLE)
		body.sprite.LoadImage("texture/circle.png", m_renderer);
	else
		body.sprite.LoadImage("texture/rect.png", m_renderer);

	body.physics.bodyType = Physics::DYNAMIC;
	body.physics.bodyShape = shape;
	body.physics.radius = RADIUS;
	body.physics.GenerateBody(GetPhysicsWorld(), &body.transform);
	body.physics.SetRestitution(RESTITUTION);

	AddObject(&body);

	// Add to moving object list
	m_dynamicList.push_back(&body);

	return body;
}

void Level1::SetIntroTexts()
{
	introTexts[0].transform.position.Set(-325.f, 275.f, 1.f);
	introTexts[0].transform.SetScale(450.f, 50.f);
	introTexts[0].text.font = mainFont;
	introTexts[0].text.SetText("Add force to Box: Arrow keys");

	introTexts[1].transform.position.Set(-325.f, 225.f, 1.f);
	introTexts[1].transform.SetScale(450.f, 50.f);
	introTexts[1].text.font = mainFont;
	introTexts[1].text.SetText("Pause / Move all objects: Space / Enter");

	introTexts[2].transform.position.Set(-400.f, 175.f, 1.f);
	introTexts[2].transform.SetScale(300.f, 50.f);
	introTexts[2].text.font = mainFont;
	introTexts[2].text.SetText("Rotate the box: Q, E");

	introTexts[3].transform.position.Set(310.f, 225.f, 1.f);
	introTexts[3].transform.SetScale(475.f, 50.f);
	introTexts[3].text.font = mainFont;
	introTexts[3].text.SetText("Activate Ghost collision: P");

	introTexts[4].transform.position.Set(225.f, 175.f, 1.f);
	introTexts[4].transform.SetScale(300.f, 50.f);
	introTexts[4].text.font = mainFont;
	introTexts[4].text.SetText("Move to Level2: N");

	introTexts[5].transform.position.Set(300.f, 275.f, 1.f);
	introTexts[5].transform.SetScale(450.f, 50.f);
	introTexts[5].text.font = mainFont;

	for (auto& object : introTexts) {
		object.text.isHud = true;
		AddObject(&object);
	}
}

