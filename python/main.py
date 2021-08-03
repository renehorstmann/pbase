import pbase as p

import numpy as np


if __name__ == '__main__':

    print('hey')
    test = p.geoc.quat_eye()
    print(test)
    test = p.geoc.quat_conj(test)
    print(test)

    # rot_a = p.geoc.rotation_from_angle_axis([0, 0, 1, np.radians(45)])
    # rot_b = p.geoc.rotation_from_angle_axis([0, 0, 1, np.radians(135)])
    #
    # quat_a = p.geoc.quat_from_rotation_matrix(rot_a)
    # quat_b = p.geoc.quat_from_rotation_matrix(rot_b)
    #
    # quat_ab = p.geoc.quat_slerp(quat_a, quat_b, 0.5)
    #
    # print(p.geoc.quat_to_angle_axis(quat_ab))
