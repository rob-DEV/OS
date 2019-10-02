
#ifndef LIB_CPP_DEQUE_H
#define LIB_CPP_DEQUE_H

#include "../kernel/include/com/string.h"

namespace std {

	template<typename T>
	class deque {
	private:
		unsigned int m_Capacity; //amount of space available
		unsigned int m_Size; //current size of vector
		T* m_Elements;

	public:
		deque();
		deque(unsigned int size);
		~deque();
		
		//std library methods
		void clear();
		void insert(const T& t);
		void emplace(const T& t);
		void erase(const T& t);

		void push_back(const T& t);
		void pop_back();
		
		void push_front(const T& t);
		void pop_front();

		void resize(unsigned int new_size);
		void swap(unsigned int a, unsigned int b);


		T operator[](unsigned int index_pointer);

	};


	/*
	clear 		clears the contents
	insert 			inserts elements
	emplace 		constructs element in-place
	erase 			erases elements
	push_back		adds an element to the end
	emplace_back	constructs an element in-place at the end
	pop_back		removes the last element
	push_front		inserts an element to the beginning
	emplace_front	constructs an element in-place at the beginning
	pop_front		removes the first element
	resize			changes the number of elements stored
	swap			swaps the contents

	
	*/

	//IMPLEMENTATION - needed the direct include due to template<typenme T> linking


}

#endif