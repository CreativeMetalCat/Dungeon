#include "UIBase.hpp"

Engine::UI::CUIBase::CUIBase(String name, String displayName, Vector location, Vector size, bool hasBorder)
	:Name(name),DisplayName(displayName),Size(size),HasBorder(hasBorder)
{
	SetOnScreenLocation(location);
}

Engine::Vector Engine::UI::CUIBase::GetOnScreenLocation() 
{
	//recursive function that basically just offsets it's own location
	return onScreenLocation + (Parent ? Parent->GetOnScreenLocation() : Vector(0, 0));
}

void Engine::UI::CUIBase::SetOnScreenLocation(Vector loc)
{
	//The limitations are here just to avoid ui being ofscreen
	onScreenLocation.X = loc.X > SCREEN_SIZE_X ? SCREEN_SIZE_X : loc.X < 0 ? 0 : loc.X;

	onScreenLocation.Y = loc.Y > SCREEN_SIZE_X ? SCREEN_SIZE_Y : loc.Y < 0 ? 0 : loc.Y;
}
