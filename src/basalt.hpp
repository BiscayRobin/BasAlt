#pragma once

#include <bits/stdint-uintn.h>
#include <cstdlib>
#include <cstdio>

uint64_t allocNumb = 0;

void* operator new(size_t size){
    allocNumb++;
    return malloc(size);
}
