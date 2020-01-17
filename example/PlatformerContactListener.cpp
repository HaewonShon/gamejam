#include "PlatformerContactListener.h"
#include "ContactData.h"
#include "CustomPhysics.h"
#include "engine/Debug.h"

PlatformerContactListener::~PlatformerContactListener()
{
}

/**
 * \brief 
 * Called when two fixtures begin to touch.
 * Based on contact, deal with information for platformer demo
 * 
 * \param contact 
 * Contact information about two shapes (objects) starting collision.
 */
void PlatformerContactListener::BeginContact(b2Contact* contact)

{
    // convert each fixture's user data's data type (void*) to ContactData.
    ContactData* fixtureAUserData = static_cast<ContactData*>(contact->GetFixtureA()->GetUserData());
    ContactData* fixtureBUserData = static_cast<ContactData*>(contact->GetFixtureB()->GetUserData());

    // if fixture A's user data is not ContactData, ignore it.
    if (fixtureAUserData)
    {
        switch (fixtureAUserData->Type)
        {
            // if fixture A is foot sensor
        case eContactTypes::FootSensor:
            // if fixture B is not ghost collision
            if (!contact->GetFixtureB()->IsSensor())
            {
                // increase contact number of fixture A's contact Data
                ++(fixtureAUserData->NumContacts);
            }
            break;
        default: 
            break;
        }
        
    }

    // if fixture B's user data is not ContactData, ignore it.
    if (fixtureBUserData)
    {
        switch (fixtureBUserData->Type)
        {
            // if fixture B is foot sensor
        case eContactTypes::FootSensor:
            // if fixture A is not ghost collision
            if (!contact->GetFixtureA()->IsSensor())
            {
                // increase contact number of fixture B's contact Data
                ++(fixtureBUserData->NumContacts);
            }
            break;
        default:
            break;
        }
    }
    
}

/**
* \brief
* Called when two fixtures cease to touch.
* Based on contact, deal with information for platformer demo
*
* \param contact
 * Contact information about two shapes (objects) finishing collision.
*/
void PlatformerContactListener::EndContact(b2Contact* contact)
{
    // convert each fixture's user data's data type (void*) to ContactData.
    ContactData* fixtureAUserData = static_cast<ContactData*>(contact->GetFixtureA()->GetUserData());
    ContactData* fixtureBUserData = static_cast<ContactData*>(contact->GetFixtureB()->GetUserData());


    // if fixture A's user data is not ContactData, ignore it.
    if (fixtureAUserData)
    {
        switch (fixtureAUserData->Type)
        {
            // if fixture A is foot sensor
        case eContactTypes::FootSensor:
            // if fixture B is not ghost collision
            if (!contact->GetFixtureB()->IsSensor())
            {
                // decrease contact number of fixture A's contact Data
                --(fixtureAUserData->NumContacts);
            }
            break;
        default:
            break;
        }

    }

    // if fixture B's user data is not ContactData, ignore it.
    if (fixtureBUserData)
    {
        switch (fixtureBUserData->Type)
        {
            // if fixture B is foot sensor
        case eContactTypes::FootSensor:
            // if fixture A is not ghost collision
            if (!contact->GetFixtureA()->IsSensor())
            {
                // decrease contact number of fixture B's contact Data
                --(fixtureBUserData->NumContacts);
            }
            break;
        default:
            break;
        }
    }
}