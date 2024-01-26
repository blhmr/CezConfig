#include "../include/cezconfig.h"

linetype_t cez_get_line_type(const char* line) {
	if (line[strlen(line) - 1] == '\n') {
		if (line[0] == '\n') {
			// printf("BLANK: %s", line);
			return CEZ_BLANK;
		}
		else if (line[0] == '#') {
			// printf("COMMENT: %s", line);
			return CEZ_COMMENT;
		}
		else {
			// KEY-VALUE PAIR: key1=some value with space\n
			if (strchr(line, '=') != NULL) {
				char* string = strdup(line);
				char* key = strtok(string, "=");
				char* value = strtok(NULL, "\n");

				assert(key != NULL && value != NULL);
				// printf("KEY: %s - VALUE: %s\n", key, value);

				if (strchr(key, ' ') != NULL) {
					// printf("INVALID KEY-VALUE SYNTAX\n");
					free(string);
					return CEZ_UNKNOWN;
				}
				else {
					// printf("VALID KEY-VALUE SYNTAX\n");
					free(string);
					return CEZ_KEY_VALUE_PAIR;
				}

			}
		}
	}
	else {
		return CEZ_UNKNOWN;
	}
}

int cez_open(cezfile_t* cezfile, const char* filename) {
	strcpy(cezfile->filename, filename);

	cezfile->file = fopen(filename, "w+");
	if (cezfile->file == NULL) return -1;

	char line[CEZ_MAX_LEN_LINE + 1];

	size_t counter = 0;
	while (fgets(line, sizeof(line), cezfile->file) != NULL) {
		if (cez_get_line_type(line) != CEZ_UNKNOWN) counter++;
		else {
			fprintf(stderr, "ERROR SYNTAX AT LINE %zu => %s", counter, line);
			return -1;
		}
	}

    rewind(cezfile->file);
	return 0;
}

int cez_close(cezfile_t* cezfile) {
	if (cezfile->file == NULL) return -1;
	else {
		fclose(cezfile->file);
		cezfile->filename[0] = '\0';
		cezfile->properties_num = 0;
		return 0;
	}
}

int cez_insert(cezfile_t* cezfile, const char* key, const char* value) {
	if (cez_key_exist(cezfile, key) == false) {
		assert(key != NULL && value != NULL);
		if (strchr(key, ' ') != NULL) return -2;
		fseek(cezfile->file, 0, SEEK_END);
		fprintf(cezfile->file, "%s=%s\n", key, value);
		cezfile->properties_num++;
		fflush(cezfile->file);
		return 0;
	}
	else return -1;
}

bool cez_key_exist(cezfile_t* cezfile, const char* key) {
	bool flag = false;
	char line[CEZ_MAX_LEN_LINE + 1];
	size_t key_len = strlen(key);
	rewind(cezfile->file);

	while (fgets(line, sizeof(line), cezfile->file) != NULL) {
		if (!strncmp(key, line, key_len)) {
			flag = true;
			break;
		}
	}

	return flag;
}

int64_t cez_get_line(cezfile_t* cezfile, const char* key) {
	if (cez_key_exist(cezfile, key)) {
		char line[CEZ_MAX_LEN_LINE + 1];
		size_t key_len = strlen(key);
		int64_t counter = 1;

		rewind(cezfile->file);

		while (fgets(line, sizeof(line), cezfile->file) != NULL) {
			if (!strncmp(key, line, key_len)) break;
			else counter++;
		}

		return counter;
	}
	else return -1;
}

char* cez_get_value(cezfile_t* cezfile, const char* key) {
	if (cez_key_exist(cezfile,  key) == true) {
		size_t line_num = cez_get_line(cezfile, key);
		char line[CEZ_MAX_LEN_LINE + 1];
		
		rewind(cezfile->file);

		for (int i = 0; i < line_num; i++) {
			fgets(line, sizeof(line), cezfile->file);
		}
	
		char key[CEZ_MAX_LEN_KEY + 1];
		char* value = malloc(CEZ_MAX_LEN_VALUE + 1);

		sscanf(line, "%[^=]=%[^\n]", key, value);

		return value;
	}
	else return NULL;
}

int cez_update(cezfile_t* cezfile, const char* key, const char* new_value) {
	if (cez_key_exist(cezfile, key) == true) {
		assert(key != NULL && new_value != NULL);
		FILE* temp_file = fopen("temp____", "w+");
		char buffer[CEZ_MAX_LEN_LINE];
		size_t key_len = strlen(key);

		if (temp_file == NULL) {
			perror("Error opening file");
			return -2;
		}

		rewind(cezfile->file);

		while (fgets(buffer, sizeof(buffer), cezfile->file) != NULL) {
			if (!strncmp(key, buffer, key_len)) {
				fprintf(temp_file, "%s=%s\n", key, new_value);
			}
			else fprintf(temp_file, buffer);
		}

		remove(cezfile->filename);
		rename("temp____", cezfile->filename);
		cezfile->file = (FILE*) temp_file;
		return 0;
	}
	else return -1;
}

int cez_delete(cezfile_t* cezfile, const char* key) {
	if (cez_key_exist(cezfile, key) == true) {
		assert(key != NULL);
		FILE* temp_file = fopen("temp____", "w+");
		char buffer[CEZ_MAX_LEN_LINE];
		size_t key_len = strlen(key);

		if (temp_file == NULL) {
			perror("Error opening file");
			return -2;
		}

		rewind(cezfile->file);

		while (fgets(buffer, sizeof(buffer), cezfile->file) != NULL) {
			if (!strncmp(key, buffer, key_len)) {
				continue;
			}
			else fprintf(temp_file, buffer);
		}

		remove(cezfile->filename);
		rename("temp____", cezfile->filename);
		cezfile->file = (FILE*) temp_file;
		return 0;
	}
	else return -1;
}
