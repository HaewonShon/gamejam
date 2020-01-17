#include "Turret.h"
#include "engine/State.h"
#include "Bullet.h"

float GetNormalizedValueWrapped(float value, float min, float max);
const float BULLET_VELOCITY = 150.f;

Turret::Turret() :
    bullet_diameter(30.f)
{
    shootSfx.SetName("Beep");
    shootSfx.sound.LoadSound("sound/beep.wav");
}

Turret::~Turret()
{
    shootSfx.sound.Free();
}

void Turret::OnShoot()
{
    shootSfx.sound.Play();
}

void Turret::IncreaseRotation(int deltaRotationDegrees)
{
    transform.rotation += deltaRotationDegrees;

    // Keep rotation in range [0, 360)
    const float RANGE_MIN = 0.f;
    const float RANGE_MAX = 360.f;
    transform.rotation = GetNormalizedValueWrapped(transform.rotation, RANGE_MIN, RANGE_MAX);

    //std::cout << "Rotation is currently: " << transform.rotation << std::endl;
}

b2Vec2 Turret::GetTipLocation()
{
    b2Vec2 tipLocation;
    b2Vec2 directionVector = GetNormalizedDirectionVector();

    float turretWidth = (transform.GetScale().x / 2.f);
    tipLocation.x = turretWidth * directionVector.x;
    tipLocation.y = turretWidth * directionVector.y;

    return tipLocation;
}

b2Vec2 Turret::GetVelocityVector() const
{
    b2Vec2 velocityVector;
    b2Vec2 directionVector = GetNormalizedDirectionVector();

    velocityVector.x = BULLET_VELOCITY * directionVector.x;
    velocityVector.y = BULLET_VELOCITY * directionVector.y;

    return velocityVector;
}

void Turret::Update(float /*dt*/)
{
    

    // Shoot
    if (!State::m_input->IsTriggered(SDL_SCANCODE_SPACE))
        return;

    OnShoot();

    // Create bullet at the tip of the turret
    b2Vec2 tipLocation = GetTipLocation();
    Bullet *newBullet = new Bullet;

    newBullet->transform.position.Set(tipLocation.x, tipLocation.y, 0.f);
    newBullet->transform.SetScale(bullet_diameter, bullet_diameter);

    newBullet->sprite.color = newBullet->GetBirthColor();
    newBullet->sprite.LoadImage("texture/circle.png", State::m_renderer);

    newBullet->physics.GenerateBody(State::sCurrentState->GetPhysicsWorld(), &newBullet->transform);

    State::sCurrentState->AddDynamicObject(newBullet);

    // Have bullet move in the direction the turret is facing
    b2Vec2 velocityVector = GetVelocityVector();
    newBullet->physics.SetVelocity(velocityVector.x, velocityVector.y);

}

b2Vec2 Turret::GetNormalizedDirectionVector() const
{
    b2Vec2 directionVector;

    float rotationRadians = transform.rotation * ((float)M_PI / 180.f);
    directionVector.x = cos(rotationRadians);

    directionVector.y = sin(rotationRadians);

    return directionVector;
}
float GetNormalizedValueWrapped(float value, float min, float max)
{
    if (value >= max)
    {
        value -= max;
    }
    else if (value < min)
    {
        value += max;
    }

    return value;
}
