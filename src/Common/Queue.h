/* openblack - A reimplementation of Lionhead's Black & White.
 *
 * openblack is the legal property of its developers, whose names
 * can be found in the AUTHORS.md file distributed with this source
 * distribution.
 *
 * openblack is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * openblack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openblack. If not, see <http://www.gnu.org/licenses/>.
 */

#include <functional>
#include <iostream>
#include <atomic>
#include <mutex>
#include <stdexcept>
#include <unordered_map>

#pragma once

template <typename Event>
using EventHandler = std::function<void(Event)>;

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
//		_Instance.push_back(event);

		for(auto handler : _Handlers)
		{
			handler(std::move(event));
//			handler(_Instance.front());
		}

//		_Instance.pop_front();
	}

private:
	~EventQueue() { }

	using Queue = std::list<T>;
	Queue _Instance;
	std::vector<EventHandler<T>> _Handlers;
};
