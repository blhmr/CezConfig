#include <stdio.h>
#include <stdbool.h>

#include "include/cezconfig.h"

int main(void) {
	cezfile_t file;
	cez_open(&file, "example.cez");

	cez_delete(&file, "city");

	cez_close(&file);
	return 0;
}
