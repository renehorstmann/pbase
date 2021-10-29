import pbase


def client_example():
    print("creating the connection")
    socket = pbase.socket.Socket('127.0.0.1', 12345)

    msg = "Hello Server"
    print("write msg:", msg)
    msg = msg.encode() + bytes(32 - len(msg))
    socket.write_msg(msg)

    print("reading")
    msg = socket.read_msg(32)
    msg = msg.decode()
    print("read msg:", msg)

    print("finished")


if __name__ == '__main__':
    client_example()
    print("fin")
