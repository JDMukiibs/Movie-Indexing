#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLTree.h"

AVLTree read_data(AVLTree t,char *[]);
void insert_movie(AVLTree, char *, int, char *, char *);
void display_index(AVLTree);
void most_popular_year_movies(AVLTree);
void display_movies_keyword(AVLTree);

int main(int argc, char *argv[])
{
    AVLTree myMovieIndex;
    myMovieIndex = CreateTree();
    myMovieIndex = read_data(myMovieIndex,argv);

    return 0;
}

AVLTree read_data(AVLTree t, char *argument[]) {
    char filename[25];
    sscanf(argument[1],"%s",filename);

    char line[350];//When iterating through the textfile this shall help store one line worth of one song's information in the file.
    // 350 is the maximum characters that a text file can show on one line.
    FILE *inFile;
    char dateTime[20];//I'll use this character array to read the date and time from within the file as one string.
    int SIZE=0,i=0;
    // SIZE -- This variable will be used to record number of songs in the textfile
    // so that during copying to List we can exit the loop once the whole file is checked. i will help with loop iteration.
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

    //TO BE COMPLETED!!

    return t;
}

void insert_movie(AVLTree t,char *Title, int year,char *imdbID, char *posterLink)
{
    struct Movie_Node *new_movie;
    new_movie = malloc(sizeof(struct Movie_Node));
    new_movie->next = NULL;
    //initialize a new movie node to be added to the list as we iterate through the file
    strcpy(new_movie->Title,Title);
    new_movie->year = year;
    strcpy(new_movie->imdbID,imdbID);
    strcpy(new_movie->posterLink,posterLink);

    t = InsertElement(new_movie,t);
}
