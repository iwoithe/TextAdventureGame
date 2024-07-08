#ifndef GLOBAL_DELETE_H
#define GLOBAL_DELETE_H

#define DEL_STD_VEC(vec) for (int i = 0; i < vec.size(); i++) { \
    if (vec[i] != nullptr) { \
        delete vec[i]; \
    } \
} \
vec.clear()

#define DEL_PTR_S(ptr) if (ptr != nullptr) { delete ptr; }

#endif // GLOBAL_DELETE_H
