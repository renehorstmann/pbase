import doctest
import os
import pbase as p

import numpy as np


# vec3 p_cloud_sum(pCloud self, vec3 start);
p.lib.p_cloud_sum.argtypes = [p.types.pCloud, p.mathc.vec3]
p.lib.p_cloud_sum.restype = p.mathc.vec3

def cloud_sum(cloud: np.ndarray,
              start) -> np.ndarray:

    res = p.lib.p_cloud_sum(
        p.types.cast_np_pCloud(cloud),
        p.mathc.cast_array_vec3(start)
    )
    return p.mathc.cast_vec3_np(res)


if __name__ == '__main__':

    data = np.arange(4*12, dtype=np.float32).reshape(12, 4)
    start = np.array([1, 2, 3], dtype=np.float32)

    res = cloud_sum(data, None)
    res2 = cloud_sum(data, res)
    res3 = cloud_sum(data, res2)

    p.log.info('lol', 'wh')

    print('hey', res)
