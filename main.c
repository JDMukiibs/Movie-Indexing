#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "AVLTree.h"

#define FALSE 0
#define TRUE 1

AVLTree read_data(AVLTree t,char *[]);
AVLTree insert_movie(AVLTree, struct Movie_Node *);
void removeSpaces(char *);//This remove spaces function will help me make better string comparisons by removing all spaces from any given strings.
char * ConverttoLower(char *);//This function will help convert the strings to lowercase that way it makes for even more efficient string comparisons.
void display_index(AVLTree);
void most_popular_year_movies(AVLTree);
void display_movies_keyword(AVLTree, char *);

int main(int argc, char *argv[])
{
    AVLTree myMovieIndex;
    int option,exit;
    char *key;

    myMovieIndex = CreateTree();
    myMovieIndex = read_data(myMovieIndex,argv);

    printf("The movies.txt file has been loaded successfully\n\n");
    exit = FALSE;

    printf(">>>Welcome to Movie Analysis at IMDB<<<\n");
    while(!exit)
    {
        fflush(stdin);
        printf("--Menu--\n");
        printf("1. Display the full index of movies\n");
        printf("2. Display the movies where their title contains a specific keyword\n");
        printf("3. Display the year with the maximum number of movies\n");
        printf("4. Exit\n");
        printf("Option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Movie Index\n");
                printf("-------------");
                display_index(myMovieIndex);
                break;
            case 2:
                printf("Enter keyword:");
                gets(key);
                display_movies_keyword(myMovieIndex, key);
                break;
            case 3:
                most_popular_year_movies(myMovieIndex);
                break;
            case 4:
                printf("\nThank you for using my Movie Index! :) \n");
                exit = TRUE;
                break;
            default:
                printf("Option key not recognized!!\n");
                break;
        }
    }
    return 0;
}

AVLTree read_data(AVLTree t, char *argument[]) {
    char filename[25];
    sscanf(argument[1],"%s",filename);

    char line[350];//When iterating through the textfile this shall help store one line worth of one song's information in the file.
    // 350 is the maximum characters that a text file can show on one line.
    FILE *inFile;
    int SIZE=0,i=0;
    // SIZE -- This variable will be used to record number of movies in the textfile
    // so that during copying to the fields we can exit the loop once the whole file is checked. i will help with loop iteration.
    inFile = fopen(filename,"r");
    while(inFile==NULL)//Checking to see if the file indeed exists and was read from.
    {
        fflush(stdin);
        printf("Error creating file!!\n");//Then asks the user to type the filename again correctly.
        printf("Enter filename correctly please: ");
        scanf("%s",filename);
        inFile = fopen(filename,"r");
    }
    while(fgets(line,350,inFile))
        SIZE++;//This helps iterate through the file to find out how many songs we will be adding to our list.

    fseek(inFile,0L,SEEK_SET);//This command will set the cursor back to the start of the file so we can now read the data into our tree.

    while((fgets(line,350,inFile)) && i<SIZE)
    {
        struct Movie_Node *movie;
        movie = (struct Movie_Node *) malloc(sizeof(struct Movie_Node));
        movie->Title = (char *) malloc(sizeof(char) * maxTitleLength);
        movie->head = (Details) malloc(sizeof(Details));
        movie->head->imdbID = (char *) malloc(sizeof(char) * maximdbIDLength);
        movie->head->posterLink = (char *) malloc(sizeof(char) * maxPosterLinkLength);
        movie->head->next = NULL;
        sscanf(line,"%[^,],%d,%[^,],%[^\n]",movie->Title,&movie->head->year,movie->head->imdbID,movie->head->posterLink);
        t = insert_movie(t,movie);
        free(movie);
        i++;
    }
    printf("i = %d",i);

    fclose(inFile);

    return t;
}

AVLTree insert_movie(AVLTree t, struct Movie_Node *m)
{
    if (t == NULL)
    {
        /*Create and return a one-node tree */
        t = malloc(sizeof(AVLTree));
        if (t == NULL)
            printf("Out of Memory space!!!\n");
        else
        {
            t->movie = (struct Movie_Node *) malloc(sizeof(struct Movie_Node));
            t->movie->Title = (char *) malloc(sizeof(char) * maxTitleLength);
            t->movie->number_of_releases = 0;
            if(t->movie == NULL)
            {
                printf("Out of memory space!!\n");
            }
            else
            {
                strcpy(t->movie->Title,m->Title);
                addDetails(t,m->head,t->movie->number_of_releases);
                t->height = 0;
                t->movie->number_of_releases++;
                t->left = t->right = NULL;
            }
        }
    }
    else if (strcmp(m->Title,t->movie->Title) < 0)
    {
        t->left = insert_movie(t->left,m);
        printf("I've gone left!\n");
        if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
        {
            if (strcmp(m->Title,t->left->movie->Title) < 0)//left left case
                t = SingleRotateToRight(t);
            else
                t = DoubleRotateFirstLeftThenRight(t);
        }
        printf("I'm in!\n");
    }
    else if (strcmp(m->Title,t->movie->Title) > 0)
    {
        t->right = insert_movie(t->right,m);
        printf("I've gone right!\n");
        if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
        {
            if (strcmp(m->Title,t->right->movie->Title) > 0)//right right case
                t = SingleRotateToLeft(t);
            else
                t = DoubleRotateFirstRightThenLeft(t);
        }
        printf("I'm in!\n");
    }
    else if (strcmp(ConverttoLower(m->Title),ConverttoLower(t->movie->Title))==0)
    {
        printf("WE are the same!!\n");
        addDetails(t,m->head,t->movie->number_of_releases);
        t->movie->number_of_releases++;
        printf("Our details were similar but I'm in!\n");
    }

    t->height = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;

    return t;
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
void display_index(AVLTree t)
{
    if (t != NULL)
    {
        display_index(t->left);
        printf("%s\n", t->movie->Title);
        display_index(t->right);
    }
}
void most_popular_year_movies(AVLTree t)
{
    int i,year_with_max_movies,count1,count2;

    if(t!=NULL)
    {
        if(t->movie->number_of_releases==1)
        {
            year_with_max_movies = t->movie->years[0][0];
            count1 = countNODES(t,year_with_max_movies);
        }
    }


}
void display_movies_keyword(AVLTree t, char *str)
{
    char *temp;

    if(t!=NULL)
    {
        display_movies_keyword(t->left,str);
        removeSpaces(str);
        strcpy(temp,t->movie->Title);
        removeSpaces(temp);

        if(strncmp(ConverttoLower(temp),ConverttoLower(str),strlen(temp))==0)
        {
            if(t->movie->number_of_releases>1)
            {
                int i;
                printf("%s,",t->movie->Title);
                for(i=0;i<t->movie->number_of_releases;i++)
                    printf("%d,",t->movie->years[0][i]);
                for(i=0;i<t->movie->number_of_releases;i++)
                    printf("%s,",t->movie->imdbID[i]);
                for(i=0;i<t->movie->number_of_releases;i++)
                    printf("%s,",t->movie->posterLink[i]);
            }
            else
            {
                printf("%s,%d,%s,%s,",t->movie->Title,t->movie->years[0][0],t->movie->imdbID[0],t->movie->posterLink[0]);
            }

        }
        display_movies_keyword(t->right,str);
    }
}
