/*****************************************************************************
 * Copyright (c) 2018-2020 openblack developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/openblack/openblack
 *
 * openblack is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include <functional>
#include <iostream>
#include <atomic>
#include <mutex>
#include <stdexcept>
#include <unordered_map>

#pragma once

template <typename Event>
using EventHandler = std::function<void(const Event&)>;

class IEventQueue
{
public:
	IEventQueue() {};
	virtual ~IEventQueue() {};
};

template <class T>
class EventQueue: public IEventQueue
{
public:
	using Ptr = std::shared_ptr<EventQueue>;

	EventQueue() {}
	void AddHandler(EventHandler<T> handler) { _Handlers.push_back(handler); }

	void Produce(T event)
	{

		for(auto handler : _Handlers)
		{
			handler(std::move(event));
		}

	}

private:
	~EventQueue() { }
	std::vector<EventHandler<T>> _Handlers;
};
