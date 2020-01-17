#include "DemoEnemySpawner.h"
#include "DemoAsteroid.h"
#include "MathUtils.h"
#include "engine/State.h"
#include "PlatformerContactListener.h"
#include "CustomBaseObject.h"
#include "DemoChasePlayer.h"

DemoEnemySpawner::DemoEnemySpawner():
    Component(eComponentTypes::DemoEnemySpawner),
    mMaxInitialAsteroid(4),
    mTotalScores(0),
    mChaseEnemySpeed(15.f),
    mChaseEnemySpawnCount(5.f),
    mTimer(0)
{
}

DemoEnemySpawner::~DemoEnemySpawner()
{
}

void DemoEnemySpawner::Initialize()
{
    mMaxInitialAsteroid = 4;
    mTotalAsteroid = 4;
    for (int i = 0; i < mMaxInitialAsteroid; ++i)
    {
        spawnAsteroid();
    }

    mScoreObject = dynamic_cast<CustomBaseObject*>(State::sCurrentState->GetObject("Score"));
}

void DemoEnemySpawner::Update(float dt)
{
    if (mTotalAsteroid <= 0)
    {
        mMaxInitialAsteroid += 1;
        mTotalAsteroid = mMaxInitialAsteroid;
        for (int i = 0; i < mMaxInitialAsteroid; ++i)
        {
            spawnAsteroid();
     
        }
    }

    mTimer += dt;
    if (mTimer >= mChaseEnemySpawnCount)
    {
        mTimer = 0;
        spawnChaseEnemy();

    }

    mScoreObject->text.SetText(std::to_string(mTotalScores).c_str());
}

void DemoEnemySpawner::spawnAsteroid()
{
    DemoAsteroid* newAsteroid = DemoAsteroid::CreateAsteroid(getRandomPositionWithinScreen(), {200, 200}, 3, 10.f, 25);
    newAsteroid->mSpawner   = this;
}

void DemoEnemySpawner::spawnChaseEnemy()
{
    b2Vec2 position = getRandomPositionWithinScreen();
    CustomBaseObject* newEnemy = new CustomBaseObject;

    newEnemy->SetName("Wasp");
    newEnemy->transform.position.Set(position.x, position.y, 0);
    newEnemy->transform.rotation = static_cast<float>(MathUtils::GetRandomInt(0, 360));
    // Set the scale of the object
    newEnemy->transform.SetScale(50, 50);
    // Connet the address of transform so sprite can use it implicitly
    newEnemy->sprite.LoadImage("texture/wasp.png", State::m_renderer);
    // Set toggle true so animation activates 
    newEnemy->sprite.activeAnimation = true;
    // Set the number of frames to update
    newEnemy->sprite.SetFrame(2);
    // Set the speed of frame updating
    newEnemy->sprite.SetSpeed(12.f);

    // particle 
    newEnemy->emitter.type = Emitter::PARTICLE_EXPLOSION;
    newEnemy->emitter.life = .5f;
    newEnemy->emitter.LoadImage("texture/fire.png", State::m_renderer);
    b2Vec3 explosion_start(1.f, 1.f, 1.f), explosion_end(1.f, 0, 0);
    newEnemy->emitter.SetColors(explosion_start, explosion_end);
    // Set the range of velocity (min - max) 
    b2Vec2 explosion_xVel(-150.f, 150.f), explosion_yVel(-150.f, 150.f);
    newEnemy->emitter.SetVelocity(explosion_xVel, explosion_yVel);
    newEnemy->emitter.GenerateParticles(500, &newEnemy->transform);
    newEnemy->emitter.SetActive(false);

    // Physics
    newEnemy->customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &newEnemy->transform);


    // Add component to object
    State::sCurrentState->AddComponentToObject(newEnemy, eComponentTypes::DemoWrapPosition);
    DemoChasePlayer* chase = dynamic_cast<DemoChasePlayer*>(
        State::sCurrentState->AddComponentToObject(newEnemy, eComponentTypes::DemoChasePlayer));
    chase->mSpeed = mChaseEnemySpeed;
    State::sCurrentState->AddDynamicObjectAndInitialize(newEnemy);
    State::sCurrentState->AddCustomPhysicsComponent(newEnemy);


    float rotationRadian = MathUtils::DegreeToRadian(newEnemy->transform.rotation) + 180;
    b2Vec2 direction(cos(rotationRadian), sin(rotationRadian));
    newEnemy->customPhysics.SetVelocity(direction.x * mChaseEnemySpeed, direction.y * mChaseEnemySpeed);
    newEnemy->customPhysics.ActiveGhostCollision(false);



}

b2Vec2 DemoEnemySpawner::getRandomPositionWithinScreen()
{
    float screenHalfWidth   = State::sCurrentState->m_width * 0.5f;
    float screenHalfHeight  = State::sCurrentState->m_height * 0.5f;
    b2Vec2 randomPosition;
    randomPosition.x = MathUtils::GetRandomFloat(-screenHalfWidth, screenHalfWidth);
    randomPosition.y = MathUtils::GetRandomFloat(-screenHalfHeight, screenHalfHeight);
    return randomPosition;
}
