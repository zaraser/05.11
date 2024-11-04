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

#include "minishell.h"

size_t ft_strlen(const char *str) {
    size_t i = 0;
    while (str[i]) i++;
    return i;
}

void ft_exit(char *message, int status) {
    if (status) {
        printf("%s\n", message);
        exit(status);
    }
}

int ft_is_quote(char c) {
    return (c == '"' || c == '\'');
}

void ft_turn_quote(char *line, int i, char *quote) {
    if (*quote == '\0' && ft_is_quote(line[i])) {
        *quote = line[i];
    } else if (*quote == line[i]) {
        *quote = '\0';
    }
}

void ft_check_line2(char *line, char *new_line, char *quote) {
    int i = 0, j = 0;
    *quote = '\0';

    // Skip initial 28 characters (if that's intended)
    while (line[i] && line[i] == 28) i++;

    while (line[i]) {
        // Skip spaces in the original line
        if (line[i] == ' ') {
            // If the last character added was not a space, add one
            if (j > 0 && new_line[j - 1] != ' ') {
                new_line[j++] = ' ';
            }
            i++; // Move past the space
            continue; // Skip to the next iteration
        }

        // Process until reaching a 28 or the quote character
        while (line[i] && (line[i] != 28 && line[i] != *quote)) {
            ft_turn_quote(line, i, quote);
            new_line[j++] = line[i++];
        }

        // If we hit a 28, we can ignore it for now
        while (line[i] && line[i] == 28) i++;
    }

    // Null-terminate the new_line string
    new_line[j] = '\0';
}

void ft_check_line(char **line) {
    char *new_line;
    char quote;

    // Allocate memory for the new line
    new_line = malloc(sizeof(char) * (ft_strlen(*line) + 1)); 
    if (!new_line) // Check memory allocation
        ft_exit("malloc failed", 1);

    ft_check_line2(*line, new_line, &quote);
    if (quote != '\0') {
        free(new_line);
        *line = NULL;
    } else {
        free(*line); // Free old line memory
        *line = new_line; // Assign new_line to line
    }
}

int main(int argc, char **argv) {
    char *line;

    line = malloc(100); // Allocate space for the input
    line = readline("Minishell$ ");
    if (!line) {
        perror("Error reading line");
        return 1;
    }

    ft_check_line(&line); // Process the line
    if (line == NULL || *line == '\0') {
        free(line); // Free the allocated line if NULL
        return 0;
    }

    printf("%s\n", line); // Output the processed line
    free(line); // Free the allocated memory
    return 0;
}
