#pragma once
#include <Base/Types/Types.hpp>


/* Event system.
 * This is a very crude event system implemention that is essentially an array of function pointes which get all called when Broadcast function is called
 * Note: nothing is stopping you from using this as array, but please don't as this implementation can change
 * Note2: event functions can not return anything, but they don't have any limits on arguments
 * Note3: This implementation also relies on std::vector, because it is meant to be simple
*/
template<class T>
class CEvent
{
protected:
	Array<T> functions = Array<T>();
public:
	//adds function to this event
	void Bind(T func);

	//Calls all functions binded to the event
	template<class ... Args, class ObjType>
	void BroadCast(ObjType  eventContext, Args ... args);

	//Removes a bind from function
	void UnBind(T func);
};

template<class T>
inline void CEvent<T>::Bind(T func)
{
	functions.push_back(func);
}

template<class T>
inline void CEvent<T>::UnBind(T func)
{
	auto it = std::find(functions.begin(), functions.end(), func);
	if (it != functions.end())
	{
		functions.erase();
	}
}

template<class T>
template<class ...Args,class ObjType>
inline void CEvent<T>::BroadCast(ObjType  eventContext, Args ...args)
{
	for (int i = 0; i < functions.size(); i++)
	{
		(eventContext->*functions[i])(args...);
	}
}

#ifndef EVENT
//this macro does nothing, but is useful when you need to tell that certain thing is an event
#define EVENT
#endif // !EVENT

#ifndef events
#define events public
#endif // !events
