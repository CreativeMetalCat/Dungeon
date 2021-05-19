#pragma once
#include "Base/Render/RenderMacros.h"

struct RenderData
{
public:
	enum class ColorPalleteType :unsigned int
	{
		//White on black
		Default = 1,
		//Red on black
		Enemy = 2,
		//Blue on black
		Item = 3
	};
	ColorPalleteType Type = ColorPalleteType::Default;

	char DisplayChar = '#';
	int Color = COLOR_WHITE;
	int BackgroundColor = COLOR_BLACK;

	RenderData() {}

	RenderData(char ch) :DisplayChar(ch) {}
};