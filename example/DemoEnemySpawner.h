/******************************************************************************/
/*!
\file   DemoEnemySpawner.h
\author Hun Yang
\par    email: hun.yang8456@gmail.com
\par    GAM150 demo
\date   2019/04/28

Spawn 'DemoAsteroid' derived object and chase enemy holding 'DemoChasePlayer' component
*/
/******************************************************************************/
#pragma once
#include "Component.h"
#include <Box2D/Common/b2Math.h>

class CustomBaseObject;
class DemoEnemySpawner : public Component
{
public:
    DemoEnemySpawner();
    ~DemoEnemySpawner();
    virtual void Initialize()       override;
    virtual void Update(float dt)   override;

private:
    // create asteroid
    void    spawnAsteroid                   (void);
    // create chase enemy
    void    spawnChaseEnemy                 (void);
    // Get random position within screen
    b2Vec2  getRandomPositionWithinScreen   ();
public:
    int                 mTotalAsteroid;             // total number of existing asteroid
    int                 mTotalScores;               // total score
    float               mChaseEnemySpeed;           // speed of enumy chasing player
    float               mChaseEnemySpawnCount;      // delay time to respawn chase enemy
private:
    int                 mMaxInitialAsteroid;        // Initial number of asteroid to be spawned
    CustomBaseObject*   mScoreObject;               // pointer to the score text object
    float               mTimer;                     // Timer
};
