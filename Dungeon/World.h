#pragma once
#include "Base/BaseObject.hpp"
#include "Base/UI/UIBase.hpp"

namespace Engine
{
	class CWorld
	{
	private:
		unsigned int spawnCounter = 0;
	public:
		
		Array<Engine::CBaseObject*> Objects = Array<Engine::CBaseObject*>();

		Array<Engine::UI::CUIBase*>UIElements = Array<Engine::UI::CUIBase*>();

		template<class Class, class ... Args>
		Class* SpawnObject(Args ... args);

		template<class Class, class ... Args>
		Class* CreateUI(UI::CUIBase* parent = nullptr,Args...args);
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

			return obj;
		}
		else
		{
			return nullptr;
		}
	}
	template<class Class, class ...Args>
	inline Class* CWorld::CreateUI(UI::CUIBase*parent, Args ...args)
	{
		Class* ui = new Class(args...);
		if (ui)
		{
			if (parent)
			{
				parent->ChildUI.push_back(ui);
				ui->Parent = parent;
			}
			UIElements.push_back(ui);
			return ui;
		}
		else
		{
			return nullptr;
		}
	}
}

