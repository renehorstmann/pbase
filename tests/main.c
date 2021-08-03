#include <stdio.h>

#include "pbase/pbase.h"


int main() {
    puts("start");

    pCloud points = p_cloud_new_zeros_1(12);

    p_cloud_kill(&points);

    puts("fin");
}
