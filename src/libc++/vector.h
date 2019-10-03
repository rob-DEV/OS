
#ifndef LIB_CPP_VECTOR_H
#define LIB_CPP_VECTOR_H

#include "../kernel/include/com/string.h"
#include "../kernel/include/mm/memorymanagement.h"

namespace std {

	template<typename T>
	class vector {
	private:
		unsigned int m_VectorBufferSize; //amount of space available
		unsigned int m_Size; //current size of vector
		T* m_Elements;

	public:
		vector();
		vector(unsigned int size);
		~vector();
		void push_back(const T& t);
		void pop_back();

		void resize(unsigned int new_size);
		void swap(unsigned int index1, unsigned int index2);

		unsigned int size();
		T operator[](unsigned int index_pointer);


		/*
		
		clear clears the contents (public member function)
		insert inserts elements (public member function)
		emplace (C++11)constructs element in-place (public member function)
		erase erases elements
		
		*/


	};


	//IMPLEMENTATION - needed the direct include due to template<typenme T> linking

	template<typename T>
	vector<T>::vector()
	{
		m_Size = 0;
		m_VectorBufferSize = 1;
		m_Elements = new T[m_VectorBufferSize];


	}

	template<typename T>
	vector<T>::vector(unsigned int size)
	{
		m_Size = size;
		m_VectorBufferSize = size;
		m_Elements = new T[m_VectorBufferSize];


	}
	template<typename T>
	vector<T>::~vector()
	{
		delete[] m_Elements;
		
		m_Elements = 0;
	}
	template<typename T>
	unsigned int vector<T>::size()
	{
		return m_Size;
	}
	template<typename T>
	void vector<T>::push_back(const T& t)
	{
		if (m_Size < m_VectorBufferSize) {
			//OS::KERNEL::Terminal::getInstance()->printf("standard allocation\n");
			m_Elements[m_Size] = t;
			m_Size++;
		}
		else {

			T* copy = new T[m_Size];

			memcpy(m_Elements, copy, sizeof(T) * m_Size);

			delete[] m_Elements;

			m_VectorBufferSize += 5;
			m_Elements = new T[m_VectorBufferSize];
			memcpy(copy, m_Elements, sizeof(T) * m_Size);

			m_Elements[m_Size] = t;

			m_Size++;
	

		}

	}
	template<typename T>
	void vector<T>::pop_back()
	{
		if(m_Size > 0)
			m_Size--;
	}

	template<typename T>
	void vector<T>::swap(unsigned int index1, unsigned int index2)
	{
		if(m_Size > 1) {


			if(index1 < m_Size && index2 < m_Size)
				return; //throw out of bounds exception

			T tmp;
			memcpy(&m_Elements[index1], &tmp, sizeof(T));
			

			m_Elements[index1] = m_Elements[index2];
			
			memcpy(&tmp, &m_Elements[index2], sizeof(T));
			

			
		}
	}


	template<typename T>
	T vector<T>::operator[](unsigned int i)
	{
		if (i <= m_Size)
			return m_Elements[i];

		return *m_Elements;

	}
	

}

#endif