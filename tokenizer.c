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

struct TokenizerT_ {
	char *separators; // array of characters i.e. ["\n", "\t", "a"...] stored as chars
	char *text; // text to tokenize
	char **tokenized; // array of tokens
	size_t seps_size;
	size_t text_size;
	size_t tokens_size;
};

typedef struct TokenizerT_ TokenizerT; // this can actually be on one line like typedef struct TokenizerT_ { ...} TokenizerT;

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

	tk->text = malloc(sizeof(char)*strlen(ts)+1);
	strcpy(tk->text, ts);
	tk->text_size = strlen(ts);
	tk->text[tk->text_size] = '\0';

	tk->tokenized = malloc(sizeof(char*)*(tk->text_size)); // max number of tokens is order number of characters in text
	tk->tokens_size = tk->text_size;					   // so I might as well overallocate and then resize once i'm done

	for (size_t i = 0; i < tk->tokens_size; i++) {
		tk->tokenized[i] = NULL;
	}

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
	free(tk->text);
	for (size_t i = 0; i < tk->tokens_size; i++) {
		if (tk->tokenized[i] != NULL) {
			free(tk->tokenized[i]);
		}
	}
	free(tk->tokenized);
	free(tk);
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
	// check argv for errors

	TokenizerT *tk = TKCreate(argv[1], argv[2]);


	TKDestroy(tk);

  return 0;
}
