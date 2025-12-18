#pragma once
#include <vector>
#include <Logger/Logger.h>

class IPool
{
public:
	virtual ~IPool() = default;
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