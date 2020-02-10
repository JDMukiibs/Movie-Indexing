//
// Created by Lenovo on 12/20/2019.
//

#ifndef MOVIE_INDEXING_AVLTREE_H
#define MOVIE_INDEXING_AVLTREE_H

#endif //MOVIE_INDEXING_AVLTREE_H
#include "Linked_List.h"

AVLTree CreateTree(void);
AVLTree InsertElement(struct Movie_Node *, AVLTree);
AVLTree SingleRotateToRight(AVLTree);
AVLTree SingleRotateToLeft(AVLTree);
AVLTree DoubleRotateFirstLeftThenRight(AVLTree);
AVLTree DoubleRotateFirstRightThenLeft(AVLTree);
void DisplayTree(AVLTree);
int AVLTreeHeight(AVLTree);
int Max(int, int);

AVLTree CreateTree(void)
{
    return NULL;
}
int AVLTreeHeight(AVLTree t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}
AVLTree InsertElement(struct Movie_Node *new_movie, AVLTree t)
{
    if (t == NULL)
    {
        /*Create and return a one-node tree */
        t = malloc(sizeof(AVLTree));
        if (t == NULL)
            printf("Out of memory space!!!\n");
        else
        {
            t->movie = CreateList();
            addMovie(t->movie,new_movie);
            t->height = 0;
            t->left = t->right = NULL;
        }
    }
    else if (new_movie->Title < t->movie->head->Title)
    {
        t->left = InsertElement(new_movie, t->left);

        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
        {
            if (new_movie->Title < t->movie->head->Title)//left left case
                t = SingleRotateToRight(t);
            else
                t = DoubleRotateFirstLeftThenRight(t);
        }
    }
    else if (new_movie->Title > t->movie->head->Title)
    {
        t->right = InsertElement(new_movie->Title, t->right);
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
        {
            if (new_movie->Title > t->movie->head->Title)//right right case
                t = SingleRotateToLeft(t);
            else
                t = DoubleRotateFirstRightThenLeft(t);
        }
    }
    else if (strncmp(new_movie->Title,t->movie->head->next->Title,strlen(new_movie->Title))==0)
    {
        //TO BE COMPLETED!!
    }
    /* else val is in the tree already ... do nothing */
    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    return t;
}
AVLTree SingleRotateToRight(AVLTree k2)
{
    AVLTree k1;
    k1=k2->left;

    AVLTree temp;
    temp = k1->right;
    k1->right = k2;
    k2->left = temp;

    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
    return k1;
}

AVLTree SingleRotateToLeft(AVLTree k1)
{
    AVLTree k2;
    k2=k1->right;

    AVLTree temp;
    temp = k2->left;
    k2->left = k1;
    k1->right = temp;

    k2->height = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
    k1->height = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
    return k2;
}

AVLTree DoubleRotateFirstLeftThenRight(AVLTree k3)
{
    k3->left = SingleRotateToLeft(k3->left);
    return SingleRotateToRight(k3);
}

AVLTree DoubleRotateFirstRightThenLeft(AVLTree k3)
{
    k3->right = SingleRotateToRight(k3->right);
    return SingleRotateToLeft(k3);
}

int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;
}
void DisplayTree(AVLTree t)
{
    if (t != NULL)
    {
        DisplayTree(t->left);
        printf("%s\n", t->movie->head->next->Title);
        DisplayTree(t->right);
    }
}
