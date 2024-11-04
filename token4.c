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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>  // Make sure to include readline library
#include <readline/history.h>
#include <stdbool.h>

// Function to check if a character is a quote
bool is_quote(char c) {
    return (c == '"' || c == '\'');
}

int ft_is_space(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

// Function to check if the command is valid
/*bool is_valid_line(const char *command) {
    size_t length = strlen(command);
    bool in_quotes = false; // Track whether we are inside quotes

    // Check if the command starts or ends with a pipe
    if (length > 0 && (command[0] == '|' || command[length - 1] == '|')) {
        printf("bash: syntax error near unexpected token `|'\n");
        return false; // Invalid if it starts or ends with |
    }

    for (size_t i = 0; i < length; i++) {
        if (is_quote(command[i])) {
            in_quotes = !in_quotes; // Toggle the quote state
        }

        // Check for consecutive pipes or pipes separated by only spaces
        if (!in_quotes && command[i] == '|') {
            size_t next = i + 1;
            while (next < length && ft_is_space(command[next])) {
                next++;
            }
            if (next < length && command[next] == '|') {
                printf("bash: syntax error near unexpected token `||'\n");
                return false; // Invalid if there are two pipes with no content between them
            }
        }
    }

    return true; // The command is valid
}*/

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
            if (i + 1 < length && command[i + 1] == '|')
            {
                printf("bash: syntax error near unexpected token `||'\n");
                return false; // Invalid if there are two pipes together
            }
            if (i + 2 < length && command[i + 2] == '|')
            {
                printf("bash: syntax error near unexpected token `|'\n");
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

// Utility functions for length, spaces, and quote management
size_t ft_strlen(const char *str) {
    size_t i = 0;
    while (str[i])
        i++;
    return i;
}


void ft_turn_quote(char **line, int i, char *quote) {
    if (*quote == '\0' && is_quote((*line)[i]))
        *quote = (*line)[i];
    else if (*quote == (*line)[i])
        *quote = '\0';
}

// Function to check and adjust line spacing
void ft_check_line2(char **line, char **new_line, char *quote) {
    int i = 0, j = 0;
    *quote = '\0';

    // Skip initial spaces
    while ((*line)[i] && ft_is_space((*line)[i])) {
        i++;
    }

    while ((*line)[i]) {
        // Process line ignoring spaces inside quotes
        while ((*line)[i] && (!ft_is_space((*line)[i]) || *quote)) {
            ft_turn_quote(line, i, quote);
            (*new_line)[j++] = (*line)[i++];
        }

        // Skip extra spaces between tokens
        while ((*line)[i] && ft_is_space((*line)[i])) {
            i++;
        }

        // Add a single space if there’s more content after the current token
        if ((*line)[i] && j > 0 && (*new_line)[j - 1] != ' ') {
            (*new_line)[j++] = ' ';
        }
    }
    (*new_line)[j] = '\0';
}


void ft_check_line(char **line) {
    char *new_line;
    char quote;

    new_line = (char *)malloc(sizeof(char) * (ft_strlen(*line) * 3 + 1));
    if (!new_line)
        exit(EXIT_FAILURE);

    ft_check_line2(line, &new_line, &quote);
    free(*line);

    if (quote != '\0') {
        free(new_line);
        *line = NULL;
        printf("Error: unmatched quote\n");
        exit(EXIT_FAILURE);
    } else {
        *line = new_line;
    }
}

int main() {
    char *line;

    line = readline("Minishell$ ");
    if (!line)
        return 0;

    ft_check_line(&line);
    if (line == NULL || *line == '\0') {
        free(line);
        return 0;
    }
    printf("%s\n", line);
    add_history(line);
    if (!is_valid_line(line)) {
        free(line);
        printf("Error: invalid pipe usage\n");
        exit(EXIT_FAILURE);
    }

    free(line);

    //rl_clear_history();
    return 0;
}
