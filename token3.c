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
#include <stdbool.h>
#include <string.h>

// Function to check if a character is a quote
bool is_quote(char c) {
    return (c == '"' || c == '\'');
}

// Function to check if the command is valid
bool is_valid_command(const char *command) {
    size_t length = strlen(command);
    bool in_quotes = false; // Track whether we are inside quotes

    // Check if the command starts with a pipe
    if (length > 0 && command[0] == '|') {
        return false; // Invalid if it starts with |
    }

    // Check if the command ends with a pipe
    if (length > 0 && command[length - 1] == '|') {
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
            if (i + 1 < length && command[i + 1] == '|') {
                return false; // Invalid if there are two pipes together
            }
        }
    }

    return true; // The command is valid
}

int main() {
    const char *commands[] = {
        "| ls",
        "ls |",
        "ls | ls",
        "ls '||' | ls",
        "ls || ls",
        "ls | | ls",
        "ls '|| ls'",
        "ls | "||"",
        "ls | '|' | ls",
        "ls '' | ls"
    };

    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        if (is_valid_command(commands[i])) {
            printf("Valid command: '%s'\n", commands[i]);
        } else {
            printf("Invalid command: '%s'\n", commands[i]);
        }
    }

    return 0;
}
