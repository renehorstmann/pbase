import ctypes as ct
from typing import Union, Optional
from . import plib

from . import alloc
from . import stream

RHC_SOCKET_STORAGE_SIZE = 8


class pSocket(ct.Structure):
    _fields_ = [
        ('stream', stream.pStream_i),
        ('allocator', alloc.pAllocator_i),
        ('impl_storage', ct.c_char * RHC_SOCKET_STORAGE_SIZE)
    ]


class pSocketServer(ct.Structure):
    _fields_ = [
        ('impl_storage', ct.c_char * RHC_SOCKET_STORAGE_SIZE)
    ]


pSocket_p = ct.POINTER(pSocket)
pSocket_p_p = ct.POINTER(pSocket_p)
pSocketServer_p = ct.POINTER(pSocketServer)

plib.p_rhc_socketserver_valid.argtypes = [pSocketServer]
plib.p_rhc_socketserver_valid.restype = ct.c_bool
plib.p_rhc_socketserver_new.argtypes = [ct.c_char_p, ct.c_uint16]
plib.p_rhc_socketserver_new.restype = pSocketServer
plib.p_rhc_socketserver_kill.argtypes = [pSocketServer_p]
plib.p_rhc_socketserver_accept_a.argtypes = [pSocketServer_p, alloc.pAllocator_i]
plib.p_rhc_socketserver_accept_a.restype = pSocket_p

plib.p_rhc_socket_valid.argtypes = [pSocket_p]
plib.p_rhc_socket_valid.restype = ct.c_bool
plib.p_rhc_socket_new_a.argtypes = [ct.c_char_p, ct.c_uint16, alloc.pAllocator_i]
plib.p_rhc_socket_new_a.restype = pSocket_p
plib.p_rhc_socket_kill.argtypes = [pSocket_p_p]


class Socket(stream.Stream_i):
    def __init__(self, address: Union[str, pSocket_p], port: Optional[int]):
        '''
        Creates and connects to a server
        '''
        super().__init__()
        if port is None:
            self._impl = address
            self.set_stream_impl(self._impl.contents.stream)
            return

        self._impl = plib.p_rhc_socket_new_a(address.encode(), port, alloc.allocator_new())
        if not plib.p_rhc_socket_valid(self._impl):
            raise RuntimeError('Socket new failed')
        self.set_stream_impl(self._impl.contents.stream)

    def __del__(self):
        plib.p_rhc_socket_kill(ct.byref(self._impl))


class SocketServer:
    def __init__(self, address: str, port: int):
        '''
        Creates a new SocketServer

        :param address: may be "localhost" or "127.0.0.1", to only enable local connections, or "0.0.0.0" to enable all incoming connections
        '''
        self._impl = plib.p_rhc_socketserver_new(address.encode(), port)
        if not plib.p_rhc_socketserver_valid(self._impl):
            raise RuntimeError('SocketServer new failed')

    def __del__(self):
        plib.p_rhc_socketserver_kill(ct.byref(self._impl))

    def accept(self) -> Socket:
        '''
        Accepts a new client for a SocketServer
        '''
        client = plib.p_rhc_socketserver_accept_a(ct.byref(self._impl), alloc.allocator_new())
        if not plib.p_rhc_socketserver_valid(self._impl):
            raise RuntimeError('SocketServer accept failed')
        return Socket(client, None)

