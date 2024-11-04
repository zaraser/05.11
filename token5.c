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
#include <stdbool.h>*/
#include "lexer.h"

/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
} t_lexer;*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

// Функция для создания новой лексемы
t_lexer *lexer_new(char *str, t_tokens token) {
    t_lexer *new_lexer = malloc(sizeof(t_lexer));
    if (!new_lexer) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_lexer->str = str; // Сохраняем строку
    new_lexer->token = token; // Сохраняем тип токена
    new_lexer->i = 0; // Индекс токена
    new_lexer->next = NULL; // Указатель на следующий токен
    new_lexer->prev = NULL; // Указатель на предыдущий токен
    return new_lexer;
}

// Функция для добавления лексемы в список
void lexer_add_back(t_lexer **lexer_list, t_lexer *new_lexer) {
    t_lexer *temp = *lexer_list;
    if (!temp) {
        *lexer_list = new_lexer; // Если список пуст, просто добавляем новый элемент
        return;
    }
    while (temp->next) // Перебираем до конца списка
        temp = temp->next;
    temp->next = new_lexer; // Добавляем новый элемент в конец
    new_lexer->prev = temp; // Устанавливаем указатель на предыдущий элемент
}

// Функция для создания лексера из входной строки
t_lexer *make_lexer(char *input) {
    t_lexer *lexer = NULL; // Инициализация списка лексем
    int start = 0;        // Начальный индекс
    size_t length = strlen(input);

    while (start < length) {
        // Пропускаем пробелы
        while (start < length && (input[start] == ' ' || input[start] == '\t' || input[start] == '\n')) {
            start++;
        }
        if (start >= length) break; // Если достигли конца строки, выходим из цикла

        // Обрабатываем кавычки
        char quote = '\0'; // Флаг для отслеживания кавычек
        int word_start = start; // Начало слова
        if (input[start] == '"' || input[start] == '\'') {
            quote = input[start]; // Определяем тип кавычек
            start++; // Переходим на следующий символ
            word_start = start; // Начинаем запись слова сразу после кавычек

            // Ищем конец кавычек
            while (start < length && input[start] != quote) {
                start++;
            }

            // Если кавычки не закрыты, считаем это ошибкой (можно обработать по-разному)
            if (start >= length) {
                fprintf(stderr, "Error: unmatched quote\n");
                return NULL; // Или обработать по-другому
            }

            // Создаем токен для слова с кавычками
            char *word = strndup(&input[word_start], start - word_start);
            lexer_add_back(&lexer, lexer_new(word, WORD));
            start++; // Переходим на следующий символ после закрывающей кавычки
            continue;
        }

        // Если нашли специальный символ
        if (input[start] == '|') {
            lexer_add_back(&lexer, lexer_new(strdup("|"), PIPE));
            start++;
            continue;
        } else if (input[start] == '>') {
            if (input[start + 1] == '>') {
                lexer_add_back(&lexer, lexer_new(strdup(">>"), APPEND));
                start += 2;
            } else {
                lexer_add_back(&lexer, lexer_new(strdup(">"), OUT));
                start++;
            }
            continue;
        } else if (input[start] == '<') {
            if (input[start + 1] == '<') {
                lexer_add_back(&lexer, lexer_new(strdup("<<"), HEREDOC));
                start += 2;
            } else {
                lexer_add_back(&lexer, lexer_new(strdup("<"), IN));
                start++;
            }
            continue;
        }

        // Обрабатываем слово
        int word_start = start;
        while (start < length && input[start] != ' ' && input[start] != '|' &&
               input[start] != '>' && input[start] != '<') {
            start++;
        }
        
        // Сохраняем слово как токен
        if (start > word_start) {
            char *word = strndup(&input[word_start], start - word_start);
            lexer_add_back(&lexer, lexer_new(word, WORD));
        }
    }

    return lexer; // Возвращаем список лексем
}

// Пример использования
int main(int argc, char **argv) {
    char *line = "echo \"hello world\" | grep 'pattern' > output.txt";
    t_lexer *lexer = make_lexer(line);

    // Печать токенов
    t_lexer *temp = lexer;
    while (temp) {
        printf("Token: '%s', Type: %d\n", temp->str, temp->token);
        temp = temp->next;
    }

    // Освобождение памяти
    temp = lexer;
    while (temp) {
        t_lexer *next = temp->next;
        free(temp->str); // Освобождаем строку токена
        free(temp);      // Освобождаем лексему
        temp = next;
    }

    return 0;
}



