#pragma once
#include <cstddef>

class IComponent
{
protected:
	static size_t nextId;
};

template<typename T>
class Component : public IComponent
{
public:
	static size_t GetId()
	{
		static size_t id = nextId++;
		return id;
	}
};