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

char *parse_text(char *text, char *separators, size_t seps_size, size_t *text_size) {
	size_t orig_size = strlen(text);
	char *parsed_text = malloc( sizeof(char)*(orig_size+1));
	size_t p_i = 0;

	// parse two-char escape characters to single-chars
	for (size_t i = 0; i<orig_size; i++) {
		char c = text[i];
		if (c == '\\') {
			char newc = parse_escape(text[i+1]);
			if (i == orig_size-1) {
				parsed_text[p_i] = '\0';
			}

			else if (check_separators(separators, seps_size, newc) == 1) {
				parsed_text[p_i] = '\0';
				p_i++;
			}
			else {
				parsed_text[p_i] = newc;
				p_i++;
			}
			i++; // skip the '\\' as well as the next character
		}
		else {
			if (check_separators(separators, seps_size, c) == 1) {
				parsed_text[p_i] = '\0';
				p_i++;
			}
			else {
				parsed_text[p_i] = c;
				p_i++;
			}
		}
	}
	parsed_text[p_i] = '\0';
	*text_size = p_i; // eg strlen(s := "a" == ['a', '\0']) is 1, and s[1] == '\0'
	return parsed_text;
}
	
char *parse_new_token(char *text, size_t start, size_t end) {
	// parses a new token starting at start and ending at end, inclusive.
	char *token = malloc( sizeof(char)*(end-start+2) );
	for (size_t i = start; i <= end; i++) {
		// parse escape chars into [0xwhatever] here
		token[i-start] = text[i];
	}
	token[end-start+1] = '\0';
	return token;
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

char *unparse_escape(char escape) {
	char *escaped = malloc(sizeof(char)*7);
	sprintf(escaped, "[0x%02X]", escape);
	return escaped;
}

int check_escape(char escape) {
	switch(escape) {
		case '\n':
			return 1;
		case '\t':
			return 1;
		case '\v':
			return 1;
		case '\b':
			return 1;
		case '\r':
			return 1;
		case '\f':
			return 1;
		case '\a':
			return 1;
		case '\\':
			return 1;
		case '"':
			return 1;
		default:
			return 0;
	}
}
// returns one if c is a separator character, 0 otherwise
// escape characters need to be passed in as the result of parse_escape
int check_separators(char *separators, size_t seps_size, char c) {
	for (size_t i = 0; i<seps_size; i++) {
		if (separators[i] == c) {
			return 1;
		}
	}
	return 0;
}
