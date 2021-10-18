#ifndef RHC_SOCKET_H
#define RHC_SOCKET_H
#ifdef OPTION_SOCKET

#include <stddef.h>

#define RHC_SOCKET_STORAGE_SIZE 8
#define RHC_SOCKETSERVER_STORAGE_SIZE 8

typedef struct {
    char impl_storage[RHC_SOCKET_STORAGE_SIZE];
} Socket;

typedef struct {
    char impl_storage[RHC_SOCKETSERVER_STORAGE_SIZE];
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
SocketServer p_rhc_socketserver_new(const char *address, const char *port);

// kills the socketserver and sets it invalid
void p_rhc_socketserver_kill(SocketServer *self);

// Accepts a new client for a SocketServer
Socket p_rhc_socketserver_accept(SocketServer *self);


//
// Socket
//

// returns true if the Socket is valid to use
bool p_rhc_socket_valid(Socket self);
// returns a new invalid Socket
Socket p_rhc_socket_new_invalid();

// Creates and connects to a server
Socket p_rhc_socket_new(const char *address, const char *port);

// kills the socket and sets it invalid
void p_rhc_socket_kill(Socket *self);

// Receives a full message (blocks until size bytes are received)
bool p_rhc_socket_recv(Socket *self, void *msg, size_t size);
// Sends a full message (blocks until size bytes are send)
bool p_rhc_socket_send(Socket *self, const void *msg, size_t size);


//
// wrapper without _rhc
//

// returns true if the SocketServer is valid to use
#define socketserver_valid p_rhc_socketserver_valid

// returns a new invalid SocketServer
#define socketserver_new_invalid p_rhc_socketserver_new_invalid

// Creates a new SocketServer
// address may be "localhost" or "127.0.0.1", to only enable local connections
// address may be "0.0.0.0" to enable all incoming connections
#define socketserver_new p_rhc_socketserver_new

// kills the socketserver and sets it invalid
#define socketserver_kill p_rhc_socketserver_kill

// Accepts a new client for a SocketServer
#define socketserver_accept p_rhc_socketserver_accept


// returns true if the Socket is valid to use
#define socket_valid p_rhc_socket_valid
// returns a new invalid Socket
#define socket_new_invalid p_rhc_socket_new_invalid

// Creates and connects to a server
#define socket_new p_rhc_socket_new

// kills the socket and sets it invalid
#define socket_kill p_rhc_socket_kill

// Receives a full message (blocks until size bytes are received)
#define socket_recv p_rhc_socket_recv
// Sends a full message (blocks until size bytes are send)
#define socket_send p_rhc_socket_send


#endif //OPTION_SOCKET
#endif //RHC_SOCKET_H
