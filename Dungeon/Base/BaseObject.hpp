#pragma once
#include "Types/Types.hpp"
#include "Base/Events/Event.hpp"

namespace Engine 
{
	class CWorld;

	enum class EFaction : char
	{
		World = 0,
		Player = 1,
		EnemyOfAll = 2
	};

	//Depening on UpdateType object's update functions will be called at different times
	enum class EUpdateType : unsigned int
	{
		//This object's update and ProcessInput functions are never called
		None,
		//This object's update and ProcessInput functions are called only when player deems input as something that affects the gameplay
		//for example : when player moves, attacks, uses something in inventory, etc.
		EventOnly,
		//This object's update and ProcessInput functions are called when any key(including non-gameplay related) keys
		Full
	};

	//base object for everything that player will interact in world
	class CBaseObject
	{
	
	protected:
		bool pendingKill = false;

		RenderData data;
	public:
		String Name = "CBaseObject";

		bool Valid()const { return !pendingKill; }
		
		CBaseObject();

		//unique object id that doesn't change during it's life time and will not be given more then once in the world
		int id = 0;

		CBaseObject(RenderData _data = RenderData(), String name = "CBaseObject"):data(_data),Name(name){}

		//This is the name used when telling stuff to player(lfor example #DisplayName# killed player with knife)
		String DisplayName = "Object";

		//World in which this object exists
		CWorld* World = nullptr;

		Vector Location;

		EFaction Faction = EFaction::World;

		CollisionType Collision = CollisionType::None;

		bool Visible = true;

		EUpdateType UpdateType = EUpdateType::Full;
		
		//This is where the object should do stuff like checking what's around them, should it flee or attack etc.
		virtual void Update() = 0;

		//This is where object should do stuff that affects gameplay
		//Note that this event runs BEFORE the update cycle
		virtual void ProcessInput(int) {}

		virtual void OnOverlap(CBaseObject* other) {}

		virtual void Draw(Vector locationOffset);

		virtual void Destroy();
	};
}