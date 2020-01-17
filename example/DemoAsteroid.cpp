#include "DemoAsteroid.h"
#include "DemoEnemySpawner.h"
#include "MathUtils.h"
#include "engine/State.h"
#include "ContactData.h"

DemoAsteroid* DemoAsteroid::CreateAsteroid(b2Vec2 position, b2Vec2 scale, int life, float speed, int score)
{
    DemoAsteroid* newAsteroid = new DemoAsteroid;
    newAsteroid->SetName("Asteroid");
    newAsteroid->transform.position.Set(position.x, position.y, 0);
    newAsteroid->transform.SetScale(scale.x, scale.y);
    newAsteroid->transform.rotation = static_cast<float>(MathUtils::GetRandomInt(0, 360));
    newAsteroid->sprite.LoadImage("texture/Asteroid1.png", State::m_renderer);

    // particle 

    newAsteroid->emitter.type = Emitter::PARTICLE_EXPLOSION;
    newAsteroid->emitter.life = .5f;
    newAsteroid->emitter.LoadImage("texture/fire.png", State::m_renderer);
    b2Vec3 explosion_start(1.f, 1.f, 1.f), explosion_end(1.f, 0, 0);
    newAsteroid->emitter.SetColors(explosion_start, explosion_end);
    // Set the range of velocity (min - max) 
    b2Vec2 explosion_xVel(-150.f, 150.f), explosion_yVel(-150.f, 150.f);
    newAsteroid->emitter.SetVelocity(explosion_xVel, explosion_yVel);
    newAsteroid->emitter.GenerateParticles(500, &newAsteroid->transform);
    newAsteroid->emitter.SetActive(false);

    newAsteroid->customPhysics.GenerateBody(State::sCurrentState->GetCustomPhysicsWorld(), &newAsteroid->transform);

    newAsteroid->mLife = life;
    newAsteroid->mSpeed = speed;
    newAsteroid->mScore = score;

    State::sCurrentState->AddComponentToObject(newAsteroid, eComponentTypes::DemoWrapPosition);
    State::sCurrentState->AddDynamicObjectAndInitialize(newAsteroid);
    State::sCurrentState->AddCustomPhysicsComponent(newAsteroid);


    float rotationRadian = MathUtils::DegreeToRadian(newAsteroid->transform.rotation);
    b2Vec2 direction(cos(rotationRadian), sin(rotationRadian));
    newAsteroid->customPhysics.SetVelocity(direction.x * speed, direction.y * speed);
    newAsteroid->customPhysics.ActiveGhostCollision(false);
    return newAsteroid;
}

DemoAsteroid::DemoAsteroid():
    mLife(0),
    mSpawner(nullptr),
    mSpeed(0),
    mDeathCount(1.f),
    mbIsDead(false),
    mTimer(0)
{

}

void DemoAsteroid::Update(float dt)
{
    // Dead
    if (mbIsDead)
    {
        mTimer += dt;
        if (mTimer >= mDeathCount)
        {
            mTimer = 0;
            --(mSpawner->mTotalAsteroid);
            isDead = true;
            printf("[Asteroid Dead]\n");
        }
        return;
    }

    // collide with bullet
    if (customPhysics.mContactData->NumContacts > 0)
    {
        mSpawner->mTotalScores += mScore;
        --mLife;
        emitter.SetActive(true);
        // split asteroid
        if (mLife > 0)
        {
            customPhysics.mContactData->NumContacts = 0;
            printf("[Create Asteroid]\n");
            b2Vec2 randomPosition;
            b2Vec2 halfScale = transform.GetHalfScale();
            randomPosition.x = MathUtils::GetRandomFloat(transform.position.x - halfScale.x, transform.position.x + halfScale.x);
            randomPosition.y = MathUtils::GetRandomFloat(transform.position.y - halfScale.y, transform.position.y + halfScale.y);
            DemoAsteroid* newAsteroid = DemoAsteroid::CreateAsteroid(randomPosition, halfScale, mLife, mSpeed * 1.5f, mScore * 2);
            newAsteroid->mSpawner = mSpawner;

            transform.SetScale(halfScale.x, halfScale.y);
            customPhysics.SetBoxScale(halfScale.x, halfScale.y);
            randomPosition.x = MathUtils::GetRandomFloat(transform.position.x - halfScale.x, transform.position.x + halfScale.x);
            randomPosition.y = MathUtils::GetRandomFloat(transform.position.y - halfScale.y, transform.position.y + halfScale.y);

            customPhysics.SetPosition(randomPosition.x, randomPosition.y);
            ++(mSpawner->mTotalAsteroid);
        }
        // die
        else
        {
            mbIsDead = true;
            customPhysics.ActivePhysics(false);
            sprite.color.a = 0;
        }
    }
}

void DemoAsteroid::Initialize()
{
    CustomBaseObject::Initialize();

    // Set contact data
    ContactData* userData = new ContactData;
    userData->Type = eContactTypes::Asteroid;
    userData->NumContacts = 0;
    userData->Owner = this;
    customPhysics.SetContactUserData(userData);

}
