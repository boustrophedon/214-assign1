/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

#define IN 0
#define OUT 1

struct TokenizerT_ {
	char *separators; // array of characters i.e. ["\n", "\t", "a"...] stored as chars
	char *parsed_text; // text to tokenize
	char **tokenized; // array of tokens
	size_t seps_size;
	size_t text_size;
	size_t tokens_size;
};

typedef struct TokenizerT_ TokenizerT; // this can actually be on one line like typedef struct TokenizerT_ { ...} TokenizerT;

void TKTokenizeAll(TokenizerT *tk);

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 * 
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
	TokenizerT *tk = malloc(sizeof(TokenizerT));

	tk->separators = parse_separators(separators, &(tk->seps_size));

	tk->parsed_text = parse_text(ts,tk->separators, tk->seps_size, &(tk->text_size));

	tk->tokenized = malloc(sizeof(char*)*(tk->text_size)); // max number of tokens is order number of characters in text
	tk->tokens_size = tk->text_size;					   // so I might as well overallocate and then resize once i'm done

	for (size_t i = 0; i < tk->tokens_size; i++) {
		tk->tokenized[i] = NULL;
	}
	TKTokenizeAll(tk);
	return tk;
}


/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
	free(tk->separators);
	free(tk->parsed_text);
	for (size_t i = 0; i < tk->tokens_size; i++) {
		if (tk->tokenized[i] != NULL) {
			free(tk->tokenized[i]);
		}
	}
	free(tk->tokenized);
	free(tk);
}

void TKTokenizeAll(TokenizerT *tk) {
	size_t start = 0;
	size_t cur = 0;
	size_t num_tokens = 0;

	int state = OUT;

	for (;cur < tk->text_size; cur++) {
		char c = tk->parsed_text[cur];
		if (c == '\0') {
			if (state == IN) {
				tk->tokenized[num_tokens] = parse_new_token(tk->parsed_text, start, cur);
				num_tokens++;
			}
			state = OUT;
		}
		else {
			if (state == OUT) {
				start = cur;
				state = IN;
			}
		}
	}
	if (state == IN) {
		tk->tokenized[num_tokens] = parse_new_token(tk->parsed_text, start, cur);
		num_tokens++;
	}

	tk->tokens_size = num_tokens;
	tk->tokenized = realloc(tk->tokenized, (sizeof(char*))*(tk->tokens_size));
	
	for (size_t i = 0; i < tk->tokens_size; i++) {
		char *cur_token = tk->tokenized[i];
		size_t cur_size = strlen(cur_token);
		char *new_token = malloc(sizeof(char)*(cur_size*6)+1);
		new_token[0] = '\0';

		size_t cur = 0;
		for (size_t j = 0; j < cur_size; j++) {
			char c = cur_token[j];
			if (check_escape(c) == 1) {
				char *esc = unparse_escape(c);
				strcat(new_token, esc);

				cur+=8;
				free(esc);
			}
			else {
				new_token[cur] = c;
				new_token[cur+1] = '\0';
				cur++;
			}
		}
		tk->tokenized[i] = realloc(new_token, (sizeof(char)*strlen(new_token)+1));
		free(cur_token);
	}
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

// so this is kind of dumb because now i need to keep a counter as part of the tokenizer state
// i guess it would make sense if i weren't just going to call getnexttoken until it runs out of tokens
char *TKGetNextToken(TokenizerT *tk) {
	return NULL;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	if (argc < 3) {
		printf("Too few arguments.\n");
		return -10;
	}
	else if (argc > 3) {
		printf("Too many arguments.\n");
		return -11;
	}

	TokenizerT *tk = TKCreate(argv[1], argv[2]);

	TKTokenizeAll(tk);
	for (size_t i = 0; i < tk->tokens_size; i++) {
		printf("%s\n", tk->tokenized[i]);
	}

	TKDestroy(tk);

  return 0;
}
