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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

/*typedef enum {
    T_WORD,     // Normal words
    T_PIPE,     // |
    T_PLUS,     // >
    T_LESS,     // <
    T_PLUS2,    // >>
    T_LESS2,    // <<
    T_DOLLAR,    // $
    //T_AND,      // &&
    //T_OR,       // ||
    //T_OPEN,     // (
    //T_CLOSE,    // )
    T_PARENT1,  // '
    T_PARENT2   // "
} t_tokens;*/

# define T_PIPE 1
# define T_PLUS2 2
# define T_PLUS 3
# define T_LESS2 4
# define T_LESS 5
# define T_WORD 6


typedef struct s_token
{
    char *value;
    int type;
    int index;
    struct s_token *next;
    //struct s_token *prev;
} t_token;

typedef struct s_minishell
{
    char *line;
    t_token *token_tous;
}t_minishell;

extern t_minishell global;

#endif
