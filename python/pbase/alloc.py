import ctypes as ct
from . import plib

class pAllocator_i(ct.Structure):
    _fields_ = [
        ('user_data', ct.c_void_p),
        ('malloc', ct.CFUNCTYPE(None)),
        ('calloc', ct.CFUNCTYPE(None)),
        ('realloc', ct.CFUNCTYPE(None)),
        ('free', ct.CFUNCTYPE(None)),
    ]


# // uses p_rhc_malloc_raising, p_rhc_realloc_raising, p_rhc_free
# Allocator_i p_rhc_allocator_new();
plib.p_rhc_allocator_new.restype = pAllocator_i


def allocator_new() -> pAllocator_i:
    return plib.p_rhc_allocator_new()
