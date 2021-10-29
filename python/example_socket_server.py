import pbase


def server_example():
    print("creating the server")
    server = pbase.socket.SocketServer('127.0.0.1', 12345)

    print("accepting the client")
    client = server.accept()

    print("read a msg")
    msg = client.read_msg(32)
    msg = msg.decode()
    print("read msg:", msg)

    msg = msg.upper()

    print("write msg:", msg)
    msg = msg.encode()
    client.write_msg(msg)

    print("finished")


if __name__ == '__main__':
    server_example()
    print("fin")
