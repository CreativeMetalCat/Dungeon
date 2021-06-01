#pragma once

#include <vector>
#include <list>

#include <iostream>

#include "Base/Render/RenderData.h"
#include <string>
#include "Base/Macros.h"

template<class T>
using  Array = std::vector<T>;

#pragma region Pair
template<class Key, class Value>
using Pair = std::pair<Key,Value>;
#define Key first
#define Value second
#pragma endregion



//array of pairs
template<class Key,class Value>
using Map = std::vector<std::pair<Key, Value>>;

#ifndef valid_index
//This macro is used as any Array function
//Example array_obj.valid_index(9) 
#define valid_index(ind) size() > ind && ind > -1
#endif // !valid_index


template<class T>
using  List = std::list<T>;

typedef std::string String;

#define SCREEN_SIZE_X 120
#define SCREEN_SIZE_Y 30

enum CollisionType
{
	//For decorations
	None,
	//For walls, obstacles, etc.
	Block,
	//For traps, pickups, etc.
	Overlap
};

namespace Engine
{
	struct Vector
	{
	public:
		int X = 0;

		int Y = 0;

		Vector(int x = 0, int y = 0) :X(x), Y(y) {}

		Vector operator*(int);

		Vector operator/(int);

		Vector operator+(Vector);

		Vector operator-(Vector);

		bool operator==(Vector);

		int Distance(Vector);

		int DistanceSquared(Vector);

		Vector Normalise();

		int Lenght();

		String ToString() { return "X: " + STRING(X) + " Y: " + STRING(Y); }
	};
}

using Vector = Engine::Vector;