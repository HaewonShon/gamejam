#include "CustomBaseObject.h"
#include "Box2D\Dynamics\b2World.h"
#include "engine/State.h"

CustomBaseObject::CustomBaseObject()
	:Object()	// Call base class' constructor
{}

CustomBaseObject::~CustomBaseObject()
{}

void CustomBaseObject::Shutdown()
{
    State::sCurrentState->RemoveCustomPhysicsComponent(&customPhysics);
    //RemoveCustomPhysicsComp(State::sCurrentState->GetCustomPhysicsWorld());
    Object::Shutdown();
}

/**
 * \brief 
 * Remove custom physics component
 * 
 * \param world 
 * Address of custom box2d world
 */
void CustomBaseObject::RemoveCustomPhysicsComp(b2World* world)
{
	// Check either if physics is allocated before
	if (customPhysics.m_body) {
		// Deregister rigid body from the physics world
		world->DestroyBody(customPhysics.m_body);
		// Set pointer to null
		customPhysics.m_body = nullptr;
	}
}

/**
* \brief
* Remove custom physics component
* *New and polished way
*/
void CustomBaseObject::RemoveCustomPhysicsComponent()
{
	auto customPhysicsList = customPhysics.m_pList;
	b2World* customPhysicsWorld = customPhysics.m_world;
	for (auto cPhysics = customPhysicsList->begin();
		cPhysics != customPhysicsList->end(); ++cPhysics)
	{
		if (customPhysics.m_body == (*cPhysics)->m_body)
		{
			// Erase component from the list
			customPhysicsList->erase(cPhysics);
			// Deregister rigid body from the physics world
			customPhysicsWorld->DestroyBody(customPhysics.m_body);
			// Set pointer to null
			customPhysics.m_body = nullptr;
			customPhysics.m_allocatedBody = false;
			break;
		}
	}
}

void CustomBaseObject::Initialize()
{
    Object::Initialize();
}

