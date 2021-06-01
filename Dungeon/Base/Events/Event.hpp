#pragma once
#include <Base/Types/Types.hpp>


/* Event system.
 * This is a very crude event system implemention that is essentially an array of function pointes which get all called when Broadcast function is called
 * Note: nothing is stopping you from using this as array, but please don't as this implementation can change
 * Note2: event functions can not return anything, but they don't have any limits on arguments
 * Note3: This implementation also relies on std::vector, because it is meant to be simple
 * T -> Function 
 * C -> Context class(Usually the base class)
*/
template<class T,class C>
class CEvent
{
protected:
	Array<Pair<T,C>> functions = Array<Pair<T, C>>();
public:
	//adds function to this event
	void Bind(T func,C contextClass);

	//Calls all functions binded to the event
	//eventContext -> object that broadcasts the event
	template<class ... Args>
	void BroadCast(Args ... args);

	//Removes a bind from function
	void UnBind(T func,C contextClass);
};

#ifndef EVENT
//this macro does nothing, but is useful when you need to tell that certain thing is an event
#define EVENT
#endif // !EVENT

#ifndef events
#define events public
#endif // !events

template<class T, class C>
inline void CEvent<T, C>::Bind(T func, C contextClass)
{
	functions.push_back(Pair<T,C>(func,contextClass));
}

template<class T, class C>
inline void CEvent<T, C>::UnBind(T func, C contextClass)
{
	auto it = std::find(functions.begin(), functions.end(), Pair<T,C>(func,contextClass));
	if (it != functions.end())
	{
		functions.erase(it);
	}
}

template<class T, class C>
template<class ...Args>
inline void CEvent<T, C>::BroadCast(Args ...args)
{
	for (int i = 0; i < functions.size(); i++)
	{
		(functions[i].second->*functions[i].first)(args...);
	}
}
