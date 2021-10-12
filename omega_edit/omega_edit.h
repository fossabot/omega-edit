#ifndef OMEGA_OMEGA_EDIT_H
#define OMEGA_OMEGA_EDIT_H


#include <cstdio>
#include <cstdint>

// Forward declarations
struct session_t;
struct author_t;
struct viewport_t;

// Create a session (return 0 on error, pointer otherwise)
session_t * create_session(FILE * file_ptr);

// Add an author to the given session, returns a pointer to the author structure
const author_t * add_author(session_t * session_ptr, const char * author_name);

// Add a viewport to the given session
viewport_t * add_viewport(session_t *session_ptr, int32_t capacity);

// Destroy the given session
void destroy_session(session_t * session_ptr);

// handle changes (return 0 on success, non-zero otherwise)
int ovr(session_t * session_ptr, int64_t offset, uint8_t byte, const author_t * author_ptr);
int del(session_t * session_ptr, int64_t offset, int64_t num_bytes, const author_t * author_ptr);
int ins(session_t * session_ptr, int64_t offset, int64_t num_bytes, uint8_t fill, const author_t * author_ptr);

size_t num_changes(const session_t * session_ptr);
size_t num_changes_by_author(const session_t * session_ptr, const author_t *author_ptr);

int64_t get_computed_file_size(const session_t * session_ptr);
int64_t offset_to_computed_offset(const session_t * session_ptr, int64_t offset);
int64_t computed_offset_to_offset(const session_t * session_ptr, int64_t offset);
int save(const session_t * session_ptr, FILE * file_ptr);

// Returns the author's name from the given author structure
const char * get_author_name(const author_t * author_ptr);

// Populate viewport at the given offset (return 0 on success, non-zero otherwise)
int set_vpt(session_t * session_ptr, viewport_t * viewport_ptr, int64_t offset);
int get_vpt(const session_t * session_ptr, viewport_t * viewport_ptr, uint8_t ** data, int32_t * length);

// Undo the last change for this author from the given session (return 0 on success, non-zero otherwise)
int undo(session_t * session_ptr, const author_t * author_ptr);

// Save the given session to the given file (return 0 on success, non-zero otherwise)
int save(const session_t * session_ptr, FILE * file_ptr);

int write_segment(FILE *from_file_ptr, int64_t offset, int64_t byte_count, FILE *to_file_ptr);

#endif //OMEGA_OMEGA_EDIT_H
