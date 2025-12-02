#ifndef COMPUTORV1
#define COMPUTORV1

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define RESET	"\033[0m"

#define MAX_SIZE 1024

typedef enum {
	END,
	INT,
	FLOAT,
	EQUAL,
	OP,
	SIGN,
	VAR,
	POW,
}	TYPE;

typedef struct s_token {
	TYPE	type;
	char	*str;
}	Token;

typedef struct s_term {
	double	coef;
	size_t	power;
}	Term;

typedef struct s_polynom {
	Term	*terms;
	size_t	size;
}	Polynom;

//Token
Token	*tokenize(char *str);

//Valid
int		valid(Token *tokens);

//Utils
size_t	ft_strlen(char *str);
void	ft_putstr(char *str);
int		ft_isdigit(int c);
int		ft_isspace(int c);
char	*ft_substr(char *str, int offset, int len);
char	*ft_strchr(char *str, int c);
void	free_all(Token *tokens, Term *l, Term *r);

//Parse
int		parse(Token *tokens, Polynom *left, Polynom *right);

//Refacto
double	*refacto(Polynom left, Polynom right, size_t *max_power);

//Solve
void	solve(double *coefs, size_t max_power);

#endif
