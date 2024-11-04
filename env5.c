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


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Custom calloc function to allocate memory and initialize to zero
void *ft_calloc(size_t count, size_t size) {
    void *ptr = malloc(count * size);
    if (ptr) {
        memset(ptr, 0, count * size); // Initialize allocated memory to zero
    }
    return ptr;
}

// Function to count the number of words in the string based on the delimiter
size_t ft_strcount(char const *str, char c) {
    size_t len = 0;
    int in_word = 0;

    while (*str) {
        if (*str != c && !in_word) {
            in_word = 1; // We are in a word
            len++;
        } else if (*str == c) {
            in_word = 0; // We have exited a word
        }
        str++;
    }
    return len;
}

// Function to count the characters in a single word
size_t ft_charcount(char const *s, size_t i, char c) {
    size_t len = 0;

    while (s[i] && s[i] != c) {
        len++;
        i++;
    }
    return len;
}

// Function to create a substring from the original string
char *ft_substr(char const *s, unsigned int start, size_t len) {
    char *substr;
    
    if (start >= strlen(s)) {
        return NULL; // If start is beyond the string length
    }
    
    substr = malloc(len + 1); // Allocate memory for the substring
    if (!substr) {
        return NULL; // Check for malloc failure
    }
    
    strncpy(substr, s + start, len); // Copy the substring
    substr[len] = '\0'; // Null-terminate the substring
    return substr;
}

// Main split function to split the input string into commands
char **ft_split(char const *s, char c) {
    char **res;
    size_t strcount;
    size_t i = 0;
    size_t j = 0;

    if (!s) {
        return NULL; // Check for null input
    }
    
    strcount = ft_strcount(s, c); // Count the number of words
    res = (char **)ft_calloc(strcount + 1, sizeof(char *)); // Allocate memory for result
    if (!res) {
        return NULL; // Check for malloc failure
    }

    while (j < strcount) {
        while (s[i] == c) // Skip delimiters
            i++;
        if (s[i]) { // If we have reached a non-delimiter character
            res[j++] = ft_substr(s, i, ft_charcount(s, i, c)); // Get the substring
        }
        while (s[i] && s[i] != c) // Move to the next delimiter
            i++;
    }
    return res; // Return the array of commands
}

// Example usage
int main() {
    char **result = ft_split("ghghj jjj", '|');
    
    for (int i = 0; result[i] != NULL; i++) {
        printf("Command %d: '%s'\n", i, result[i]);
        free(result[i]); // Free each individual command
    }
    free(result); // Free the array itself

    return 0;
}
