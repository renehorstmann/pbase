import sys
import pbase as p

if __name__ == '__main__':
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print('Usage:', sys.argv[0], '<load_mesh.stl> <save_mesh.ply> [ascii=0]')
        exit(1)

    ascii = False
    if len(sys.argv) == 4 and sys.argv[3] == '1':
        print('saving as ascii ply')
        ascii = True

    points, indices = p.io.load_mesh_stl(sys.argv[1])
    p.io.save_mesh_ply(points, indices, sys.argv[2], ascii)
