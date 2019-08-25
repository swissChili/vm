#ifndef VM_MAP_H
#define VM_MAP_H

#include <stdint.h>
#include "hash.h"

/* 1kb seems reasonable doesn't it? */
#define MAP_ALLOC_SIZE (1 * 1024)

struct map_node
{
    char *key;
    void *val;
    int used : 1;
    uint32_t h;
};

typedef struct map_node map_node;

#define EMPTY_NODE { NULL, NULL, 0, 0 }

struct map
{
    uint64_t len;
    map_node *items;
    uint64_t full;
    uint64_t count;
};

typedef struct map map;

#define MAP_USED_AT(m, i) (m[i].used)

map *new_map();
map *new_map_sized(uint64_t);
void free_map(map *);

void map_set(map *, char *, void *);
void *map_get(map *, char *);
int map_exists(map *, char *);
void map_debug(map *m);

#define MAP_GET(t, m, k) *(t *)map_get(m, k)
#define MAP_SET(m, k, v)                 \
    {                                    \
        __typeof__(v) *__map_temp = malloc(sizeof(__typeof(v)));    \
        *__map_temp = v;                 \
        map_set(m, k, __map_temp);       \
    }


#endif
