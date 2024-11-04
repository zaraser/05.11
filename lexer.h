/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:42:22 by zserobia          #+#    #+#             */
/*   Updated: 2024/10/29 14:42:25 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

/*
typedef enum token
{
	WORD,
	PIPE,
	SIMPLEQUOTE,
	DOUBLEQUOTE,
	IN_REDIR, // < 
	OUT_REDIR, // >
	DELIMITER, // <<
	APPEND, // >>
	HERE_DOC,
	SPACES,
}	token;

typedef struct s_lexer
{
	char	*str;
	int		token;

}	t_lexer;*/

typedef enum e_tokens {
    WORD,
    PIPE,
    IN,
    OUT,
    APPEND,
    HEREDOC,
    INVALID
} t_tokens;

typedef struct s_lexer {
    char *str;              // Строка токена
    t_tokens token;        // Тип токена
    int i;                  // Индекс токена в строке
    struct s_lexer *next;  // Указатель на следующий токен
    struct s_lexer *prev;  // Указатель на предыдущий токен
} t_lexer;

t_lexer *make_lexer(char *input);

/*
typedef struct s_exec
{
	int	exit_status;
	
}	t_exec;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	t_list			*lst;
}					t_env;

// ENVP
void init_envp(const char **envp);
void	get_env_names_and_values(t_env *env);

// LEXER
void	minishell_loop();*/


#endif