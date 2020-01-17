#include "DemoControlEmitters.h"
#include "engine/Object.h"
#include "engine/State.h"

DemoControlEmitters::DemoControlEmitters():
    Component(eComponentTypes::DemoControlEmitters)
{
}

DemoControlEmitters::~DemoControlEmitters()
{

}

void DemoControlEmitters::Initialize()
{
    electricitytoggle = snowToggle = fireToggle = changeToggle = false;

    electricity->emitter.SetActive(true);
    explosion->emitter.SetActive(true);
    snow->emitter.SetActive(true);
    fire->emitter.SetActive(true);
    radian = 0.f;
}

void DemoControlEmitters::Update(float dt)
{
    if (State::m_input->IsTriggered(SDL_SCANCODE_1))
        explosion->emitter.SetActive(true);

    if (State::m_input->IsTriggered(SDL_SCANCODE_2)) {
        electricity->emitter.SetActive(electricitytoggle);
        electricitytoggle = !electricitytoggle;
    }

    if (State::m_input->IsTriggered(SDL_SCANCODE_3)) {
        fire->emitter.SetActive(fireToggle);
        fireToggle = !fireToggle;
    }

    if (State::m_input->IsTriggered(SDL_SCANCODE_4)) {
        snow->emitter.SetActive(snowToggle);
        snowToggle = !snowToggle;
    }

    if (State::m_input->IsTriggered(SDL_SCANCODE_5)) {

        // Normal way
        if (changeToggle) {
            // Reset the range of starting position 
            electricity->emitter.SetStartingRange(0.f, 0.f);
            explosion->emitter.SetStartingRange(0.f, 0.f);
            // Set snow's starting position top
            snow->transform.position.Set(0.f, 400.f, 0.f);
            // Let snow fall to bottom
            snow->emitter.SetDegree(270);
            // Set new velocity for fire particle
            b2Vec2 fire_xVel(-15.f, 15.f), fire_yVel(-10.f, 150.f);
            fire->emitter.SetVelocity(fire_xVel, fire_yVel);
        }

        // Anothe way
        else {
            // Set the range of starting position a little wide
            electricity->emitter.SetStartingRange(50.f, 0.01f);
            explosion->emitter.SetStartingRange(50.f, 50.f);
            // Set snow's starting position bottom
            snow->transform.position.Set(0.f, -400.f, 0.f);
            // Let snow blow to top
            snow->emitter.SetDegree(90);
        }

        changeToggle = !changeToggle;
    }

    if (changeToggle) {
        // Stack radian
        radian += dt;
        b2Vec2 newVelx, newVely;
        // Set the minimum value of range
        newVelx.x = newVely.x = 0;
        // Set the maximum value of range
        newVelx.y = cos(radian) * 350.f;
        newVely.y = sin(radian) * 350.f;

        fire->emitter.SetVelocity(newVelx, newVely);
    }
}
