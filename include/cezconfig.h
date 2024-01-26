#ifndef __CEZCONFIG_H__
#define __CEZCONFIG_H__

#ifndef CEZ_MAX_LEN_KEY
    #define CEZ_MAX_LEN_KEY 50
#endif

#ifndef CEZ_MAX_LEN_VALUE
    #define CEZ_MAX_LEN_VALUE 50
#endif

#define CEZ_MAX_LEN_LINE (CEZ_MAX_LEN_KEY + CEZ_MAX_LEN_VALUE + 1)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

typedef enum {
	CEZ_COMMENT = 0, // Line is a comment
	CEZ_KEY_VALUE_PAIR = 1, // Line is a key-value pair
	CEZ_UNKNOWN = -1, // Unknown => error
	CEZ_BLANK = 2// Nothing || blank
} linetype_t;

linetype_t cez_get_line_type(const char* line); // Get the type of a line

typedef struct __attribute__((packed)) {
	char key[CEZ_MAX_LEN_KEY + 1];
	char value[CEZ_MAX_LEN_VALUE + 1];
} cezpair_t;

void cez_pair_create(cezpair_t* pair, const char* key, const char* value); // Initialize a CEZ cezpair_t struct

typedef struct __attribute__((packed)) {
	FILE* file;
	char filename[30];
	size_t properties_num;
} cezfile_t;

/* DONE */
int cez_open(cezfile_t* cezfile, const char* filename);// Open a CEZ configuration file and return a cezfile_t structure
int cez_close(cezfile_t* cezfile); // Close a CEZ configuration file
int64_t cez_get_line(cezfile_t* cezfile, const char* key); // Ket the line of a configuration file in a CEZ file
bool cez_key_exist(cezfile_t* cezfile, const char* key); // Check if the key exists (really helpful)
int cez_insert(cezfile_t* cezfile, const char* key, const char* value); // Insert a configuration key with value into the CEZ file
char* cez_get_value(cezfile_t* cezfile, const char* key); // Get the value of a configuration key
int cez_update(cezfile_t* cezfile, const char* key, const char* new_value); // Update a configuration key with value into the CEZ file
int cez_delete(cezfile_t* cezfile, const char* key); // Delete a configuration key from the CEZ file

/* UNDONE */

/* IN PROGRESS */

// None at the moment...

/* --- Functions using cezpair_t (Undone) ---*/
int cez_insert_p(cezfile_t* cezfile, cezpair_t* pair); // Insert a configuration key using the cezpair_t struct into the CEZ file
int cez_update_p(cezfile_t* cezfile, cezpair_t* pair); // Update a configuration key using the cezpair_t struct into the CEZ file

#endif

