//
//  uint1024_t.c
//  BigInteger
//
//  Created by Антон Чемодуров on 02.10.2021.
//

#include "uint1024_t.h"
#include <stdlib.h>

uint1024_t from_uint(unsigned int x) {
    uint1024_t num = {
        (uint64_t *)malloc(sizeof(uint64_t)),
        1
    };
    *num.nums = x;
    return num;
}

uint1024_t from_uint1024(uint1024_t x) {
    uint1024_t new = {
        (uint64_t *)malloc(sizeof(uint64_t) * x.size),
        x.size
    };
    
    uint64_t *x_ptr = x.nums;
    uint64_t *new_ptr = new.nums;
    uint64_t *end = x.nums + x.size;
    
    while (x_ptr != end) {
        *new_ptr++ = *x_ptr++;
    }
    
    return new;
}

uint1024_t add_op(uint1024_t x, uint1024_t y) {
    if (x.size < y.size) {
        uint1024_t tmp = x;
        x = y;
        y = tmp;
    }
    
    uint1024_t x_cpy = from_uint1024(x);
    add_op_(&x_cpy, y);
    
    return x_cpy;
}


/**
 *  скаладывает два числа результат записвает в x
 *   x.size >= y.size
 */
void add_op_(uint1024_t *x, uint1024_t y) {
    uint64_t *ptr = y.nums;
    uint64_t *end = ptr + y.size;
    int r = 0;
    while (ptr != end) add(x, r++, *ptr++);
}


/**
 * привляет к x в разряд r число y  с учетом переноса, при необходимости расщиряет x
 * вызывающая фукциия горантирует что разряд r существует
 */
void add(uint1024_t *x, uint32_t r,  uint64_t y) {
    uint64_t *ptr = x->nums + r;
    uint64_t *end = x->nums + x->size;
    //uint64_t tmp = *ptr + y;
    while (UINT64_MAX - y < *ptr) { // произошло переполнение
        *ptr++ += y;
        y = 1; // перенос в следующий разряд
        if (ptr == end) { // расширяем массив если нужно
            resize(x);
            end++;
        }
    }
    *ptr += y;
}

void resize(uint1024_t *x) {
    uint64_t *new_x = (uint64_t *)malloc((x->size + 1) * sizeof(uint64_t));
    uint64_t *ptr = x->nums;
    for (int i = 0; i < x->size; ++i) {
        new_x[i] = ptr[i];
    }
    x->nums = new_x;
    x->size++;
}

void printf_value(uint1024_t x) {
    uint64_t *ptr = x.nums;
    uint64_t *end = ptr + x.size;
    while (ptr != end) {
        printf("%016");
    }
}
