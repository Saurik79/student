#include <stdio.h>
#include <stdlib.h>

typedef struct tag_symbol_list {
	int data;
	struct tag_symbol_list *next;
} symbol_list;

typedef struct tag_word_list {
	symbol_list *symbols;
	struct tag_word_list *next;
} word_list;

symbol_list *create_symb_list (int *c) {	
	
	static int check = 0;
	symbol_list *tmp;
	
	*c = getchar();
	if ((*c == EOF) || (*c == '\n') || ((*c == ' ') && (!check))) {
		return NULL;
	}
	if (*c == '"') { 
		check =! check;
		tmp = create_symb_list(c);
		return tmp; 												   	
	} else {
		tmp = malloc(sizeof(symbol_list));
		tmp->data = *c;
		tmp->next = create_symb_list(c);
		return tmp;
	}	
}

word_list *create_word_list(int *c) {	
	
	word_list *tmp; 

	if ((*c == EOF) || (*c == '\n')) 
		return NULL;
	tmp = malloc(sizeof(word_list));
	tmp->symbols = create_symb_list(c);
	tmp->next = create_word_list(c);
	return tmp; 
}

void print_symbol_list(const symbol_list *pointer) {
	
	if (pointer) {					                          
		printf("%c", pointer->data);
		print_symbol_list(pointer->next);
	}
}

void print_word_list(const word_list *pointer) {
	
	if (pointer) {
		symbol_list *pointer_symbol = pointer->symbols; 
		print_symbol_list(pointer_symbol);
		printf("\n");
		print_word_list(pointer->next);
	}	
}

void clean_symbol_list(symbol_list *pointer) {
	
	if (!pointer) {
		return;
	}
	symbol_list *tmp = pointer->next;
	free(pointer);
	if (tmp) {
		clean_symbol_list(tmp);
	} 
}

void clean_word_list(word_list *pointer) {
	
	if (!pointer){ 
		return; 
	}
	word_list *tmp = pointer->next;
	clean_symbol_list(pointer->symbols);
	free(pointer);
	if (tmp) { 
		clean_word_list(tmp);
	}
}

void shell_step_one(int *c) {
	
	word_list *words;
	
	printf("Enter your string:\n");
	words = create_word_list(c);
	printf("Your words:\n");
	print_word_list(words);
	clean_word_list(words);
	if (*c != EOF) {
		*c = '+';
		shell_step_one(c);
	}
}

int main()
{
	int c;
	shell_step_one(&c);
	return 0;
}

