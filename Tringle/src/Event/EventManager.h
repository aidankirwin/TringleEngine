#pragma once

#include "Singleton.h"
#include <string>
#include <vector>

struct Event
{
	std::vector<EventArgs> Args;
	std::string Type;

	static std::vector<std::string> Types;
};

struct EventArgs
{
	enum Type
	{
		INTEGER,
		FLOAT,
		BOOL,
		STRING
	};

	Type type;

	union
	{
		int asInt;
		float asFloat;
		bool asBool;
		std::string asString;
	};
};

class EventManager : public Singleton<EventManager>
{

};

// EXAMPLE USE CASE OF EVENT SYSTEM
// -- 1 CollisionManager checks collisions of entities with colliders
// -- 2 CollisionManager detects a collision between 2 entities
// -- 3 CollisionManager registers a CollisionEvent
// -- 4 PhysicsManager reads off CollisionEvents
// -- 5 PhysicsManager handles physics of collision (i.e., makes objects bounce or stop or whatever)

// Issue: what if user wants to handle an event, creating something like CombatManager
// Now we need to know ahead of time where in the game loop CollisionManager should register events

// Soln: anything that registers an event should do so at start of game loop
// + anything that reads off events should do so at the end

// Issue: what if user wants to create new types of events that they register during the app->Update call
// + what if these events rely on other systems

//maybe soln: Might need to consider reworking game loop to call manager update functions at specific times