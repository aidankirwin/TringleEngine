#pragma once
#include "Mesh.h"

class Component
{
public:
	Component() {}
	~Component() {}

	bool isInitialized = false;

	virtual void Init(unsigned int entityId)
	{
		isInitialized = true;
		eId = entityId;
	}
	virtual void Destroy() {}

private:
	unsigned int eId;
};

class SpriteComponent : public Component
{
public:
	SpriteComponent() {}
	~SpriteComponent() {}

private:
	Mesh* mMesh;

};

/* TODO: add engine provided components
- SpriteComponent
- ModelComponent
- 2DRigidbodyColliderComponent
- 3DRigidbodyColliderComponent
- 2DRigidbodyPhysicsComponent
- 3DRigidbodyPhysicsComponent
- AudioComponent
- TransformComponent
- InputComponent
- 2DAnimationComponent
- 3DAnimationComponent

Engine components simply act as user interface for engine subsystems
e.g., the model component may contain mesh, texture, and shader data which
are each sent to respective engine managers
*/