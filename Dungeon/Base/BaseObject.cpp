#include "BaseObject.hpp"

void Engine::CBaseObject::Destroy()
{
	//add code that will remove this object from game
	pendingKill = true;
}
