#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

char *parse_separators(char *separators, size_t *seps_size) {
	size_t cur = 0;
	size_t index = 0;
	char *seps_array = malloc(sizeof(char)*strlen(separators)); // max number of seps is the length of the string if there are no escape chars
	while (separators[cur] != '\0') {
		if (separators[cur] != '\\') {
			seps_array[index] = separators[cur];
			index++;
			cur++;
		}
		else { // backslash case
			cur++;
			seps_array[index] = parse_escape(separators[cur]);
			index++;
			cur++;
		}
	}
	*seps_size = index;
	return seps_array;
}

char parse_escape(char second_char) {
	// parses the second character of a two-char escape code starting with a backslash required for assignment
	switch(second_char) {
		case 'n':
			return '\n';
		case 't':
			return '\t';
		case 'v':
			return '\v';
		case 'b':
			return '\b';
		case 'r':
			return '\r';
		case 'f':
			return '\f';
		case 'a':
			return '\a';
		case '\\':
			return '\\';
		case '"':
			return '"';
		default:
			return second_char;
	}
}
