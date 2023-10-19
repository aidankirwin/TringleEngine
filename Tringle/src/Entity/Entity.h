#pragma once

#include <string>

#include "Core.h"
#include "EventManager.h"

// TODO: separate definitions and declarations

class Entity
{
public:
	Entity()
	{
		mId = Entity::GenerateID();
	}

	bool isInitialized = false;
	// Inherited entities may choose fill this with component initialization
	virtual void Init() {}
	virtual void Destroy()
	{
		// Loop through all components and call individual destroy functions
		// Base component destroy function is empty
		for (auto itr = mComponents.begin(); itr != mComponents.end(); ++itr)
		{
			auto c = itr->second;
			c->Destroy();

			// Free memory
			// TODO: might be worth exporing alternative system of storing components
			// Entities may be created and destroyed frequently, leading to lots of
			// allocating + deallocating and raw pointers

			// Might also be better to use events for component destruction
			// That way individual engine systems can manage deletion
			// An alternative solution would be needed for user-made components however
			delete c;
		}
	}
	// Some components handle events automatically
	virtual void OnEvent(Event* e) {}

	void AddComponent(std::string SID, Component* c)
	{
		// Initialize component if user has not done so
		if(!c->isInitialized) c->Init(mId);
		mComponents.insert(std::make_pair(SID, c));
	}
	Component* GetComponent(std::string SID)
	{
		return mComponents.at(SID);
	}

	unsigned int GetId()
	{
		return mId;
	}

private:
	// Component pointer vector
	ComponentMap mComponents;

	// Entity instance unique id
	unsigned int mId;

	// Entity id counter
	static unsigned int GenerateID()
	{
		if(!mAllIds) mAllIds = 0;
		unsigned int newId = mAllIds;
		mAllIds++;
		return newId;
	}
	static unsigned int mAllIds;

public:
	void _Init_()
	{
		isInitialized = true;
		Init();
	}
};