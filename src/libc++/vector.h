#ifndef LIB_CPP_VECTOR_H
#define LIB_CPP_VECTOR_H

#include "../kernel/include/io/terminal.h"

namespace std {

    template<typename T>
    class vector {
    private:
        unsigned int m_VectorBufferSize;
        unsigned int m_Size;
        T* m_Elements;

    public:
        vector();
        vector(unsigned int size);
        ~vector();
        void push_back(T t);
        void pop_back();
        unsigned int size();
        T operator[](unsigned int index_pointer);

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
    void vector<T>::push_back(T t)
    {
        OS::KERNEL::Terminal::getInstance()->printf("push_back(%d) begin\n", *t);
        OS::KERNEL::Terminal::getInstance()->printf("m_Size : %d m_VectorBufferSize : %d\n", m_Size, m_VectorBufferSize);

        if(m_Size < m_VectorBufferSize){
            //OS::KERNEL::Terminal::getInstance()->printf("standard allocation\n");
            m_Elements[m_Size] = t;
            m_Size++;
        }
        else {
            //msize = 1
            OS::KERNEL::Terminal::getInstance()->printf("attempt vector copy\n");

            T* copyElements = new T[m_Size];

            for (size_t i = 0; i < m_Size; i++)
            {
                OS::KERNEL::Terminal::getInstance()->printf("copyElements %d\n", copyElements[i]);   
            }
            

            memcpy(m_Elements, copyElements, sizeof(T) * m_Size + 1);
            delete[] m_Elements;

            m_Elements = new T[m_VectorBufferSize + 5];
            m_VectorBufferSize += 5;

            memcpy(copyElements, m_Elements, sizeof(T) * m_Size + 1);
            //msize = 1
            
            m_Elements[m_Size] = t;
            ++m_Size;


        }

        OS::KERNEL::Terminal::getInstance()->printf("m_Size : %d m_VectorBufferSize : %d\n", m_Size, m_VectorBufferSize);
        OS::KERNEL::Terminal::getInstance()->printf("push_back() end\n");
    }
    template<typename T>
    void vector<T>::pop_back()
    {

    }

    template<typename T>
    T vector<T>::operator[](unsigned int i)
    {
        if (true)
        {
            //OS::KERNEL::Terminal::getInstance()->printf("index %d\n", i);
            return m_Elements[i];
        }

        return *m_Elements;

    }

}

#endif