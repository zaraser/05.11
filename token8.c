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

typedef enum {
    T_WORD,
    T_PIPE,
    T_PLUS,
    T_PLUS2,
    T_LESS,
    T_LESS2
} t_tokens;

typedef struct s_lexer {
    char *str;
    t_tokens token;
    int i;
    struct s_lexer *next;
    struct s_lexer *prev;
} t_lexer;

// Функция для освобождения памяти связанного списка
void free_lexer_list(t_lexer **list) {
    t_lexer *current = *list;
    t_lexer *next_node;

    while (current) {
        next_node = current->next;
        free(current->str);
        free(current);
        current = next_node;
    }
    *list = NULL;
}

// Функция для создания нового узла в списке
t_lexer *lexer_create(char *value, t_tokens token, int index) {
    t_lexer *new = (t_lexer *)malloc(sizeof(t_lexer));
    if (!new)
        return NULL;

    new->str = value;
    new->token = token;
    new->i = index;
    new->next = NULL;
    new->prev = NULL;

    return new;
}

// Функция для добавления узла в конец списка
void lexer_add_back(t_lexer **list, t_lexer *new_token) {
    if (!*list) {
        *list = new_token;
        return;
    }
    t_lexer *temp = *list;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = new_token;
    new_token->prev = temp;
}

// Функция для создания и добавления токена в список
void ft_create_lexer_list(char *value, t_tokens type, int index, t_lexer **list) {
    t_lexer *new_token = lexer_create(value, type, index);
    if (new_token) {
        lexer_add_back(list, new_token);
    }
}

// Проверка, является ли символ пробелом или управляющим символом
int ft_ifspace(char *line) {
    return (*line == ' ' || (*line >= 9 && *line <= 13));
}

// Считывание слова до первого разделителя
int ft_read_word(char *line) {
    int i = 0;
    while (line[i] && !ft_ifspace(&line[i]) && line[i] != '|' && line[i] != '>' && line[i] != '<') {
        i++;
    }
    return i;
}

// Считывание символов внутри одинарных или двойных кавычек
int ft_read_word_quote(char *line, char quote) {
    int i = 1;
    while (line[i] && line[i] != quote) {
        i++;
    }
    return (line[i] == quote) ? i + 1 : i; // Если кавычка найдена, включаем ее в длину
}

// Функция для создания подстроки
char *substr(const char *str, size_t start, size_t len) {
    size_t str_len = strlen(str);
    if (start >= str_len) return NULL;
    if (start + len > str_len) len = str_len - start;

    char *sub = (char *)malloc(len + 1);
    if (!sub) return NULL;
    strncpy(sub, str + start, len);
    sub[len] = '\0';
    return sub;
}

// Функция для разбора строки и добавления токенов в список
t_lexer *ft_read_line(char *line, t_lexer **list) {
    int index = 0;

    while (*line) {
        while (ft_ifspace(line)) line++;

        if (*line == '|') {
            ft_create_lexer_list(NULL, T_PIPE, index, list);
        } else if (*line == '>' && *(line + 1) == '>') {
            ft_create_lexer_list(NULL, T_PLUS2, index, list);
            line++;
        } else if (*line == '>' && *(line + 1) != '>') {
            ft_create_lexer_list(NULL, T_PLUS, index, list);
        } else if (*line == '<' && *(line + 1) == '<') {
            ft_create_lexer_list(NULL, T_LESS2, index, list);
            line++;
        } else if (*line == '<' && *(line + 1) != '<') {
            ft_create_lexer_list(NULL, T_LESS, index, list);
        } else if (*line == '\'' || *line == '"') {
            char quote = *line;
            int len = ft_read_word_quote(line, quote);
            char *word = substr(line, 0, len);  // сохраняем кавычки
            ft_create_lexer_list(word, T_WORD, index, list);
            line += len - 1;
        } else {
            int len = ft_read_word(line);
            char *word = substr(line, 0, len);
            ft_create_lexer_list(word, T_WORD, index, list);
            line += len - 1;
        }
        line++;
        index++;
    }
    return *list;
}

// Функция для вывода токенов (для отладки)
void print_tokens(t_lexer *list) {
    while (list) {
        printf("Index: %d, Type: %d, Value: %s\n", list->i, list->token, list->str ? list->str : "NULL");
        list = list->next;
    }
}

// Основная функция
int main() {
    char input[] = "echo 'hello world' | grep \"pattern\" > output.txt";
    t_lexer *token_list = NULL;

    ft_read_line(input, &token_list);  // Токенизация строки
    print_tokens(token_list);          // Вывод токенов (если требуется)

    free_lexer_list(&token_list);      // Освобождение памяти
    return 0;
}
