#pragma once


template <class T>
class Singleton
{
protected:
	Singleton() {}

public:
	static T& GetInstance()
	{
		static T instance;
		return instance;
	}
};