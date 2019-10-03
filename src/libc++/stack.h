
#ifndef LIB_CPP_VECTOR_H
#define LIB_CPP_VECTOR_H

#include "../kernel/include/com/string.h"
#include "../kernel/include/mm/memorymanagement.h"

#include "vector.h"

namespace std {

	template<typename T>
	class stack {
	private:
		
        std::vector<T> m_Stack;
        bool m_Empty;

	public:
		stack();
		~stack();
		
        const T& top();

        void push(const T& t);
        void pop();
		void swap(unsigned int index1, unsigned int index2);

	};


	//IMPLEMENTATION - needed the direct include due to template<typenme T> linking

	template<typename T>
	stack<T>::stack()
	{
		


	}

	template<typename T>
	stack<T>::~stack()
	{

	}
	
	template<typename T>
	void stack<T>::push(const T& t)
	{
		

	}
	template<typename T>
	void stack<T>::pop()
	{
		
	}

	template<typename T>
	void stack<T>::swap(unsigned int index1, unsigned int index2)
	{
        
	}

}

#endif