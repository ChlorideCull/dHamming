// Thanks Pat
#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAMMDIST_LIBRARY_H
#define HAMMDIST_LIBRARY_H

#include <stdbool.h>
#include <stdint.h>

void hammdist_init(void);
bool hammdist_native();
void hammdist_forcemode(bool native);

int hamm_distance32(const uint32_t v1, const uint32_t v2);
int hamm_distance64(const uint64_t v1, const uint64_t v2);
int hamm_distance32_m(const uint32_t *v1, const uint32_t *v2, unsigned int count);
int hamm_distance64_m(const uint64_t *v1, const uint64_t *v2, unsigned int count);

#ifdef __cplusplus
}
#endif
#endif
