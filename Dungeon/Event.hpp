#pragma once
#include <Base/Types/Types.hpp>

/* Event system.
 * This is a very crude event system implemention that is essentially an array of function pointes which get all called when Broadcast function is called
 * Note: nothing is stopping you from using this as array, but please don't as this implementation can change
 * Note2: event functions can not return anything, but they don't have any limits on arguments
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
	template<class ... Args>
	void BroadCast(Args ... args);

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
	Array<T>::iterator it = std::find(functions.begin(), functions.end(), func);
	if (it != functions.end())
	{
		functions.erase();
	}
}

template<class T>
template<class ...Args>
inline void CEvent<T>::BroadCast(Args ...args)
{
	for (auto it = functions.begin(); it != functions.end(); ++it)
	{
		(*it)(args...);
	}
}


#ifndef EVENT
//this macro does nothing, but is useful when you need to tell that certain thing is an event
#define EVENT
#endif // !EVENT