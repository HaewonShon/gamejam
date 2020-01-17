/******************************************************************************/
/*!
This level demonstrates how to create emitters.
There are few samples for electricity, snow, explosion, fire emitters 
so you can get reference from those.
There are several helper functions and attirbutes to deal with from emitter class
so go over and get used to it before actually you play with it.

Controls:
1:		Activate/Inactivate electricity emitter
2:		Activate/Inactivate explosion emitter
3:		Activate/Inactivate fire emitter
4:		Activate/Inactivate snow emitter
5:		Change some of emitters' starting point
C:		Go to next level
*/
/******************************************************************************/
#include "CommonLevel.h"
#include "DemoControlEmitters.h"
#include "Color.h"

void Level3::Initialize()
{
    // Set current state
    State::sCurrentState = this;

	m_backgroundColor = Color::BLACK;

	// Set Camera
	camera.position.Set(0, 0, 0);

	// Set main font
	mainFont = TTF_OpenFont("font/JaykopDot.ttf", 48);

	electricity.SetName("electricity");
	electricity.transform.position.Set(0.f, 0.f, 0.f);
	electricity.transform.SetScale(16, 16);
	// Set the life of emitter
	electricity.emitter.life = 1.f;
	// Set the image of particle
	electricity.emitter.LoadImage("texture/lightening.png", m_renderer);
	// Set the colors of center and boundary
	b2Vec3 electricity_start( 1.f, 1.f, 1.f ), electricity_end( 0, 0, 1.f );
	electricity.emitter.SetColors(electricity_start, electricity_end);
	electricity.emitter.rotationSpeed = 90.f;
	// Generate the particles
	electricity.emitter.GenerateParticles(500, &electricity.transform);

    explosion.SetName("explosion");
    explosion.transform.position.Set(-250.f, 0.f, 0.f);
    explosion.transform.SetScale(16, 16);
    // Different type of emitter
    explosion.emitter.type = Emitter::PARTICLE_EXPLOSION;
    explosion.emitter.life = .5f;
    explosion.emitter.LoadImage("texture/particle.png", m_renderer);
    b2Vec3 explosion_start(1.f, 1.f, 1.f), explosion_end(1.f, 0, 0);
    explosion.emitter.SetColors(explosion_start, explosion_end);
    // Set the range of velocity (min - max) 
    b2Vec2 explosion_xVel(-150.f, 150.f), explosion_yVel(-150.f, 150.f);
    explosion.emitter.SetVelocity(explosion_xVel, explosion_yVel);
    explosion.emitter.GenerateParticles(500, &explosion.transform);





	fire.SetName("fire");
	fire.transform.position.Set(250.f, 0.f, 0.f);
	fire.transform.SetScale(32, 32);
	fire.emitter.life = 2.f;
	fire.emitter.LoadImage("texture/fire.png", m_renderer);
	// *The original color of fire particle is yellowy
	b2Vec3 fire_start(1.f, 1.f, 1.f), fire_end(1.f, 0, 0);
	fire.emitter.SetColors(fire_start, fire_end);
	// Set the range of direction of emitter
	// *If you set the degree 0,
	// them particles would move totally depends on velocity
	fire.emitter.SetDegree(0);
	// Set the range of velocity (min - max) 
	b2Vec2 fire_xVel(-15.f, 15.f), fire_yVel(-10.f, 150.f);
	fire.emitter.SetVelocity(fire_xVel, fire_yVel);
	fire.emitter.GenerateParticles(1000, &fire.transform);

	snow.SetName("snow");
	snow.transform.position.Set(0.f, 400.f, 0.f);
	snow.transform.SetScale(8, 8);
	// Different type of emitter
	snow.emitter.type = Emitter::PARTICLE_SNOW;
	snow.emitter.life = 5.f;
	// Set the range of respwan position
	snow.emitter.SetStartingRange(500.f, 100.f);
	snow.emitter.LoadImage("texture/snow.png", m_renderer);
	b2Vec3 snow_color(1.f, 1.f, 1.f);
	snow.emitter.SetColors(snow_color, snow_color);
	b2Vec2 snow_xVel(-15.f, 15.f), snow_yVel(75.f, 150.f);
	snow.emitter.SetVelocity(snow_xVel, snow_yVel);
	snow.emitter.rotationSpeed = 50.f;
	snow.emitter.SetDegree(270);
	snow.emitter.GenerateParticles(1000, &snow.transform);

	AddObject(&electricity);
	AddObject(&fire);
	AddObject(&explosion);
	AddObject(&snow);

    // Add 'DemoControlEmitters' component to 'emitterController' Object
    Component* pComp = AddComponentToObject(&emitterController, eComponentTypes::DemoControlEmitters);
    DemoControlEmitters* emitters = dynamic_cast<DemoControlEmitters*>(pComp);
    // Set 'DemoControlEmitters' component's member variables
    emitters->electricity       = &electricity;
    emitters->explosion         = &explosion;
    emitters->snow              = &snow;
    emitters->fire              = &fire;
    // Register object containing component to the state
    AddObject(&emitterController);

	SetIntroTexts();
    InitializeObjects();
}

void Level3::Update(float dt)
{
    UpdateObjects(dt);
	// Move to level1 by pressing 'N' key
	if (m_input->IsTriggered(SDL_SCANCODE_N))
		m_game->Change(LV_Level4);

	// Print delta time out
	introTexts[3].text.SetText("Delta time: %.3f", dt);

	// Must be one of the last functions called at the end of State Update
	UpdatePhysics(dt);
	Render(dt);
}

void Level3::Close()
{
	// Wrap up state
	ClearBaseState();
}


void Level3::SetIntroTexts()
{
	introTexts[0].transform.position.Set(-225.f, -275.f, 1.f);
	introTexts[0].transform.SetScale(650.f, 35.f);
	introTexts[0].text.font = mainFont;
	introTexts[0].text.SetText("Activate / Inactivate emitters: Number 1 - 4");

	introTexts[1].transform.position.Set(-225.f, -225.f, 1.f);
	introTexts[1].transform.SetScale(650.f, 35.f);
	introTexts[1].text.font = mainFont;
	introTexts[1].text.SetText("Change attributes of emitters: Number 5");

	introTexts[2].transform.position.Set(-400.f, -175.f, 1.f);
	introTexts[2].transform.SetScale(300.f, 35.f);
	introTexts[2].text.font = mainFont;
	introTexts[2].text.SetText("Move to Main menu: C");

	introTexts[3].transform.position.Set(375.f, -275.f, 1.f);
	introTexts[3].transform.SetScale(300.f, 35.f);
	introTexts[3].text.font = mainFont;

	for (auto& object : introTexts) {
		object.text.isHud = true;
		AddObject(&object);
	}
}