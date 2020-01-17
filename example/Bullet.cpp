#include "Bullet.h"
#include "Game.h"
#include "engine/Object.h"
#include "ContactData.h"

char GetRandomCharacter();
Bullet::Bullet()
{
    // Assign a randomized color to be applied to this bullet at birth
    unsigned char randomRed = GetRandomCharacter();
    unsigned char randomGreen = GetRandomCharacter();
    unsigned char randomBlue = GetRandomCharacter();
    birthColor = { randomRed, randomGreen, randomBlue, 255 };
}

bool Bullet::IsOffscreen() const
{
    float halfWidth = Game::SCREEN_WIDTH / 2.f;
    float halfHeight = Game::SCREEN_HEIGHT / 2.f;

    bool isOnscreen = transform.position.x > -halfWidth &&
        transform.position.x < halfWidth &&
        transform.position.y > -halfHeight &&
        transform.position.y < halfHeight;
    return !isOnscreen;
}

void Bullet::Update(float /*dt*/)
{
    if (!IsOffscreen()) return;

    // Delete this object from current state
    this->isDead = true;
}

char GetRandomCharacter()
{
    char randomCharacter = static_cast<char>((rand() % static_cast<int>(UCHAR_MAX + 1)));
    return randomCharacter;
}

CustomBullet::CustomBullet():
    mLifeCount(0),
    mTimer(0)
{
}


void CustomBullet::Update(float dt)
{
    mTimer += dt;
    if ((mTimer >= mLifeCount) ||
        // collide with enemy
        (customPhysics.mContactData->NumContacts))
    {
        printf("[Bullet Die]\n");
        mTimer = 0;
        this->isDead = true;
        customPhysics.ActivePhysics(false);
    }
}

void CustomBullet::Initialize()
{
    Object::Initialize();
}
