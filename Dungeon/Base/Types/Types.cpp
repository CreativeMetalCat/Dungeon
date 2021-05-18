#include "Types.hpp"

Engine::Vector Engine::Vector::operator*(int a) { return Engine::Vector(X * a, Y * a); }

Engine::Vector Engine::Vector::operator/(int a ) { return Engine::Vector(X / a, Y / a); }

Engine::Vector Engine::Vector::operator+(Engine::Vector a) { return Engine::Vector(X + a.X, Y + a.Y); }

Engine::Vector Engine::Vector::operator-(Vector a ) { return Engine::Vector(X - a.X, Y - a.Y); }

bool Engine::Vector::operator==(Engine::Vector a )
{
	return X == a.X && Y == a.Y;
}

int Engine::Vector::Distance(Vector a)
{
	return (int)sqrt(DistanceSquared(a));
}

int Engine::Vector::DistanceSquared(Vector a)
{
	return (X - a.X)* (X - a.X) + (Y - a.Y)* (Y - a.Y);
}
