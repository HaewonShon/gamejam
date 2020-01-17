#include "DemoLv4Controller.h"
#include "engine/State.h"
#include "engine/Object.h"
#include "CustomBaseObject.h"
#include "CustomPhysics.h"
#include <iostream>

DemoLv4Controller::DemoLv4Controller():
    Component(eComponentTypes::DemoLv4Controller),
    physicsVector(nullptr),
    customOwner(nullptr)
{
}

DemoLv4Controller::~DemoLv4Controller()
{
}

void DemoLv4Controller::Initialize()
{
    customOwner = dynamic_cast<CustomBaseObject*>(mOwner);
}

void DemoLv4Controller::Update(float dt)
{
    if (!customOwner ||
        !physicsVector)
        return;

    // Stop all the rigidbodies' movement
    if (State::m_input->IsTriggered((SDL_SCANCODE_SPACE))) {

        // Refresh the color of box
        mOwner->sprite.color = { 255, 255, 255, 255 };

        for (auto physics : *physicsVector)
            physics->SetVelocity(0.f, 0.f);
    }

    // Set box's random direction
    else if (State::m_input->IsTriggered((SDL_SCANCODE_RETURN))) {
        // Refresh the color of box
        mOwner->sprite.color = { 255, 255, 255, 255 };

        for (auto physics : *physicsVector)
            physics->SetVelocity(GetRandomFloat(), GetRandomFloat());
    }
    
    // Check if the box object has rigid body first
    if (customOwner->customPhysics.HasBody()) {

        // Control box with arrow keys
        if (State::m_input->IsTriggered((SDL_SCANCODE_LEFT)))
            customOwner->customPhysics.AddForce(-10.f, 0.f);

        else if (State::m_input->IsTriggered((SDL_SCANCODE_RIGHT)))
            customOwner->customPhysics.AddForce(10.f, 0.f);

        else if (State::m_input->IsTriggered((SDL_SCANCODE_UP)))
            customOwner->customPhysics.AddForce(0.f, 10.f);

        else if (State::m_input->IsTriggered((SDL_SCANCODE_DOWN)))
            customOwner->customPhysics.AddForce(0.f, -10.f);

        // Rotate by pressing Q and E
        if (State::m_input->IsPressed(SDL_SCANCODE_Q))
            customOwner->transform.rotation += dt * 100.f;

        else if (State::m_input->IsPressed(SDL_SCANCODE_E))
            customOwner->transform.rotation -= dt * 100.f;

        // Enable / disable the collision
        else if (State::m_input->IsTriggered(SDL_SCANCODE_P)) {
            toggle = !toggle;
            printf("Toggle: %d\n", toggle);
            customOwner->customPhysics.ActiveGhostCollision(toggle);
        }
    }
    CollisionResponse();
}

float DemoLv4Controller::GetRandomFloat()
{
    int intValue = rand() % 20;
    if (rand() % 2)
        intValue *= -1;

    return float(intValue);
}

void DemoLv4Controller::CollisionResponse()
{
    // Check collision status of box(box)

    // Check if the box object has rigid body first
    if (customOwner->customPhysics.HasBody()) {
        // If the box got collided with arbitrary object...
        if (customOwner->customPhysics.IsColliding())
        {
            // If the object is RED ball...
            if (customOwner->customPhysics.IsCollidingWith(redBall))
                customOwner->sprite.color = redBall->sprite.color;

            // If the object is BLUE ball...
            else if (customOwner->customPhysics.IsCollidingWith(blueBall))
                customOwner->sprite.color = blueBall->sprite.color;

            // If the object is BLACK ball...
            else if (customOwner->customPhysics.IsCollidingWith(blackBall))
                customOwner->sprite.color = blackBall->sprite.color;

            // That must be one of walls
            else
                customOwner->sprite.color = { 136, 136, 136, 255 };
        }

        std::cout << customOwner->customPhysics.GetVelocity().Length() << std::endl;

        static const char* name = "None";
        // You can get information from the "other" object colliding with "this" object
        CustomBaseObject* with = customOwner->customPhysics.GetCollidingWith();
        if (with) {
            name = with->GetName().c_str();
            collisionText->text.SetText("Last collided with: %s", name);
        }
    }
}
