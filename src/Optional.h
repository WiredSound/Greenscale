#pragma once

#include <memory>

template <typename T>
class Optional {
public:
	Optional() : present(false) {}
	Optional(T obj) : object(std::make_unique<T>(obj)), present(true) {}
	Optional(std::unique_ptr<T> obj) : object(std::move(obj)), present(true) {}

	std::unique_ptr<T> &get() {
		return object;
	}

	T *getRaw() {
		object.get();
	}

	void set(std::unique_ptr<T> obj) {
		object = std::move(obj);
		present = true;
	}

	void set(T obj) {
		object = std::make_unique<T>(obj);
		present = true;
	}

	std::unique_ptr<T> claim() {
		present = false;
		return std::move(object);
	}

	void remove() {
		object.release();
		present = false;
	}

	bool isPresent() {
		return present;
	}

	T *operator->() {
		return object.get();
	}

	operator bool() {
		return isPresent();
	}

	T &operator*() {
		return *object.get();
	}

private:
	std::unique_ptr<T> object;
	bool present;
};