#pragma once

#include <memory>

template <typename T>
class Optional {
public:
	Optional() : present(false) {}
	Optional(std::unique_ptr<T> obj) : object(obj), present(true) {}

	std::unique_ptr<T> &get() {
		return object;
	}

	void set(std::unique_ptr<T> obj) {
		object = std::move(obj);
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

private:
	std::unique_ptr<T> object;
	bool present;
};