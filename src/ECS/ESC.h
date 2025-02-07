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


class IPool
{
public:
	virtual ~IPool() = 0;
};

template<typename T>
class Pool : public IPool
{
private:
	std::vector<T> data;
public:
	Pool( int size = 100 )
	{
		data.resize( size );
	}

	virtual ~Pool() override = default;

	bool IsEmpty() const
	{
		return data.empty();
	}

	int GetSize() const
	{
		return data.size();
	}

	void Resize( int n )
	{
		if ( n > 0 )
		{
			data.resize( n );
			return;
		}
		Logger::Error( "Pool::Reize::Negative value passed!" );
	}

	void Clear()
	{
		data.clear();
	}

	void Add( T object )
	{
		data.push_back( object );
	}

	void Set( int index, T object )
	{
		data[index] = object;
	}

	T& operator []( unsigned int index )
	{
		return data[index];
	}

	const T& operator []( unsigned int index ) const
	{
		return data[index];
	}
};


class Registry
{
private:
	int numEntities{ 0 };

	// Vector ind = component ID
	// Pool ind = entity ID
	std::vector<IPool*> componentPool;
};