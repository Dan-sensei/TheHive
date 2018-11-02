#ifndef _ARENA_H
#define _ARENA_H

#include <cstdint>
#include <stack>

class Arena{

    public:
        Arena(std::size_t size);
        Arena(const Arena &orig) = delete;
        void operator=(const Arena &orig) = delete;
        ~Arena();

        void * allocate(std::size_t size);
        void deallocate(void* p);

    private:

        uint8_t *memory;
        uint8_t *memoryEnd;
        std::stack<uint8_t*> memoryStack;
};

#endif
