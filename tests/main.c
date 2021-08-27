#include <stdio.h>

#include "pbase/pbase.h"


int main() {
    puts("start");

    pCloud points = p_cloud_new_zeros_1(12);
    for(int i=0; i<points.size; i++) {
        points.data[i].x = i;
    }

    p_cloud_kill(&points);

    puts("fin");
}
