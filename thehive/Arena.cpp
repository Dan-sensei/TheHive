#include "Arena.hpp"


Arena::Arena(std::size_t size){
    firstElement = memory = new uint8_t[size];
    memoryStack.push(memory);
}

Arena::~Arena(){
    delete [] memory;
}

//===============================================
//  Allocates needed memory. On overflow, it will
//  override first element.
//===============================================
void * Arena::allocate(std::size_t size){
    uint8_t *p = memoryStack.top();
    memoryStack.pop();
    uint8_t *next = p;
    if(memoryStack.empty()){
        next += size;
        if(next >= memory)
            next = firstElement;
        memoryStack.push(next);
    }
    return p;
}

void Arena::deallocate(void* p){
    uint8_t *newPtr  = reinterpret_cast<uint8_t*>(p);
    memoryStack.push(newPtr);
}
