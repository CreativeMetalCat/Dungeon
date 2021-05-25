#include "UIBase.hpp"
#include "Base/Render/RenderMacros.h"

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

void Engine::UI::CUIBase::Draw()
{
	if (HasBorder)
	{
		if (this->Size.X > 0 && this->Size.Y > 0)
		{
			//Create upper border
			ADD_CHAR_AT(this->GetOnScreenLocation().Y, this->GetOnScreenLocation().X, ACS_ULCORNER);

			for (int i = 1; i < this->Size.X - 1; i++)
			{
				ADD_CHAR_AT(this->GetOnScreenLocation().Y, this->GetOnScreenLocation().X + i, '-');
			}

			ADD_CHAR_AT(this->GetOnScreenLocation().Y, this->GetOnScreenLocation().X + this->Size.X - 1, ACS_URCORNER);
			PRINT_AT_W(this->GetOnScreenLocation().Y, this->GetOnScreenLocation().X + 1, this->DisplayName.c_str());

			//create left and right border
			for (int i = 1; i < this->Size.Y; i++)
			{
				ADD_CHAR_AT(this->GetOnScreenLocation().Y + i, this->GetOnScreenLocation().X, '|');
				ADD_CHAR_AT(this->GetOnScreenLocation().Y + i, this->GetOnScreenLocation().X + this->Size.X - 1, '|');
			}

			//Create lower border
			ADD_CHAR_AT(this->GetOnScreenLocation().Y + this->Size.Y - 1, this->GetOnScreenLocation().X, ACS_LLCORNER);

			for (int i = 1; i < this->Size.X - 1; i++)
			{
				ADD_CHAR_AT(this->GetOnScreenLocation().Y + this->Size.Y - 1, this->GetOnScreenLocation().X + i, '-');
			}
			ADD_CHAR_AT(this->GetOnScreenLocation().Y + this->Size.Y - 1, this->GetOnScreenLocation().X + this->Size.X - 1, ACS_LRCORNER);
		}
	}
	else
	{
		attron(COLOR_PAIR((int)selected ? SelectedColors : DefaultColors));
		PRINT_AT_W(this->GetOnScreenLocation().Y, this->GetOnScreenLocation().X, this->DisplayName.c_str());
		attroff(COLOR_PAIR((int)selected ? SelectedColors : DefaultColors));
	}
}

void Engine::UI::CUIBase::ChangeState(bool sel)
{
	selected = sel;
}
