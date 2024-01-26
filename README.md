# CezConfig Library [⚙️]

CezConfig is a lightweight C library designed for parsing configuration files. It provides basic functions for opening, closing, reading, and manipulating configuration files using a key-value pair format.

## Use case
This library is for personal use, therefore it lacks some features other configuration files have, so keep your expectations low.
Example of usage: consider the following folder scheme

```
school/
├── class-1/
│   ├── student-1/
│   │   ├── history.txt
│   │   ├── grades/
│   │   └── information.cez <- Informations about the student
│   ├── student-2/
│   │   ├── history.txt
│   │   ├── grades/
│   │   └── information.cez
```

## Example
Go to the examples directory to see how the functions work.
This is a `.cez` file:
```ini
# This is a comment

key1=value1
key2=value2
```

## Installation (Unix)

```bash
git clone https://github.com/blhmr/CezConfig.git
cd CezConfig

# TO INSTALL
make install

# You can compile the example code in examples directory

# TO DELETE FROM YOUR SYSTEM
make uninstall
```

## Constants

- `CEZ_MAX_LEN_KEY`: Maximum length for a configuration key.
- `CEZ_MAX_LEN_VALUE`: Maximum length for a configuration value.
- `CEZ_MAX_LEN_LINE`: Maximum length for a configuration line (key + value + 1).

## Enums

- `linetype_t`: Enumerates different types of lines in a configuration file.
  - `CEZ_COMMENT`: Line is a comment.
  - `CEZ_KEY_VALUE_PAIR`: Line is a key-value pair.
  - `CEZ_UNKNOWN`: Unknown line type (error).
  - `CEZ_BLANK`: Blank line.

## Structs

- `cezpair_t`: Represents a key-value pair in the configuration file.
- `cezfile_t`: Represents a configuration file, including the file pointer, filename, and the number of properties.

## Functions

### File Operations

- `cez_open(cezfile_t* cezfile, const char* filename)`: Open a CEZ configuration file and return a `cezfile_t` structure.
- `cez_close(cezfile_t* cezfile)`: Close a CEZ configuration file.

### Line Operations

- `cez_get_line(cezfile_t* cezfile, const char* key)`: Get the line number of a configuration file based on the key.
- `cez_key_exist(cezfile_t* cezfile, const char* key)`: Check if a key exists in the configuration file.

### Data Operations

- `cez_insert(cezfile_t* cezfile, const char* key, const char* value)`: Insert a configuration key with a value into the CEZ file.
- `cez_get_value(cezfile_t* cezfile, const char* key)`: Get the value of a configuration key.
- `cez_update(cezfile_t* cezfile, const char* key, const char* new_value)`: Update a configuration key with a new value.
- `cez_delete(cezfile_t* cezfile, const char* key)`: Delete a configuration key from the CEZ file.

### Undone and In Progress

- Functions using `cezpair_t` are currently undone.
- No functions are in progress at the moment.

## License

This library is provided under the [MIT License](LICENSE). Feel free to use and modify it in your projects.

