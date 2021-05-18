#pragma once
#include "Base/BaseObject.hpp"
namespace Engine
{
	class CWorld
	{
	private:
		unsigned int spawnCounter = 0;
	public:
		
		Array<Engine::CBaseObject*> Objects = Array<Engine::CBaseObject*>();

		template<class Class, class ... Args>
		Class* SpawnObject(Args ... args);
	};

	template<class Class, class ...Args>
	inline Class* CWorld::SpawnObject(Args ... args)
	{
		Class* obj = new Class(args...);
		if (obj)
		{
			obj->World = this;
			obj->id = spawnCounter;
			spawnCounter++;
			Objects.push_back(obj);

			return static_cast<Class*>(obj);
		}
		else
		{
			return nullptr;
		}
	}
}

