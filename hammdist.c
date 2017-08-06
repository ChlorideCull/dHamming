// Thanks Pat :)

#include "hammdist.h"

#include <cpuid.h>
#include <popcntintrin.h>
#include <stdlib.h>
#include <math.h>

bool is_fast = false;
char *lookup = NULL;

/*static inline void switch_bit(int bit) {
	uint32_t i, i2, diff;

	diff = (uint32_t) pow(2, bit);

	for(i = diff; i <= UINT16_MAX; i += diff * 2) {
		for(i2 = diff; i2--;) {
			lookup[i+i2] += 1;
		}
	}
}*/

static inline void gen_lookup() {
	uint32_t i, i2, diff, bit;

	lookup = calloc(UINT16_MAX + 1, 1);
	diff = 1;

	for(bit = 0; bit < 16; bit++, diff *= 2) {
		for(i = diff; i <= UINT16_MAX; i += diff * 2) {
			for(i2 = diff; i2--;) {
				lookup[i+i2] += 1;
			}
		}
	}
}

void hammdist_init(void) {
	unsigned int eax, ebx, ecx, edx;

	is_fast = __get_cpuid(0x01, &eax, &ebx, &ecx, &edx) && ecx & bit_POPCNT;

	if(!is_fast && !lookup) {
		gen_lookup();
	}
}

bool hammdist_native(void) {
	return is_fast;
}

void hammdist_forcemode(bool native) {
	is_fast = native;

	if(!is_fast && !lookup) {
		gen_lookup();
	}
}

static inline int lookup32(uint32_t v) {
	return lookup[v & 0x0000FFFF] + lookup[(v & 0xFFFF0000) >> 16];
}

static inline int lookup64(uint64_t v) {
	return lookup32((uint32_t) (v & 0x00000000FFFFFFFF)) + lookup32((uint32_t) ((v & 0xFFFFFFFF00000000) >> 32));
}

int hamm_distance32(const uint32_t v1, const uint32_t v2) {
	register uint32_t v = v1 ^ v2;
	if(is_fast) {
		return _mm_popcnt_u32(v);
	}
	else {
		return lookup32(v);
	}
}
int hamm_distance64(const uint64_t v1, const uint64_t v2) {
	register uint64_t v = v1 ^ v2;
	if(is_fast) {
		return (int) _mm_popcnt_u64(v);
	}
	else {
		return lookup64(v);
	}
}
int hamm_distance32_m(const uint32_t *v1, const uint32_t *v2, unsigned int count) {
	register uint32_t v;
	register int ret;

	ret = 0;
	if(is_fast) {
		while(count--) {
			v = v1[count] ^ v2[count];
			ret += _mm_popcnt_u32(v);
		}
	}
	else {
		while(count--) {
			v = v1[count] ^ v2[count];
			ret += lookup32(v);
		}
	}

	return ret;
}
int hamm_distance64_m(const uint64_t *v1, const uint64_t *v2, unsigned int count) {
	register uint64_t v;
	register int ret;

	ret = 0;
	if(is_fast) {
		while(count--) {
			v = v1[count] ^ v2[count];
			ret += _mm_popcnt_u64(v);
		}
	}
	else {
		while(count--) {
			v = v1[count] ^ v2[count];
			ret += lookup64(v);
		}
	}

	return ret;
}