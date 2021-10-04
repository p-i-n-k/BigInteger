//
//  uint1024_t.h
//  BigInteger
//
//  Created by Антон Чемодуров on 02.10.2021.
//

#ifndef uint1024_t_h
#define uint1024_t_h

#include <stdio.h>

typedef struct {
    uint64_t *nums;
    size_t size;
} uint1024_t;

uint1024_t from_uint(unsigned int x);
uint1024_t add_op(uint1024_t x, uint1024_t y);
void add_op_(uint1024_t *x, uint1024_t y);
void resize(uint1024_t *x);
void add(uint1024_t *x, uint32_t r, uint64_t y);
uint1024_t from_uint1024(uint1024_t x);

void printf_value(uint1024_t x);
void scanf_value(uint1024_t* x);
#endif /* uint1024_t_h */
