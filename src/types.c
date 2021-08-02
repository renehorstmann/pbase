#include <math.h>
#include <string.h>
#include "pbase/rhc/allocator.h"
#include "pbase/rhc/log.h"
#include "pbase/types.h"

#include "pbase/mathc/mathc.h"


/** Creates a new Cloud structure with empty data (malloc) */
pCloud p_cloud_new_empty(size_t size) {
    pCloud self = {0};
    self.data = p_rhc_malloc_raising(size * sizeof *self.data);
    self.size = size;
    return self;
}

/** Creates a new Cloud structure with all zeros (calloc) */
pCloud p_cloud_new_zeros(size_t size) {
    pCloud self = p_cloud_new_empty(size);
    memset(self.data, 0, self.size * sizeof *self.data);
    return self;
}

/** Creates a new Cloud structure with all zeros but .w=1 */
pCloud p_cloud_new_zeros_1(size_t size) {
    pCloud self = p_cloud_new_zeros(size);
    for(int i=0; i<self.size; i++) {
        self.data[i].w = 1;
    }
    return self;
}

/** Frees a Cloud structure */
void p_cloud_kill(pCloud *self) {
    p_rhc_free(self->data);
    *self = (pCloud) {0};
}


vec3 p_cloud_sum(pCloud self, vec3 start) {
    log_warn("p_cloud_sum: start (vec3){{%f, %f, %f}}", start.x, start.y, start.z);
    for(int i=0; i<self.size; i++)
        start = vec3_add_vec(start, self.data[i].xyz);
    return start;
}
