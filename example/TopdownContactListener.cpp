#include "TopdownContactListener.h"
#include "ContactData.h"
#include "CustomPhysics.h"

TopdownContactListener::~TopdownContactListener()
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
void TopdownContactListener::BeginContact(b2Contact* contact)
{
    // convert each fixture's user data's data type (void*) to ContactData.
    ContactData* fixtureAUserData = static_cast<ContactData*>(contact->GetFixtureA()->GetUserData());
    ContactData* fixtureBUserData = static_cast<ContactData*>(contact->GetFixtureB()->GetUserData());

    // if contact object does not have user date, return
    if (!fixtureAUserData || !fixtureBUserData)
        return;

    // fixture A's user data type
    switch (fixtureAUserData->Type)
    {
    case eContactTypes::Bullet:
        if (fixtureBUserData->Type == eContactTypes::Asteroid ||
            fixtureBUserData->Type == eContactTypes::Enemy)
        {
            // if A's type is Bullet & B's type is Asteroid or Enemy,
            // increase both fixtures' contact data
            ++(fixtureAUserData->NumContacts);
            ++(fixtureBUserData->NumContacts);
        }
        break;
    case eContactTypes::Asteroid:
        if (fixtureBUserData->Type == eContactTypes::Bullet)
        {
            // if A's type is Asteroid & B's type is Bullet,
            // increase both fixtures' contact data
            ++(fixtureAUserData->NumContacts);
            ++(fixtureBUserData->NumContacts);
        }
        break;
    case eContactTypes::Player:
        if (fixtureBUserData->Type == eContactTypes::Asteroid ||
            fixtureBUserData->Type == eContactTypes::Enemy)
        {
            // if A's type is Player & B's type is Asteroid or Enemy,
            // increase Player's contact data
            ++(fixtureAUserData->NumContacts);
        }
        break;
    default:
        break;
    }

    // fixture B's user data type
    switch (fixtureBUserData->Type)
    {
    case eContactTypes::Bullet:
        if (fixtureAUserData->Type == eContactTypes::Asteroid ||
            fixtureAUserData->Type == eContactTypes::Enemy)
        {
            // if B's type is Bullet & A's type is Asteroid or Enemy,
            // increase both fixtures' contact data
            ++(fixtureAUserData->NumContacts);
            ++(fixtureBUserData->NumContacts);
        }
        break;
    case eContactTypes::Asteroid:
        if (fixtureAUserData->Type == eContactTypes::Bullet)
        {
            // if B's type is Asteroid & A's type is Bullet,
            // increase both fixtures' contact data
            ++(fixtureAUserData->NumContacts);
            ++(fixtureBUserData->NumContacts);
        }
        break;
    case eContactTypes::Player:
        if (fixtureAUserData->Type == eContactTypes::Asteroid ||
            fixtureAUserData->Type == eContactTypes::Enemy)
        {
            // if B's type is Player & A's type is Asteroid or Enemy,
            // increase Player's contact data
            ++(fixtureBUserData->NumContacts);
        }
        break;
    default:
        break;
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
void TopdownContactListener::EndContact(b2Contact* /*contact*/)
{
}