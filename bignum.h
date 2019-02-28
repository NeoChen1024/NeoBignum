/* ========================================================================== *\
||                   Neo_Chen's Bignum Library Routine Set                    ||
\* ========================================================================== */

/* ========================================================================== *\
||   This is free and unencumbered software released into the public domain.  ||
||									      ||
||   Anyone is free to copy, modify, publish, use, compile, sell, or	      ||
||   distribute this software, either in source code form or as a compiled    ||
||   binary, for any purpose, commercial or non-commercial, and by any	      ||
||   means.								      ||
||									      ||
||   In jurisdictions that recognize copyright laws, the author or authors    ||
||   of this software dedicate any and all copyright interest in the	      ||
||   software to the public domain. We make this dedication for the benefit   ||
||   of the public at large and to the detriment of our heirs and	      ||
||   successors. We intend this dedication to be an overt act of	      ||
||   relinquishment in perpetuity of all present and future rights to this    ||
||   software under copyright law.					      ||
||									      ||
||   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,	      ||
||   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       ||
||   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   ||
||   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR        ||
||   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,    ||
||   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR    ||
||   OTHER DEALINGS IN THE SOFTWARE.					      ||
||									      ||
||   For more information, please refer to <http://unlicense.org/>            ||
\* ========================================================================== */

/* * * * * * *
 * bignum.h  *
 * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define _BASE	10
#define _LENGTH	512

#define _POS 0	/* Positive */
#define _NEG -1	/* Negative */

#define _NEG_CHAR	-1
#define _INVAILD_CHAR	-2

#define _A	1
#define _B	-1
#define _SAME	0

struct _bignum
{
	unsigned int size;
	unsigned int ndigit; /* Number of digits */
	int8_t sign;
	int8_t *digit;	/* Signed because it would be easier to handle subtraction */
};

/* Digits is stored as little endian BCD (One digit per byte, so wasteful?) */

typedef struct _bignum bignum_t;

#define CARRY(bignum, ptr)	\
		if(bignum->digit[ptr] >= _BASE)					\
		{								\
			bignum->digit[ptr + 1] += bignum->digit[ptr] / _BASE;	\
			bignum->digit[ptr] %= _BASE;				\
		}

#define BORROW(bignum, ptr)	\
		if(bignum->digit[ptr] < 0)					\
		{								\
			bignum->digit[ptr + 1] -= bignum->digit[ptr] / _BASE + 1;\
			bignum->digit[ptr] += _BASE;				\
		}

/* Panic Codes */
#define P_SIZE	0
#define P_INVAILD_CHAR	1

void panic(int type);
bignum_t *bignum_init(unsigned int size);
void bignum_destroy(bignum_t **bignum);
int8_t bignum_digitcmp(bignum_t *src1, bignum_t *src2);
int8_t bignum_cmp(bignum_t *src1, bignum_t *src2);
void bignum_setzero(bignum_t *bignum);
void bignum_copy(bignum_t *src, bignum_t *dst);
unsigned int bignum_len(bignum_t *bignum, unsigned int start);
void bignum_rawadd(bignum_t *big, bignum_t *small, bignum_t *dst);
void bignum_rawsub(bignum_t *big, bignum_t *small, bignum_t *dst);
void bignum_rawdec(bignum_t *dst, bignum_t *dec);
void bignum_rawmul(bignum_t *large, bignum_t *small, bignum_t *dst);
void bignum_rawdiv(bignum_t *src, bignum_t *div, bignum_t *dst);
void bignum_rawmod(bignum_t *src, bignum_t *div, bignum_t *dst);
void bignum_add(bignum_t *a, bignum_t *b, bignum_t *dst);
void bignum_sub(bignum_t *a, bignum_t *b, bignum_t *dst);
void bignum_mul(bignum_t *a, bignum_t *b, bignum_t *dst);
void bignum_div(bignum_t *a, bignum_t *b, bignum_t *dst);
void bignum_mod(bignum_t *a, bignum_t *b, bignum_t *dst);
void bignum_lshift(bignum_t *bignum, unsigned int ndigit);
void bignum_rshift(bignum_t *bignum, unsigned int ndigit);
int chartoint(char c);
char inttochar(int8_t c);
void bignum_strtonum(char *str, bignum_t *dst);
void bignum_prints(char *str, size_t size, bignum_t *bignum);
void bignum_dump(bignum_t *bignum, char *name);
void bignum_inttonum(bignum_t *dst, long long int integer);
unsigned int larger(unsigned int a, unsigned int b);

unsigned long long int intpow(unsigned long long int x, unsigned long long int y);
