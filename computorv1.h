#ifndef COMPUTORV1
#define COMPUTORV1

#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>
#include <stdio.h>

typedef struct s_term {
	char *str;
	double coef;
	int exponent;
	struct s_term *next;
} Term;

typedef struct s_data {
	Term *left;
	Term *right;
} Data;

// MAIN
void print_array(char **arr);

// TERM
Term *get_tail(Term *list);
Term *create_node(void);
void add_node(Term **list, Term *node);
void free_list(Term *list);
void print_node(Term *node);
void printTerm(Term *list);
void print_list(Term *list);
void fill_term(Term *term);
void remove_node(Term **list, Term *node);
Term *get_node(Term *list, size_t exponent);
void free_node(Term *node);
size_t get_size(Term *list);

// UTILS
void ft_putstr(char *str);
size_t ft_strlen(char *str);
char *ft_strstr(char *fullstr, char *substr);
char *ft_strchr(char *str, int c);
int ft_isblank(int c);
void free_array(char **array);
char **ft_split(char *str, int sep);
char *ft_substr(char *str, int offset, int len);
int ft_isdigit(int c);

// PARSE
int parse(Data *data, char *str);

// REFACTO
void refacto(Data *data);

// SOLVE
void solve(Term *term);

#endif
