
#include <stdio.h>
#include "lru_cache.h"

int main()
{
    gms::lru_cache<int, int> cache(4);
    cache.set(1, 1000);
    cache.set(2, 2000);
    cache.set(3, 3000);
    cache.set(4, 4000);

    printf("value of key(%d): %d\n", 1, cache.get(1));
    printf("value of key(%d): %d\n", 2, cache.get(2));
    printf("value of key(%d): %d\n", 3, cache.get(3));
    printf("value of key(%d): %d\n", 4, cache.get(4));

    cache.set(4, 44000);
    printf("value of key(%d): %d\n", 4, cache.get(4));

    cache.set(5, 5000);
    printf("value of key(%d): %d\n", 5, cache.get(5));

    try
    {
        printf("value of key(%d): %d\n", 1, cache.get(1));
    }
    catch (std::exception const& ex)
    {
        printf("%s\n", ex.what());
    }

    printf("value of key(%d): %d\n", 2, cache.get(2));

    cache.set(6, 6000);

    try
    {
        printf("value of key(%d): %d\n", 3, cache.get(3));
    }
    catch (std::exception const& ex)
    {
        printf("%s\n", ex.what());
    }

    printf("capacity: %u\n", cache.get_capacity());
    printf("size: %u\n",cache.get_size());
    
    return 0;
}
