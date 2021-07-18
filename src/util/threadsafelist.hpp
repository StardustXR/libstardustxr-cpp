#pragma once

#include <mutex>
#include <pthread.h>
#include <functional>
#include <stddef.h>
#include <inttypes.h>
#include <vector>

namespace StardustXR {

template <class T>
class ThreadSafeList {
public:
	ThreadSafeList() {}
	~ThreadSafeList() {}

	uint32_t length() {
		const std::lock_guard<std::mutex> lock(mutex);

		if(!lengthDirty)
			return listLength;

		listLength = (bool) begin;
		ListItem *currentItem = begin;

		for(; currentItem && currentItem->next != nullptr; listLength++)
			currentItem = currentItem->next;

		return listLength;
	}
	bool exists(int index) {
		const std::lock_guard<std::mutex> lock(mutex);
		
		return (index >= 0) ? index+1 : -index > length();
	}

	T &operator[](int i) {
		return at(i);
	}
	T &at(int i) {
		const std::lock_guard<std::mutex> lock(mutex);
		return *get(i)->value;
	}

	typedef std::function<void(uint32_t, T &)> ForEachFunction;
	void forEach(ForEachFunction function) {
		const std::lock_guard<std::mutex> lock(mutex);

		uint32_t i = 0;
		ListItem *currentItem = begin;
		while(currentItem) {
			ListItem *nextItem = currentItem->next;
			function(i, *currentItem->value);
			currentItem = nextItem;
			i++;
		}
	}

	void pushFront(const T &object) {
		const std::lock_guard<std::mutex> lock(mutex);

		lengthDirty = true;
		ListItem *newItem = new ListItem();
		newItem->value = new T(object);
		newItem->next = begin;
		if(begin)
			begin->previous = newItem;
		begin = newItem;
		if(end == nullptr)
			end = begin;
	}
	void pushBack(const T &object) {
		const std::lock_guard<std::mutex> lock(mutex);
		
		lengthDirty = true;
		ListItem *newItem = new ListItem();
		newItem->value = new T(object);
		newItem->previous = end;
		if(end)
			end->next = newItem;
		end = newItem;
		if(begin == nullptr)
			begin = end;
	}
	void erase(int index) {
		const std::lock_guard<std::mutex> lock(mutex);

		lengthDirty = true;
		ListItem *item = get(index);

		if(item == begin)
			begin = item->next;
		else if(item->previous)
			item->previous->next = item->next;

		if(item == end)
			end = item->previous;
		else if(item->next)
			item->next->previous = item->previous;

		delete item->value;
		delete item;
	}

protected:
	std::mutex mutex;

	struct ListItem {
		struct ListItem *previous;
		T *value;
		struct ListItem *next;
	};
	typedef struct ListItem ListItem;

	ListItem *begin = nullptr;
	ListItem *end = nullptr;

	uint32_t listLength;
	bool lengthDirty;
	ListItem *get(int index) {
		int iMax = (index >= 0) ? index : length() + index;
		ListItem *currentItem = begin;

		for(int i=0; i<iMax; ++i)
			currentItem = currentItem->next;

		return currentItem;
	}
};

} // namespace StardustXRServer
