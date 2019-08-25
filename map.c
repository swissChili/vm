#include "map.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


map *new_map_sized(uint64_t size)
{
    map *m = malloc(sizeof(map));

    /*
     * Calloc zeroes the memory, which is what we want.
     */

    map_node empty = EMPTY_NODE;
    
    m->items = calloc(size, sizeof(map_node));
    m->len = MAP_ALLOC_SIZE;
    m->full = 0;

    for (int i = 0 ; i < m->len; i++)
    {
        m->items[i] = empty;
    }

    return m;
}

map *new_map()
{
    return new_map_sized(MAP_ALLOC_SIZE);
}

void free_map(map *m)
{
    /* gotta be a more efficient way to do this kek */
    for (int i = 0; i < m->len; i++)
    {
        if (m->items[i].key != NULL)
        {
            free(m->items[i].key);
            free(m->items[i].val);
        }
    }
    free(m->items);
    free(m);
}

void map_set(map *m, char *k, void *v)
{
    uint64_t h = hash(k);
    uint32_t i = h % m->len;

    printf("hash %lu i %u\n", h, i);

    if (m->full++ < m->len)
    {
        puts("not full");
        map_node val =
        {
            malloc(strlen(k)),
            v,
            0,
            h,
        };

        strcpy(val.key, k);

        uint32_t current = i;

        while (MAP_USED_AT(m->items, current))
            if (current == m->len - 1)
                current = 0;
            else
                current++;

        printf("Current %d\n", current);

        m->items[current] = val;

        printf("val %d\n", *(int *)m->items[current].val);
    }
    else
    {
        puts("resizing");
        /* resize map */
        map *n_m = new_map_sized(m->len * 2);

        for (uint64_t j = 0; j < m->len; j++)
        {
            if (!MAP_USED_AT(m->items, j))
                continue;

            uint32_t current = m->items[j].h;

            while (MAP_USED_AT(m->items, current))
                if (current == m->len - 1)
                    current = 0;
                else
                    current++;

            n_m->items[current] = m->items[j];
        }

        free_map(m);
        m = n_m;
    }
}

void *map_get(map *m, char *k)
{
    uint64_t h = hash(k);
    uint32_t i = h % m->len;

    uint32_t current = i;

    printf("%s should be %s\n", m->items[current].key, k);
    printf("streq %d\n", strcmp(m->items[current].key, k));

    printf("Current get %d\n", current);

    while (strcmp(m->items[current].key, k) != 0)
    {
        printf("While at %d\n", current);
        if (current >= m->len - 1)
        {
            current = 0;
            printf("Current reset to 0\n");
        }
        else
        {
            current++;
            printf("Incrementing current\n");
        }
    }
    
    printf("val %d\n", *(int *)m->items[current].val);

    return m->items[current].val;

    //return 1;
}

void map_debug(map *m)
{
    for (int i = 0; i < m->len; i++)
    {
        if (m->items[i].val != NULL)
            printf("i = %d, k = %s, v = %d\n", i, m->items[i].key, *(int *)m->items[i].val);
    }
}
