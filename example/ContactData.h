/******************************************************************************/
/*!
\file   ContactData.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

Contact Data type and structure for Custom Contact List
*/
/******************************************************************************/
#pragma once
class CustomBaseObject;
enum class eContactTypes
{
    FootSensor,
    Enemy,
    Bullet,
    Asteroid,
    Player
};

struct ContactData
{
    eContactTypes               Type;
    CustomBaseObject*           Owner;
    int                         NumContacts;
};