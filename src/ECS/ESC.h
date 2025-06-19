#pragma once
#include <Logger/Logger.h>
#include <bitset>
#include <vector>
#include <ostream>
#include <unordered_map>
#include <set>
#include <typeindex>
#include <algorithm>


const size_t MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class IComponent
{
protected:
	static size_t nextId;
};

template<typename T>
class Component : public IComponent
{
	static size_t GetId()
	{
		static size_t id = nextId++;
		return id;
	}
};


class Entity
{
private:
	size_t id;
public:
	Entity( size_t id );
	Entity( const Entity& entity ) = default;

	size_t GetID() const;

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
	void RequireComponent();
};

template <typename TComponent>
void System::RequireComponent()
{
	const size_t componentId = Component<TComponent>::GetId();
	componentSignature.set( componentId );
}


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
	Pool( size_t size = 100 )
	{
		data.resize( size );
	}

	virtual ~Pool() override = default;

	bool IsEmpty() const
	{
		return data.empty();
	}

	size_t GetSize() const
	{
		return data.size();
	}

	void Resize( size_t n )
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

	void Set( size_t index, T object )
	{
		if ( index >= data.size() )
		{
			data.resize( std::max( data.size() * 2, index + 1 ) );
		}
		data[index] = object;
	}

	T& operator []( size_t index )
	{
		return data[index];
	}

	const T& operator []( size_t index ) const
	{
		return data[index];
	}
};


class Registry
{
private:
	size_t numEntities{ 0 };
	std::set<Entity> entitiesToBeAdded;
	std::set<Entity> entitiesToBeKilled;

	//Vector ind == component ID
	//Pool ind == entity ID
	std::vector<IPool*> componentPools;

	//Vector ind == entity id
	//Components on/off for an entity
	std::vector<Signature> entityComponentSignatures;
	std::unordered_map<std::type_index, System*> systems;
public:
	void Update();

	Entity CreateEntity();

	void KillEntity( Entity entity );

	void AddEntityToSystem( Entity entity );

	template<typename TComponent, typename ...TArgs>
	void AddComponent( Entity entity, TArgs&& ...args );

	template<typename TComponent>
	void RemoveComponent( Entity entity );

	template<typename TComponent>
	bool HasComponent( Entity entity );


	template<typename TSystem, typename ...TArgs>
	void AddSystem( TArgs&& ...args );

	template<typename TSystem>
	void RemoveSystem();

	template<typename TSystem>
	bool HasSystem();

	template<typename TSystem>
	void GetSystem();
};


template<typename TComponent, typename ...TArgs>
void Registry::AddComponent( Entity entity, TArgs&& ...args )
{
	const size_t componentId = Component<TComponent>::GetId();
	const size_t entityId = entity.GetID();

	if ( componentId >= componentPools.size() )
	{
		componentPools.resize( std::max( componentPools.size() * 2, componentId + 1 ), nullptr );
	}

	if ( !componentPools[componentId] )
	{
		Pool<TComponent>* newComponentPool = new Pool<TComponent>();
		componentPools[componentId] = newComponentPool;
	}

	Pool<TComponent>* componentPool = componentPools[componentId];
	TComponent newComponent{ std::forward<TArgs>( args )... };
	componentPool->Set( entityId, newComponent );
	entityComponentSignatures[entityId].set( componentId );
}

template<typename TComponent>
void Registry::RemoveComponent( Entity entity )
{
	const size_t entityId = entity.GetID();
	const size_t componentId = Component<TComponent>::GetId();

	entityComponentSignatures[entityId].set( componentId, false );
}

template<typename TComponent>
bool Registry::HasComponent( Entity entity )
{
	const size_t entityId = entity.GetID();
	const size_t componentId = Component<TComponent>::GetID();

	return entityComponentSignatures[entityId].test( componentId );
}

template<typename TSystem, typename ...TArgs>
void Registry::AddSystem( TArgs && ...args )
{
	TSystem* newSystem = new TSystem( std::forward<TArgs>( args )... );
	systems[std::type_index( typeid( TSystem ) )] = newSystem;
}

template<typename TSystem>
void Registry::RemoveSystem()
{
}

template<typename TSystem>
bool Registry::HasSystem()
{
	return false;
}

template<typename TSystem>
void Registry::GetSystem()
{
	// TODO: insert return statement here
}

