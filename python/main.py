import pbase as p

import ctypes as ct
import numpy as np


if __name__ == '__main__':
    print('start')

    v = p.bb.c_int()

    points, indices = p.meshprimitives.arrow([0, 0, 0], [100, 0, 0], 10)

    p.io.save_mesh_ply(points, indices, 'test.ply', False)


    print('fin')
