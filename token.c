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
/*
void	free_list(t_token **list)
{
	t_token *current;
	t_token *next_node;

	current = *list;
	while (current) {
		next_node = current->next;
		free(current->value);
		free(current);
		current = next_node;
	}
	*list = NULL;
}

t_token	*token_create(char *value, int type, int index)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = (value != NULL) ? strdup(value) : strdup("NULL");
	new->next = NULL;
	//new->prev = NULL;
	new->index = index;
	return (new);
}

void	token_add_back(t_token **list, t_token *new_token)
{
	t_token	*new;

	if (*list)
	{
		new = *list;
		while (new->next != NULL)
			new = new->next;
		new->next = new_token;
		//new_token->prev = new;
	}
	else
	{
		*list = new_token;
	}
}

int	ft_ifspace(char *line)
{
	if ((*line >= 9 && *line <= 13) || *line == ' ')
			return (1);
	return (0);
}

void	ft_create_list(char *value, int type, int index, t_token **list)
{
	t_token *new_token;

	new_token = token_create(value, type, index);
	if (new_token)
		token_add_back(list, new_token);
}

int	ft_read_word(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_ifspace(&line[i]) && line[i] != '|' && line[i] != '>' && line[i] != '<') {
		i++;
	}
	return (i);
}

int	ft_read_word_1(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != '\'')
	{
		i++;
	}
	return (i);
}

char *substr(const char *str, size_t start, size_t len)
{
	size_t str_len = ft_strlen(str);
	
	// Проверяем, что начальный индекс не выходит за границу строки
	if (start >= str_len) return NULL;
	// Корректируем длину подстроки, если она выходит за конец строки
	if (start + len > str_len)
	{
		len = str_len - start;
	}
	// Выделяем память для подстроки + 1 для нуль-терминатора
	char *sub = malloc(len + 1);
	if (!sub) return NULL;
	// Копируем подстроку и добавляем нуль-терминатор
	strncpy(sub, str + start, len);
	sub[len] = '\0';
	return sub;
}
t_token *ft_read_line(char *line, t_token **list)
{
	int	index;

	index = 0;
	while(*line)
	{
		while (ft_ifspace(line))
			line++;
		if (*line == '|')
			ft_create_list(NULL, T_PIPE, index, list);
		else if (*line == '>' && *(line + 1) == '>')
		{
			ft_create_list(NULL, T_PLUS2, index, list);
			line++;
		}
		else if (*line == '>' && *(line + 1) != '>')
			ft_create_list(NULL, T_PLUS, index, list);
		else if (*line == '<' && *(line + 1) == '<')
		{
			ft_create_list(NULL, T_LESS2, index, list);
			line++;
		}
		else if (*line == '<' && *(line + 1) != '<')
			ft_create_list(NULL, T_LESS, index, list);
		else if (*line == '/'')
		{
			int c = ft_read_word_1(line, '/'');
			char *word = substr(line, 0, c);
			ft_create_list(word, T_WORD, index, list);
			line += c - 1;
		}
		else if
		{
			int c = ft_read_word(line);
			char *word = substr(line, 0, c);
			ft_create_list(word, T_WORD, index, list);
			line += c - 1;
		}
		line++;
		index++;
	}
	return (*list);
}

int	ft_check_quote(char *list)
{
	char *temp;

	temp = list;
	while(*temp)
	{
		while (*temp != "\"" && *temp != '\'')
			temp++;
		if (temp == "\"")
		{
			while (*temp && *temp != "\"")
				temp++;
			if (*temp !=  "\"")
				return (1);
		}
		if (temp == "\'")
		{
			while (*temp && *temp != "\'")
				temp++;
			if (*temp !=  "\'")
				return (1);
		}
return (0);
}

#include <stdbool.h>

int ft_check_quote(char *list)
{
    char *temp = list;
    bool single_quote = false;
    bool double_quote = false;

    while (*temp)
    {
        // Check for single quotes
        if (*temp == '\'')
        {
            single_quote = !single_quote;  // Toggle the state of single_quote
        }
        // Check for double quotes
        else if (*temp == '\"')
        {
            double_quote = !double_quote;   // Toggle the state of double_quote
        }
        temp++; // Move to the next character
    }

    // If either single or double quotes are still open, return 1 (error)
    if (single_quote || double_quote)
        return 1;

    return 0; // Quotes are balanced
}*/

size_t ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (!str[i])
		return (i);
	while(str[i])
		i++;
	return (i);
}
void ft_exit(char *message, int status)
{
	if (status)
	{
		printf("%s\n", message);
		exit(status);
	}
	exit(status);
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

void ft_check_line2(char **line, char **new_line, char *quote) {
    int i = 0;
	int j = 0;
    *quote = '\0';

    // Skip initial control characters (28)
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
		if ((*line)[i])
			(*new_line)[j++] = ' ';
    }
    (*new_line)[j] = '\0'; // Null-terminate the new line
}


/*void ft_check_line(char **line)
{
    char *new_line;
    char quote;

    new_line = (char *)malloc(sizeof(char) * ft_strlen(*line) + 1); // Выделяем память для новой строки
    if (!new_line) // Проверка успешности выделения
        ft_exit("malloc failed", 1); // Обработка ошибки
	ft_check_line2(line, &new_line, &quote);
	free(*line);
	if (quote != '\0')
	{
		free(new_line);
		*line = NULL;
	}
	else
	{
		*line = new_line;
		free(new_line);
	}
}*/

void ft_check_line(char **line)
{
    char *new_line;
    char quote;

    new_line = (char *)malloc(sizeof(char) * (ft_strlen(*line) + 1)); // Proper allocation
    if (!new_line) // Check memory allocation
        ft_exit("malloc failed", 1); // Handle malloc failure

    ft_check_line2(line, &new_line, &quote);
	free(*line);
    
    if (quote != '\0') // If there's an unmatched quote
    {
        free(new_line); // Just free new_line
        *line = NULL; // Set line to NULL
		ft_exit("invalide quote", 1);
    }
    else
        *line = new_line; 
}



int main(int argc, char **argv) {
    char *line;

    line = malloc(100); // Allocate space for the input
    line = readline("Minishell$ ");
    if (!line)
        return 0;

    ft_check_line(&line); // Process the line
    if (line == NULL || *line == '\0') {
        free(line); // Free the allocated line if NULL
        return 0;
    }

    free(line); // Free the allocated memory
    return 0;
}

/*int	main(int argc, char **argv, char **envp)
{
	char *line;
	printf("1");
	//t_token *list = NULL;

	line = readline("Minishell$ ");
	if (!line) 
	{
		perror("Error reading line");
		return 1;
	}
	line = "Hello world | you are >>the best < merci";
	printf("1  %s", line);
	ft_check_line(?line);
	if (line == NULL|| *line == '\0')
		return (0);
	//add_history(line);
	
	//printf("%s", line);
	if (ft_check_quote)
		return ...;
	ft_read_line(line, &list);
	t_token *current = list; // Временный указатель для итерации
	while (current) {
		printf("Value - %s, type - %d, index - %d\n", current->value, current->type, current->index);
		current = current->next; // Переход к следующему токену
	}
	free_list(&list);
	return 0;
}*/
