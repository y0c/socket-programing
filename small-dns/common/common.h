#include "netdb.h"
typedef struct host_data {
    struct hostent* hostent;
    int hit;
} host_data;
