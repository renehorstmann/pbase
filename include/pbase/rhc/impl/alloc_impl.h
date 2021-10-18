#ifndef RHC_ALLOC_IMPL_H
#define RHC_ALLOC_IMPL_H

#include <stdlib.h>
#include <string.h>
#include "../error.h"
#include "../log.h"
#include "../alloc.h"

#ifdef OPTION_SDL
#include <SDL2/SDL.h>
#endif

void *p_rhc_malloc_try(size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_malloc(size);
#else
    void *data = malloc(size);
#endif
    if(!data) {
        log_error("allocation failed for a size of: %zu", size);
        p_rhc_error = "allocation error";
    }
    return data;
}

void *p_rhc_calloc_try(size_t size) {
    void *data = p_rhc_malloc_try(size);
    memset(data, 0, size);
    return data;
}

void *p_rhc_realloc_try(void *memory, size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_realloc(memory, size);
#else
    void *data = realloc(memory, size);
#endif
    if(!data) {
        log_error("reallocation failed for a size of: %zu", size);
        p_rhc_error = "allocation error";
        return memory;
    }
    return data;
}


void p_rhc_free(void *memory) {
#ifdef OPTION_SDL
    SDL_free(memory);
#else
    free(memory);
#endif
}


void *p_rhc_malloc(size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_malloc(size);
#else
    void *data = malloc(size);
#endif
    assume(data, "allocation failed for a size of: %zu", size);
    return data;
}

void *p_rhc_calloc(size_t size) {
    void *data = p_rhc_malloc(size);
    memset(data, 0, size);
    return data;
}

void *p_rhc_realloc(void *memory, size_t size) {
#ifdef OPTION_SDL
    void *data = SDL_realloc(memory, size);
#else
    void *data = realloc(memory, size);
#endif
    assume(data, "reallocation failed for a size of: %zu", size);
    return data;
}


static void *p_rhc_allocator_try_malloc_impl_(Allocator_s self, size_t size) {
    return p_rhc_malloc_try(size);
}

static void *p_rhc_allocator_try_calloc_impl_(Allocator_s self, size_t size) {
    return p_rhc_calloc_try(size);
}

static void *p_rhc_allocator_try_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    return p_rhc_realloc_try(memory, size);
}

static void p_rhc_allocator_free_impl_(Allocator_s self, void *memory) {
    p_rhc_free(memory);
}

static void *p_rhc_allocator_malloc_impl_(Allocator_s self, size_t size) {
    return p_rhc_malloc(size);
}

static void *p_rhc_allocator_calloc_impl_(Allocator_s self, size_t size) {
    return p_rhc_calloc(size);
}

static void *p_rhc_allocator_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    return p_rhc_realloc(memory, size);
}

static void *p_rhc_allocator_empty_try_malloc_impl_(Allocator_s self, size_t size) {
    return NULL;
}

static void *p_rhc_allocator_empty_try_calloc_impl_(Allocator_s self, size_t size) {
    return NULL;
}

static void *p_rhc_allocator_empty_try_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    return NULL;
}

static void p_rhc_allocator_empty_try_free_impl_(Allocator_s self, void *memory) {
}

static void *p_rhc_allocator_empty_malloc_impl_(Allocator_s self, size_t size) {
    assume(false, "allocator empty raising malloc called");
    return NULL;
}

static void *p_rhc_allocator_empty_calloc_impl_(Allocator_s self, size_t size) {
    assume(false, "allocator empty raising calloc called");
    return NULL;
}

static void *p_rhc_allocator_empty_realloc_impl_(Allocator_s self, void *memory, size_t size) {
    assume(false, "allocator empty raising realloc called");
    return NULL;
}

static void p_rhc_allocator_empty_free_impl_(Allocator_s self, void *memory) {
    assume(false, "allocator empty raising free called");
}


Allocator_s p_rhc_allocator_new_try() {
    return (Allocator_s) {
        NULL,
        p_rhc_allocator_try_malloc_impl_,
        p_rhc_allocator_try_calloc_impl_,
        p_rhc_allocator_try_realloc_impl_,
        p_rhc_allocator_free_impl_
    };
}


Allocator_s p_rhc_allocator_new() {
    return (Allocator_s) {
        NULL,
        p_rhc_allocator_malloc_impl_,
        p_rhc_allocator_calloc_impl_,
        p_rhc_allocator_realloc_impl_,
        p_rhc_allocator_free_impl_
    };
}

Allocator_s p_rhc_allocator_new_empty_try() {
    return (Allocator_s) {
        NULL,
        p_rhc_allocator_empty_try_malloc_impl_,
        p_rhc_allocator_empty_try_calloc_impl_,
        p_rhc_allocator_empty_try_realloc_impl_,
        p_rhc_allocator_empty_try_free_impl_,
    };
}

Allocator_s p_rhc_allocator_new_empty() {
    return (Allocator_s) {
        NULL,
        p_rhc_allocator_empty_malloc_impl_,
        p_rhc_allocator_empty_calloc_impl_,
        p_rhc_allocator_empty_realloc_impl_,
        p_rhc_allocator_empty_free_impl_,
    };
}

#endif //RHC_ALLOC_IMPL_H
