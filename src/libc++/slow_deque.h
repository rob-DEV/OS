
#ifndef LIB_CPP_SLOW_DEQUE_H
#define LIB_CPP_SLOW_DEQUE_H

#include "../kernel/include/com/string.h"
#include "../kernel/include/mm/memorymanagement.h"

namespace std {

	template<typename T>
	class slow_deque {
	private:
		unsigned int m_VectorBufferSize; //amount of space available
		unsigned int m_Size; //current size of slow_deque
		T* m_Elements;

	public:

		slow_deque();
		~slow_deque();
		
		//std library methods
		void clear();
		void insert(const T& t);
		void emplace(const T& t);
		void erase(uint32_t first, uint32_t nToRemove);

		void push_back(const T& t);
		void pop_back();
		
		void push_front(const T& t);
		void pop_front();

		unsigned int size();
		void resize(unsigned int new_size);
		bool empty();
		void swap(unsigned int a, unsigned int b);

		const T& operator[](unsigned int i);


	};


	//IMPLEMENTATION - needed the direct include due to template<typenme T> linking

	template<typename T>
	slow_deque<T>::slow_deque()
	{
		m_Size = 0;
		m_VectorBufferSize = 1;
		m_Elements = new T[m_VectorBufferSize];
	}

	template<typename T>
	slow_deque<T>::~slow_deque()
	{
		delete[] m_Elements;
		
		m_Elements = 0;
	}

	template<typename T>
	void slow_deque<T>::clear()
	{
		delete[] m_Elements;
		m_Elements = 0;

		m_Size = 0;
		m_VectorBufferSize = 1;

		m_Elements = new T[m_VectorBufferSize];

	}

	template<typename T>
	void slow_deque<T>::erase(uint32_t firstIndex, uint32_t nToRemove)
	{
		//TODO: check for 0th element indexing
		if(firstIndex > size())
			return;

		if(nToRemove > size())
			return;

		//at least 1 element must be erased
		if(nToRemove == 0)
			nToRemove = 1;

		//actually delete the elements

		T* lhsCopy = new T[firstIndex];

		//copy elements from lhs to index to erased - 1
		memcpy(m_Elements, lhsCopy, firstIndex * sizeof(T));

		//for (size_t i = 0; i < firstIndex; i++)
            //OS::KERNEL::Terminal::getInstance()->printf("lhs 0x%x slow_test[%d] = %d\n", lhsCopy, i, lhsCopy[i]);

		//rhs copy
		uint32_t rhsCount = (m_Size) - firstIndex - nToRemove;
		T* rhsCopy = new T[rhsCount];

		//OS::KERNEL::Terminal::getInstance()->printf("rhs COUNT %d\n", rhsCount);
		//OS::KERNEL::Terminal::getInstance()->printf("rhs COUNT %d\n", rhsCount);
		//OS::KERNEL::Terminal::getInstance()->printf("n %d\n", rhsCount);
		//OS::KERNEL::Terminal::getInstance()->printf("rhs COUNT %d\n", rhsCount);

		memcpy(&m_Elements[firstIndex + nToRemove], rhsCopy, rhsCount * sizeof(T));


		//for (size_t i = 0; i < rhsCount; i++)
            //OS::KERNEL::Terminal::getInstance()->printf("rhs slow_test[%d] = %d\n", i, rhsCopy[i]);


		delete[] m_Elements;

		m_Elements = new T[firstIndex + rhsCount];

		memcpy(lhsCopy, m_Elements, firstIndex + rhsCount * sizeof(T));



		memcpy(rhsCopy, &m_Elements[firstIndex], firstIndex + rhsCount * sizeof(T));


		m_Size = firstIndex + rhsCount;

	}



	template<typename T>
	unsigned int slow_deque<T>::size()
	{
		return m_Size;
	}

	template<typename T>
	void slow_deque<T>::push_back(const T& t)
	{
		if (m_Size < m_VectorBufferSize) {
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

			delete[] copy;

			m_Elements[m_Size] = t;

			m_Size++;
	

		}

	}

	template<typename T>
	void slow_deque<T>::pop_back()
	{
		if(m_Size > 0)
			m_Size--;
	}

	template<typename T>
	void slow_deque<T>::push_front(const T& t)
	{
		//take vector
		//copy vector 
		//reverse one space front
		//copy offset 1
		//insert at 0th element

		//slow as it is always reallocing memory through underlying malloc
		if(m_Size == 0) {
			m_Elements[0] = t;
			return;
		}

		T* copy = new T[m_Size];
		memcpy(m_Elements, copy, sizeof(T) * m_Size);

		delete[] m_Elements;

		m_Elements = new T[m_Size + 1];

		memcpy(copy, &m_Elements[1], sizeof(T) * m_Size);
		delete[] copy;

		m_Elements[0] = t;

		m_Size++;
	}

	template<typename T>
	void slow_deque<T>::pop_front()
	{
		//take vector
		//copy vector 
		//reverse one space front
		//copy offset 1
		//insert at 0th element

		//slow as it is always reallocing memory through underlying malloc
		if(m_Size == 0) 
			return;

		T* copy = new T[m_Size - 1];
		memcpy(&m_Elements[1], copy, sizeof(T) * m_Size -1);

		delete[] m_Elements;

		m_Elements = new T[m_Size-1];

		memcpy(copy, m_Elements, sizeof(T) * m_Size-1);

		delete copy;

		m_Size--;

	}

	template<typename T>
	void slow_deque<T>::swap(unsigned int index1, unsigned int index2)
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
	const T& slow_deque<T>::operator[](unsigned int i)
	{
		if (i <= m_Size)
			return m_Elements[i];

		return *m_Elements;

	}
	

}

#endif