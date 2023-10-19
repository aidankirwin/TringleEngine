#pragma once

#include <iostream>

template <typename T>
class Singleton
{
public:
	// Return single instance of object
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
	// Delete the copy constructor
	Singleton(const Singleton& obj) = delete;
protected:
	// Default constructor
	Singleton()
	{
	}
};