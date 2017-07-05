#ifndef _SHM_COM_H_HEADER
#define _SHM_COM_H_HEADER
#define TEXT_SZ 2048
struct shared_use_st {
    int written;//可读或可写的标志，非0表示可读，0表示可写
    char text[TEXT_SZ];
};
#endif
