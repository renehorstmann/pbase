import ctypes as ct
from typing import Union, Optional
from . import plib

RHC_SOCKET_STORAGE_SIZE = 8
RHC_SOCKETSERVER_STORAGE_SIZE = 8


class pSocket(ct.Structure):
    _fields_ = [
        ('impl_storage', ct.c_char * RHC_SOCKET_STORAGE_SIZE)
    ]


class pSocketServer(ct.Structure):
    _fields_ = [
        ('impl_storage', ct.c_char * RHC_SOCKETSERVER_STORAGE_SIZE)
    ]


pSocket_p = ct.POINTER(pSocket)
pSocketServer_p = ct.POINTER(pSocketServer)

plib.p_rhc_socketserver_valid.argtypes = [pSocketServer_p]
plib.p_rhc_socketserver_valid.restype = ct.c_bool
plib.p_rhc_socketserver_new.argtypes = [ct.c_char_p, ct.c_char_p]
plib.p_rhc_socketserver_new.restype = pSocketServer
plib.p_rhc_socketserver_kill.argtypes = [pSocketServer_p]
plib.p_rhc_socketserver_accept.argtypes = [pSocketServer_p]
plib.p_rhc_socketserver_accept.restype = pSocket

plib.p_rhc_socket_valid.argtypes = [pSocket_p]
plib.p_rhc_socket_valid.restype = ct.c_bool
plib.p_rhc_socket_new.argtypes = [ct.c_char_p, ct.c_char_p]
plib.p_rhc_socket_new.restype = pSocket
plib.p_rhc_socket_kill.argtypes = [pSocket_p]
plib.p_rhc_socket_recv.argtypes = [pSocket_p, ct.c_void_p, ct.c_size_t]
plib.p_rhc_socket_recv.restype = ct.c_size_t
plib.p_rhc_socket_send.argtypes = [pSocket_p, ct.c_void_p, ct.c_size_t]
plib.p_rhc_socket_send.restype = ct.c_size_t
plib.p_rhc_socket_recv_msg.argtypes = [pSocket_p, ct.c_void_p, ct.c_size_t]
plib.p_rhc_socket_recv_msg.restype = ct.c_bool
plib.p_rhc_socket_send_msg.argtypes = [pSocket_p, ct.c_void_p, ct.c_size_t]
plib.p_rhc_socket_send_msg.restype = ct.c_bool


class Socket:
    def __init__(self, address: Union[str, pSocket], port: Optional[str]):
        '''
        Creates and connects to a server
        '''
        if port is None:
            self._impl = address
            return

        self._impl = plib.p_rhc_socket_new(address.encode(), port.encode())
        if not plib.p_rhc_socket_valid(self._impl).value:
            raise RuntimeError('Socket new failed')

    def __del__(self):
        plib.p_rhc_socket_kill(ct.byref(self._impl))

    def recv(self, n: int) -> bytes:
        '''
        Receives up to n bytes
        '''
        msg = bytes(n)
        ret = plib.p_rhc_socket_recv(ct.byref(self._impl), msg, len(msg))
        if ret.value == 0:
            raise RuntimeError('Socket recv failed')
        return msg[0:ret.value]

    def send(self, msg: bytes) -> int:
        '''
        Sends up to len(msg) bytes

        :returns: the number of bytes send
        '''
        ret = plib.p_rhc_socket_send(ct.byref(self._impl), msg, len(msg))
        if ret.value == 0:
            raise RuntimeError('Socket send failed')
        return ret.value

    def recv_msg(self, n: int) -> bytes:
        '''
        Receives a full message (blocks until size bytes are received)
        '''
        msg = bytes(n)
        ret = plib.p_rhc_socket_recv(ct.byref(self._impl), msg, len(msg))
        if not ret.value:
            raise RuntimeError('Socket recv_msg failed')
        return msg

    def send_msg(self, msg: bytes):
        '''
        Sends a full message (blocks until size bytes are send)
        '''
        ret = plib.p_rhc_socket_send(ct.byref(self._impl), msg, len(msg))
        if not ret.value:
            raise RuntimeError('Socket send_msg failed')


class SocketServer:
    def __init__(self, address: str, port: str):
        '''
        Creates a new SocketServer

        :param address: may be "localhost" or "127.0.0.1", to only enable local connections, or "0.0.0.0" to enable all incoming connections
        '''
        self._impl = plib.p_rhc_socketserver_new(address.encode(), port.encode())
        if not plib.p_rhc_socketserver_valid(self._impl).value:
            raise RuntimeError('SocketServer new failed')

    def __del__(self):
        plib.p_rhc_socketserver_kill(ct.byref(self._impl))

    def accept(self) -> Socket:
        '''
        Accepts a new client for a SocketServer
        '''
        client = plib.p_rhc_socketserver_accept(ct.byref(self._impl))
        if not plib.p_rhc_socketserver_valid(self._impl).value:
            raise RuntimeError('SocketServer accept failed')
        return Socket(client, None)

