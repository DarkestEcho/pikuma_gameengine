#pragma once
#include <bitset>
#include <vector>
#include <ostream>


const unsigned int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class IComponent
{
protected:
	static int nextId;
};

template<typename T>
class Component : public IComponent
{
	static int GetId()
	{
		static int id = nextId++;
		return id;
	}
};


class Entity
{
private:
	int id;
public:
	Entity( int id );
	Entity( const Entity& entity ) = default;

	int GetID() const;

	Entity& operator = ( const Entity& entity ) = default;

	bool operator == ( const Entity& other ) const;
	bool operator != ( const Entity& other ) const;
	bool operator < ( const Entity& other ) const;
	bool operator > ( const Entity& other ) const;
};

std::ostream& operator << ( std::ostream& os, const Entity& entity );

class System
{
private:
	// Which components an entity must have for the system to consider the entity
	Signature componentSignature;
	// List of all entities that the system is interested in
	std::vector<Entity> entities;
public:
	System() = default;
	virtual ~System() = default;

	void AddEntityToSystem( Entity entity );

	void RemoveAllEntityEntriesFromSystem( Entity entity );

	void RemoveEntityFromSystem( Entity entity );

	const std::vector<Entity>& GetSystemEntities() const;

	const Signature& GetComponentSignature() const;

	template <typename TComponent>
	void RequireComponent()
	{
		const auto componentId = Component<TComponent>::GetId();
		componentSignature.set( componentId );
	}
};


class Registry
{
public:
	// TODO: ...
};
