#ifndef LIB_CPP_TYPE_TRAITS_H
#define LIB_CPP_TYPE_TRAITS_H

namespace std {

    template <typename T>
    bool is_pointer(T const &t) // edited: was "T t"; see the comments
    {
        return false;
    }

    template <typename T>
    bool is_pointer(T *t)
    {
        return true;
    }   

}

#endif

