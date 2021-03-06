#ifndef RHC_SOCKET_H
#define RHC_SOCKET_H
#ifdef OPTION_SOCKET

#include <stdint.h>
#include "types.h"
#include "alloc.h"

#define RHC_SOCKET_STORAGE_SIZE 8

typedef struct {
    Stream_i stream;
    Allocator_i allocator;
    char impl_storage[RHC_SOCKET_STORAGE_SIZE];
} Socket;

typedef struct {
    char impl_storage[RHC_SOCKET_STORAGE_SIZE];
} SocketServer;


//
// SocketServer
//

// returns true if the SocketServer is valid to use
bool p_rhc_socketserver_valid(SocketServer self);

// returns a new invalid SocketServer
SocketServer p_rhc_socketserver_new_invalid();

// Creates a new SocketServer
// address may be "localhost" or "127.0.0.1", to only enable local connections
// address may be "0.0.0.0" to enable all incoming connections
// if address is NULL, "127.0.0.1" is used
// SDLs implementation is only able to use "0.0.0.0"
SocketServer p_rhc_socketserver_new(const char *address, uint16_t port);

// kills the socketserver and sets it invalid
void p_rhc_socketserver_kill(SocketServer *self);

// Accepts a new client for a SocketServer
// If an error occures, SocketServer will be set invalid and false is returned
Socket *p_rhc_socketserver_accept_a(SocketServer *self, Allocator_i a);


//
// Socket
//

// safe way to use the Stream interface
static Stream_i socket_get_stream(Socket *self) {
    if(!self)
        return stream_new_invalid();
    return self->stream;
}

// returns true if the Socket is valid to use
bool p_rhc_socket_valid(const Socket *self);
// returns a new invalid Socket
Socket *p_rhc_socket_new_invalid();

// Creates and connects to a server
// if address is NULL, "127.0.0.1" is used
Socket *p_rhc_socket_new_a(const char *address, uint16_t port, Allocator_i a);

// kills the socket and sets it invalid
void p_rhc_socket_kill(Socket **self_ptr);



//
// wrapper without _rhc
//

// Accepts a new client for a SocketServer
// If an error occures, SocketServer will be set invalid and false is returned
static Socket *socketserver_accept(SocketServer *self) {
    return p_rhc_socketserver_accept_a(self, RHC_DEFAULT_ALLOCATOR);
}

// Creates and connects to a server
// if address is NULL, "127.0.0.1" is used
static Socket *socket_new(const char *address, uint16_t port) {
    return p_rhc_socket_new_a(address, port, RHC_DEFAULT_ALLOCATOR);
}


// returns true if the SocketServer is valid to use
#define socketserver_valid p_rhc_socketserver_valid

// returns a new invalid SocketServer
#define socketserver_new_invalid p_rhc_socketserver_new_invalid

// Creates a new SocketServer
// address may be "localhost" or "127.0.0.1", to only enable local connections
// address may be "0.0.0.0" to enable all incoming connections
// if address is NULL, "127.0.0.1" is used
// SDLs implementation is only able to use "0.0.0.0"
#define socketserver_new p_rhc_socketserver_new

// kills the socketserver and sets it invalid
#define socketserver_kill p_rhc_socketserver_kill


// returns true if the Socket is valid to use
#define socket_valid p_rhc_socket_valid
// returns a new invalid Socket
#define socket_new_invalid p_rhc_socket_new_invalid

// kills the socket and sets it invalid
#define socket_kill p_rhc_socket_kill


#endif //OPTION_SOCKET
#endif //RHC_SOCKET_H
