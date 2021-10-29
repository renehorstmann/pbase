import ctypes as ct
from . import plib


class pStream_i(ct.Structure):
    _fields_ = [
        ('user_data', ct.c_void_p),
        ('opt_read', ct.CFUNCTYPE(None)),
        ('opt_write', ct.CFUNCTYPE(None))
    ]

# // reads up to n bytes from the stream into memory
# // returns bytes read or 0 on error
# // if self.read is NULL, 0 is returned
# size_t p_rhc_stream_read(struct Stream_i self, void *memory, size_t n);
plib.p_rhc_stream_read.argtypes = [pStream_i, ct.c_void_p, ct.c_size_t]
plib.p_rhc_stream_read.restype = ct.c_size_t

# // writes up to n bytes into the stream from memory
# // returns bytes written or 0 on error
# // if self.write is NULL, 0 is returned
# size_t p_rhc_stream_write(struct Stream_i self, const void *memory, size_t n);
plib.p_rhc_stream_write.argtypes = [pStream_i, ct.c_void_p, ct.c_size_t]
plib.p_rhc_stream_write.restype = ct.c_size_t

# // reads exactly n bytes from the stream into memory
# // returns bytes read or 0 on error
# // if self.read is NULL, 0 is returned
# size_t p_rhc_stream_read_msg(struct Stream_i self, void *memory, size_t n);
plib.p_rhc_stream_read_msg.argtypes = [pStream_i, ct.c_void_p, ct.c_size_t]
plib.p_rhc_stream_read_msg.restype = ct.c_size_t

# // writes exactly n bytes into the stream from memory
# // returns bytes written or 0 on error
# // if self.write is NULL, 0 is returned
# size_t p_rhc_stream_write_msg(struct Stream_i self, const void *memory, size_t n);
plib.p_rhc_stream_write_msg.argtypes = [pStream_i, ct.c_void_p, ct.c_size_t]
plib.p_rhc_stream_write_msg.restype = ct.c_size_t

class Stream_i:
    def __init__(self):
        self._stream_impl = None

    def set_stream_impl(self, impl: pStream_i):
        self._stream_impl = impl

    def read(self, n: int) -> bytes:
        '''
        Receives up to n bytes
        '''
        if self._stream_impl is None:
            raise RuntimeError('Stream_i impl not set!')
        msg = bytes(n)
        ret = plib.p_rhc_stream_read(self._stream_impl, msg, len(msg))
        if ret.value == 0:
            raise RuntimeError('Stream read failed')
        return msg[0:ret.value]

    def write(self, msg: bytes) -> int:
        '''
        Writes up to len(msg) bytes

        :returns: the number of bytes send
        '''
        if self._stream_impl is None:
            raise RuntimeError('Stream_i impl not set!')
        ret = plib.p_rhc_stream_write(self._stream_impl, msg, len(msg))
        if ret.value == 0:
            raise RuntimeError('Stream write failed')
        return ret.value

    def read_msg(self, n: int) -> bytes:
        '''
        Reads a full message (blocks until size bytes are received)
        '''
        if self._stream_impl is None:
            raise RuntimeError('Stream_i impl not set!')
        msg = bytes(n)
        ret = plib.p_rhc_stream_read_msg(self._stream_impl, msg, len(msg))
        if not ret:
            raise RuntimeError('Stream read_msg failed')
        return msg

    def write_msg(self, msg: bytes):
        '''
        Writes a full message (blocks until size bytes are send)
        '''
        if self._stream_impl is None:
            raise RuntimeError('Stream_i impl not set!')
        ret = plib.p_rhc_stream_write_msg(self._stream_impl, msg, len(msg))
        if not ret:
            raise RuntimeError('Stream write_msg failed')
