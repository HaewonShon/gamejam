#include "DemoLv1Controller.h"
#include "engine/State.h"
#include "engine/Object.h"
#include <iostream>
#include "Box2D/Box2D.h"

DemoLv1Controller::DemoLv1Controller():
    Component(eComponentTypes::DemoLv1Controller)
{
}

DemoLv1Controller::~DemoLv1Controller()
{

}

void DemoLv1Controller::Initialize()
{
    toggle = true;
}

void DemoLv1Controller::Update(float dt)
{
    // Stop all the rigidbodies' movement
    if (State::m_input->IsTriggered((SDL_SCANCODE_SPACE))) {

        // Refresh the color of box
        mOwner->sprite.color = { 255, 255, 255, 255 };

        for (auto physics : *(State::m_physics_vector))
            physics->SetVelocity(0.f, 0.f);
    }

    // Set box's random direction
    else if (State::m_input->IsTriggered((SDL_SCANCODE_RETURN))) {
        // Refresh the color of box
        mOwner->sprite.color = { 255, 255, 255, 255 };

        for (auto physics : *(State::m_physics_vector))
            physics->SetVelocity(GetRandomFloat(), GetRandomFloat());
    }

    // Check if the box object has rigid body first
    if (mOwner->physics.HasBody()) {

        // Control box with arrow keys
        if (State::m_input->IsTriggered((SDL_SCANCODE_LEFT)))
            mOwner->physics.AddForce(-10.f, 0.f);

        else if (State::m_input->IsTriggered((SDL_SCANCODE_RIGHT)))
            mOwner->physics.AddForce(10.f, 0.f);

        else if (State::m_input->IsTriggered((SDL_SCANCODE_UP)))
            mOwner->physics.AddForce(0.f, 10.f);

        else if (State::m_input->IsTriggered((SDL_SCANCODE_DOWN)))
            mOwner->physics.AddForce(0.f, -10.f);

        // Rotate by pressing Q and E
        if (State::m_input->IsPressed(SDL_SCANCODE_Q))
            mOwner->transform.rotation += dt * 100.f;

        else if (State::m_input->IsPressed(SDL_SCANCODE_E))
            mOwner->transform.rotation -= dt * 100.f;

        // Enable / disable the collision
        else if (State::m_input->IsTriggered(SDL_SCANCODE_P)) {
            mOwner->physics.ActiveGhostCollision(toggle);
            toggle = !toggle;
        }

        // Enforce to set a position and rotation
        else if (State::m_input->IsTriggered(SDL_SCANCODE_0))
            mOwner->transform.position.Set(0.f, 0.f, 0.f);
    }
    CollisionResponse();
}

float DemoLv1Controller::GetRandomFloat()
{
    int intValue = rand() % 10; 
    float offset = 5.f;
    if (rand() % 2) 
        intValue *= -1;

    return intValue * offset;
}

void DemoLv1Controller::CollisionResponse()
{// Check collision status of box(box)

	// Check if the box object has rigid body first
    if (!mOwner->physics.HasBody()) return;

    // If the box got collided with arbitrary object...
    if (mOwner->physics.IsColliding())
    {
        // If the object is RED Ball->..
        if (mOwner->physics.IsCollidingWith(redBall)) {
            std::cout << "Collided with red ball, ";
            mOwner->sprite.color = redBall->sprite.color;
            std::cout << "Did red ball detect the box?: " <<
                redBall->physics.IsCollidingWith(mOwner) << "\n";
        }
        // If the object is BLUE Ball->..
        else if (mOwner->physics.IsCollidingWith(blueBall)) {
            std::cout << "Collided with blue ball, ";
            mOwner->sprite.color = blueBall->sprite.color;
            std::cout << "Did blue ball detect the box?: " <<
                blueBall->physics.IsCollidingWith(mOwner) << "\n";
        }
        // If the object is BLACK Ball->..
        else if (mOwner->physics.IsCollidingWith(blackBall)) {
            std::cout << "Collided with black ball, ";
            mOwner->sprite.color = blackBall->sprite.color;
            std::cout << "Did black ball detect the box?: " <<
                blackBall->physics.IsCollidingWith(mOwner) << "\n";
        }
        // That must be the one of walls
        else
            mOwner->sprite.color = { 136, 136, 136, 255 };
    }

    static const char* name = "None";
    // You can get information from the "other" object colliding with "this" object
    Object* with = mOwner->physics.GetCollidingWith();
    if (with) {
        printf("Colliding...\n");
        name = with->GetName().c_str();
        collisionText->text.SetText("Last collided with: %s", name);
    }
}
