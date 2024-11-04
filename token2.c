/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zserobia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:40:48 by zserobia          #+#    #+#             */
/*   Updated: 2024/10/29 14:40:51 by zserobia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>  // Make sure to include readline library*/

#include <stdbool.h>
#include "lexer.h"

// Function to check if a character is a quote
bool is_quote(char c) {
    return (c == '"' || c == '\'');
}

// Function to check if the command is valid
bool is_valid_line(const char *command) {
    size_t length = strlen(command);
    bool in_quotes = false; // Track whether we are inside quotes

    // Check if the command ends with a pipe
    if (length > 0 && command[length - 1] == '|') {
        printf("bash: syntax error near unexpected token `|'\n");
        return false; // Invalid if it ends with |
    }

    // Check for consecutive pipes
    for (size_t i = 0; i < length; i++) {
        // Toggle the in_quotes flag when encountering quotes
        if (is_quote(command[i])) {
            in_quotes = !in_quotes; // Toggle the quote state
        }

        // If we are not inside quotes, check for consecutive pipes
        if (!in_quotes && command[i] == '|') {
            // If the next character is also a pipe, return false
            if (i + 2 < length && command[i + 2] == '|') 
            {
                printf("bash: syntax error near unexpected token `||'\n");
                return false; // Invalid if there are two pipes together
            }
        }
            // Check if the command starts with a pipe
        if (length > 0 && command[0] == '|')
        {
            printf("bash: syntax error near unexpected token `|'\n");
            return false; // Invalid if it starts with |
         }
    }

    return true; // The command is valid
}

size_t ft_strlen(const char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return i;
}

void ft_exit(char *message, int status)
{
    if (status)
    {
        printf("%s\n", message);
        exit(status);
    }
}

int ft_is_quote(char c)
{
    return (c == '"' || c == '\'');
}

void ft_turn_quote(char **line, int i, char *quote)
{
    if (*quote == '\0' && ft_is_quote((*line)[i]))
        *quote = (*line)[i];
    else if (*quote == (*line)[i])
        *quote = '\0';
}

int ft_is_space(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

/*void ft_check_line2(char **line, char **new_line, char *quote) {
    int i = 0, j = 0;
    *quote = '\0';

    // Skip initial space characters
    while ((*line)[i] && ft_is_space((*line)[i]))
        i++;

    while ((*line)[i])
    {
        // Handle the part of the line outside quotes
        while ((*line)[i] && (!ft_is_space((*line)[i]) || *quote)) 
        {
            ft_turn_quote(line, i, quote);
            (*new_line)[j++] = (*line)[i++];
        }
        while ((*line)[i] && ft_is_space((*line)[i]))
            i++;
        if ((*line)[i])  // Fixed the invalid read issue
            (*new_line)[j++] = ' ';
    }
    (*new_line)[j] = '\0'; // Null-terminate the new line
}*/


void ft_check_line2(char **line, char **new_line, char *quote) {
    int i = 0, j = 0;
    *quote = '\0';

    // Пропускаем начальные пробелы
    while ((*line)[i] && ft_is_space((*line)[i]))
        i++;

    while ((*line)[i]) {
        // Обрабатываем строку, игнорируя пробелы внутри кавычек
        while ((*line)[i] && (!ft_is_space((*line)[i]) || *quote)) {
            ft_turn_quote(line, i, quote);

            // Если не внутри кавычек и символ специальный, добавляем пробелы вокруг
            if ((*quote == '\0') && ((*line)[i] == '|' || (*line)[i] == '>' || (*line)[i] == '<')) 
            {
                if (j > 0 && (*new_line)[j - 1] != 'A')
                    (*new_line)[j++] = 'A';
                if (((*line)[i] == '>' && (*line)[i + 1] == '>') || ((*line)[i] == '<' && (*line)[i + 1] == '<'))
                    (*new_line)[j++] = (*line)[i++];
                (*new_line)[j++] = (*line)[i++];
               // add_spaces_around_specials(new_line, &j, (*line)[i++]);
                break;
            } else {
                // Копируем обычный символ без изменений
                (*new_line)[j++] = (*line)[i++];
            }
        }

        // Пропускаем дополнительные пробелы между словами или символами
        while ((*line)[i] && ft_is_space((*line)[i]))
            i++;

        // Добавляем пробел только если есть еще символы для обработки, чтобы избежать лишнего пробела в конце
        if ((*line)[i] && j > 0 && (*new_line)[j - 1] != ' ')
            (*new_line)[j++] = 'A';
    }
     (*new_line)[j] = '\0';
}

void ft_check_line(char **line)
{
    char *new_line;
    char quote;

    new_line = (char *)malloc(sizeof(char) * (ft_strlen(*line)* 3 + 1)); // Allocate memory
    if (!new_line) // Check memory allocation
        ft_exit("malloc failed", 1); // Handle malloc failure

    ft_check_line2(line, &new_line, &quote);
    free(*line); // Free the old line

    if (quote != '\0') // If there's an unmatched quote
    {
        free(new_line); // Free new_line
        *line = NULL; // Set line to NULL
        ft_exit("invalid quote", 1);
    }
    else
    {
        *line = new_line; // Assign new_line to line
        // Don't free new_line here again, as *line points to it now.
    }

}

int main(int argc, char **argv) {
    char *line;

    // Using readline for input
    line = readline("Minishell$ ");
  // line =  "   <<|ls|>|lsls| "|">>   ";
    if (!line)  // Check for successful line reading
        return 0;

    ft_check_line(&line); // Process the line
    if (line == NULL || *line == '\0') {
        free(line); // Free the allocated line if NULL
        return 0;
    }
    printf("%s\n", line);
    if(!is_valid_line(line))
    {
        free(line); // Free new_line
        line = NULL; // Set line to NULL
        exit(1);
    }
    t_lexer *lexer = make_lexer(line);

    // Печать токенов
    while (lexer) {
        printf("Token: '%s', Type: %d\n", lexer->str, lexer->token);
        lexer = lexer->next;
    }
   // printf("%s\n", line); // Output the processed line
    free(line); // Free the allocated memory
    return 0;
}
