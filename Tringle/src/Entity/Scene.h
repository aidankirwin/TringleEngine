#include "Entity.h"

// TODO: separate definitions and declarations

struct Scene
{
public:
	Scene() {}
	~Scene() {}
	void AddEntity(Entity* e)
	{
		// Initialize entity if user has not done so
		if(!e->isInitialized) e->_Init_();
		mEntities.insert(std::make_pair(e->GetId(), e));
	}

private:
	// May be able to swap this for simple list of Ids
	// Also worth noting that this cannot go in Core.h
	// Might be worth removing Core.h and scrapping typedef system
	typedef std::map<int, Entity*> EntityMap;
	EntityMap mEntities;
};