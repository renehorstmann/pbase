import pbase as p

import ctypes as ct
import numpy as np


if __name__ == '__main__':
    print('start')


    rot_a = p.geoc.rotation_from_angle_axis([0, 0, 1, np.radians(45)])
    rot_b = p.geoc.rotation_from_angle_axis([0, 0, 1, np.radians(135)])

    quat_a = p.geoc.quat_from_rotation_matrix(rot_a)
    quat_b = p.geoc.quat_from_rotation_matrix(rot_b)

    quat_ab = p.geoc.quat_slerp(quat_a, quat_b, 0.5)

    res_aaxis = p.geoc.quat_to_angle_axis(quat_ab)
    print(res_aaxis)
    print(np.degrees(res_aaxis[3]))

    print('fin')
