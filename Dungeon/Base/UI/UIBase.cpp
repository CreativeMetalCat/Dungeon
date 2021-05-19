#include "UIBase.hpp"

void Engine::UI::CUIBase::SetOnScreenLocation(Vector loc)
{
	//The limitations are here just to avoid ui being ofscreen
	onScreenLocation.X = loc.X > SCREEN_SIZE_X ? SCREEN_SIZE_X : loc.X < 0 ? 0 : loc.X;

	onScreenLocation.Y = loc.Y > SCREEN_SIZE_X ? SCREEN_SIZE_Y : loc.Y < 0 ? 0 : loc.Y;
}
