#include <stdio.h>
#include <cezconfig.h>

#define CEZ_MAX_LEN_KEY 50
#define CEZ_MAX_LEN_VALUE 50

int main(void) {
	cezfile_t file;
	cez_open(&file, "./info.cez"); // => open/create CEZ file

	// Insert key-value pairs
	cez_insert(&file, "name", "hatim");
	cez_insert(&file, "country", "morocco");
	cez_insert(&file, "age", "17"); // You have to handle type casting yourself

	cez_insert(&file, "city", "unkown");

	char* name = cez_get_value(&file, "name");

	if (name != NULL) {
		printf("Name: %s\n", name); // => "hatim"
		free(name);
	}

	// Updating
	cez_update(&file, "age", "18");

	// Deleting
	cez_delete(&file, "name");

	cez_close(&file);
}
