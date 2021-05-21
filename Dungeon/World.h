#pragma once
#include "Base/BaseObject.hpp"
#include "Base/UI/UIBase.hpp"
#include "Base/Macros.h"

namespace Engine
{
	class CWorld
	{
	private:
		unsigned int spawnCounter = 0;
	public:
		int CurrenInput = -1;

		//This value is set by object if there was an input that has effect on gameplay
		//Reset after all update functions are called
		bool GameplayUpdate = false;

		Array<Engine::CBaseObject*> Objects = Array<Engine::CBaseObject*>();

		Array<Engine::UI::CUIBase*>UIElements = Array<Engine::UI::CUIBase*>();

		//Update UI calls ui to proccess input and them be drawn
		void UpdateUI();

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

