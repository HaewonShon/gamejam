#pragma once
#include "engine/Object.h"
#include "CustomPhysics.h"

class CustomBaseObject : public Object
{

public:

	CustomBaseObject();
	~CustomBaseObject() override;

    virtual void Shutdown() override;

	void RemoveCustomPhysicsComp(b2World* world);
	
	// New way to remove custom physics
	void RemoveCustomPhysicsComponent();

	CustomPhysics customPhysics;
protected:
    virtual void Initialize() override;
};