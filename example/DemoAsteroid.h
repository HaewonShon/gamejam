#pragma once
#include "CustomBaseObject.h"

class DemoEnemySpawner;
class DemoAsteroid : public CustomBaseObject
{
public:
    static DemoAsteroid* CreateAsteroid(b2Vec2 position, b2Vec2 scale, int life, float speed, int score);
    DemoAsteroid();
    void Update(float dt) override;
private:
    virtual void Initialize() override;
public:
    int                 mLife;
    DemoEnemySpawner*   mSpawner;
    int                 mScore;
    float               mDeathCount;
private:
    bool                mbIsDead;
    float               mTimer;
    float               mSpeed;
};
