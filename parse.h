#ifndef PARSE_h
#define PARSE_h
char *parse_separators(char *separators, size_t *seps_size);
char *parse_text(char *text, char *separators, size_t seps_size, size_t *text_size);
char *parse_new_token(char *text, size_t start, size_t end);
char parse_escape(char second_char);
char *unparse_escape(char escape);
int check_escape(char escape);
int check_separators(char *separators, size_t seps_size, char c);

#endif
