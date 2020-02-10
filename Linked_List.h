//
// Created by Lenovo on 12/20/2019.
//

#ifndef MOVIE_INDEXING_LINKED_LIST_H
#define MOVIE_INDEXING_LINKED_LIST_H

#endif //MOVIE_INDEXING_LINKED_LIST_H

#include <ctype.h>

struct Movie_Node{
    char *Title;
    int year;
    char *imdbID;
    char *posterLink;
    struct Movie_Node *next;
};

struct Movie_List{
    struct Movie_Node *head;
    struct Movie_Node *tail;
    int size;
};

struct AVLTreeNode{
    struct Movie_List *movie;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
    int height;
};

typedef struct AVLTreeNode *AVLTree;
typedef struct Movie_List *movie_List;

movie_List CreateList();
void MakeEmptyList(movie_List);
int IsEmptyList(movie_List);
void addMovie(movie_List, struct Movie_Node *);
void DisplayList(movie_List);

movie_List CreateList()
{
    movie_List m;

    m = malloc(sizeof(struct Movie_List));
    if (m == NULL)
        printf("Out of memory!\n");
    else
        MakeEmptyList(m);

    return m;
}
void MakeEmptyList(movie_List m)
{
    m->head = malloc(sizeof(struct Movie_Node));
    if (m->head == NULL)
        printf("Out of memory!\n");

    m->head->next = NULL;
    m->tail = m->head;
    m->size = 0;
}
void removeSpaces(char *str)
{
    // To keep track of non-space character count
    int count = 0;
    // If current character is not space, then place it at index 'count' then increment index for count.
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
        {
            str[count] = str[i];
            count++;
        }
    }
    str[count] = '\0';
}
char * ConverttoLower(char *str)
{
    int i = 0;
    while(str[i]){
        str[i] = (char) tolower(str[i]);
        i++;
    }
    return str;
}