#pragma once

#include <vector>
#include <list>

#include <iostream>

template<class T>
using  Array = std::vector<T>;

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
	};
}

