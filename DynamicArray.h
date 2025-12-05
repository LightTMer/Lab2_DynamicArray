#pragma once
#include <iostream>
#include <string>





template<typename T>
class Array final {
public:
	Array() :
		capacity{ 4 }, length{ 0 } {
		buf = static_cast<T*>(malloc((capacity) * sizeof(T)));
	}


	Array(int cap) :
		capacity(cap) {
		buf = static_cast<T*>(malloc((capacity) * sizeof(T)));
	}


	~Array() {
		if (buf) {
			for (int i = 0; i < length; i++) {
				buf[i].~T();
			}
			free(buf);
		}
	}


	int insert(const T& value) {
		if (capacity == length) {
			int newCapacity = capacity * 2;
			T* p = static_cast<T*>(malloc(newCapacity * sizeof(T)));

			for (int i = 0; i < length; i++) {
				new(p + i) T(std::move(buf[i]));
				buf[i].~T();
			}

			free(buf);
			buf = p;
			capacity = newCapacity;
		}
		new (buf + length) T(value);
		return length++;
	}


	int insert(int index, const T& value) {
		if (index < 0 || index > length) {
			throw std::out_of_range("index out of range"); 
		}

		if (capacity == length) {
			int newCapacity = capacity * 2;
			T* p = static_cast<T*>(malloc(newCapacity * sizeof(T)));

			for (int i = 0; i < index; i++) {
				new(p + i)T(std::move(buf[i]));
				buf[i].~T();
			}

			new (p + index) T(value);

			for (int i = index; i < length; i++) {
				new (p + i + 1) T(std::move(buf[i]));
				buf[i].~T();
			}

			free(buf);
			buf = p;
			capacity = newCapacity;
			length++;
			return index;

		}

		for (int i = length; i > index; i--) {
			new (buf + i) T(std::move(buf[i - 1]));
			buf[i - 1].~T();
		}

		new (buf + index) T(value);
		length++;
		return index;
	}


	void remove(int index) {
		if (index < 0 || index >= length) {
			throw std::out_of_range("index out of range");
		}

		buf[index].~T();

		for (int i = index + 1; i < length; i++) {
			new(buf + (i - 1)) T(std::move(buf[i]));
			buf[i].~T();
		}

		length--;
	}


	const T& operator[] (int index) const {
		if (index < 0 || index >= length) {
			throw std::out_of_range("index out of range");
		}
		return buf[index];
	}


	T& operator[] (int index) {
		if (index < 0 || index >= length) {
			throw std::out_of_range("index out of range");
		}
		return buf[index];
	}


	int size() const {
		return length;
	}


	class Iterator {
	public:
		Iterator(T* current, T* begin, T* end, int step) : current(current), begin(begin), end(end), step(step) {}
		const T& get() const {
			return *current;
		}
		void set(const T& value) {
			*current = value;
		}
		void next() {
			current += step;
		}

		bool hasNext() const {
			if (step == 1) {
				return current + 1 < end;
			}
			else {
				return current - 1 >= begin;
			}
		}


	private:
		T* current;
		T* begin;
		T* end;
		int step;
	};


	Iterator iterator() {
		return Iterator(buf, buf, buf + length, +1);
	}


	Iterator iterator() const {
		return Iterator(buf, buf, buf + length, +1);
	}


	Iterator reverseIterator() {
		return Iterator(buf + length - 1, buf, buf + length, -1);
	}


	Iterator reverseIterator() const {
		return Iterator(buf + length - 1, buf, buf + length, -1);
	}


private:
	T* buf;
	int length;
	int capacity;
};