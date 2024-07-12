
#define _AllocIMD_ptrV(type, size) (type*)malloc(sizeof(type) * (size))
#define _CheckIMD_ptr(ptr) ((ptr) != nullptr)
#define _AllocIMD_ptr(type) (type*)malloc(sizeof(type))
