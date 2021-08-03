import ctypes as ct

ref = ct.byref

#
# basics:
#
c_void_p = ct.c_void_p
c_bool = ct.c_bool
c_bool_p = ct.POINTER(c_bool)
c_char = ct.c_char
c_char_p = ct.c_char_p
c_int = ct.c_int
c_int_p = ct.POINTER(c_int)
c_size_t = ct.c_size_t
c_size_t_p = ct.POINTER(c_size_t)
c_float = ct.c_float
c_float_p = ct.POINTER(c_float)
c_double = ct.c_double
c_double_p = ct.POINTER(c_double)



