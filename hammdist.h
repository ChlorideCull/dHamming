#ifndef HAMMDIST_LIBRARY_H
#define HAMMDIST_LIBRARY_H

#include <stdbool.h>
#include <stdint.h>

void hammdist_init(void);
bool hammdist_native();
void hammdist_forcemode(bool native);

int hamm_distance32(uint32_t v1, uint32_t v2);
int hamm_distance64(uint64_t v1, uint64_t v2);
int hamm_distance32_m(uint32_t *v1, uint32_t *v2, unsigned int count);
int hamm_distance64_m(uint64_t *v1, uint64_t *v2, unsigned int count);

#endif