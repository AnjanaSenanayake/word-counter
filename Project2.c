/***************************************************************************************
*    Title: Word/character Counter
*    Author: Anjana Senanayake
*    Date: 2016  
*    Code version: v1.5
*    Availability: https://github.com/AnjanaSenanayake/Mandelbrot-Julia-
*
***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

typedef struct node
{
	int wordcount;
	char word[100];
    char character;
    int length;
	struct node* next;
}node;

//Functions signatures.
char* wordfix(char word[]);
int listcheckwords(node* temp,char word[]);
int listcheckcharacter(node* temp,char character);
void sortWordList(node* first); 
void linkSwapWord(node *node1, node *node2);
void sortCharacterList(node* first); 
void linkSwapCharacter(node *node1, node *node2);
int maxwordlength(node* head,int len);
int numcheck(char* string);
void printwordgraph(node* head,int len);
void printcharagraph(node* head,int len);
int listsum(node* head);
void printWordList(node* head);
void printCharacterList(node* head);
void print_usage();

//The head node of the linked list. 
node* head;
int sum = 0,scaled = 0;

int main(int argc, char** argv)
{
	char character,word[150],file[100];
    int i,j,k,len=10;
    int cflag=0,wflag=0,c=0,w=1;
	FILE *fp;
    i=1;
    while(i<argc)
    {    
        if(strcmp(argv[i],"-l")==0)
        {
           if((i+1)>=argc || !numcheck(argv[i+1]))
            {     
                if((i+1)>=argc)
                {    
                    printf("Not enough options for [-l]\n");
                    print_usage();
                    exit(1);
                }
                else
                {
                    printf("Invalid options for [-l]\n");
                    print_usage();
                    exit(1);
                }     
            }       
            if(atoi(argv[i+1])==0)
            {
                exit(0);
            } 
            len = atoi(argv[i+1]);
        }   
        if(strcmp(argv[i],"-c")==0)
        {    
            if(cflag)
            {
                printf("[-c] and [-w] cannot use together\n");
                print_usage();
                exit(1);
            } 
            else
            {
                cflag++;
                wflag++;
            }  
            c = 1;
            w = 0;
        }
        else if(strcmp(argv[i],"-w")==0)    
        {
            if(wflag)
            {
                printf("[-c] and [-w] cannot use together\n");
                print_usage();
                exit(1);
            } 
            else
            {
                cflag++;
                wflag++;
            }
            w = 1;
            c = 0;
        } 
        if(strcmp(argv[i],"--scaled")==0)
        {
            scaled = 1;
        }     
    i++;          
    }    

    head = (node*)malloc(sizeof(node));
    node* temp = (node*)malloc(sizeof(node));      
    head->next = temp;

    for(i=1;i<argc;i++)
    {
        if(isalpha(*argv[i]) && *argv[i]!='-')
        {    
            strcpy(file,argv[i]);     
		    fp = fopen(file, "r");
            if(fp == NULL)
            {
                printf("Cannot open one or more given files\n");
                exit(1);
            }    
            if(w)
            {    
		        while(fscanf(fp,"%s",word) != EOF)
                {
                    if(strcmp(wordfix(word),"")==0)
                    {
                        continue;
                    }
                    else{    
                    strcpy(word,wordfix(word));   
                    if(temp->wordcount==0)
                    {
                        strcpy(temp->word,word);
                        temp->length=strlen(word);
                        temp->wordcount++;
                    } 
                    else if(!listcheckwords(head,word))
                    {
                
                        temp->next = (node*)malloc(sizeof(node));
                        temp = temp->next;
                        strcpy(temp->word,word);
                        temp->length=strlen(word);
                        temp->wordcount++;
                    }    
                    }
                }
            }
            else if(c)
            {
                while(character = fgetc(fp))
                {
                    if(character==EOF)
                    {
                        break;
                    }    
                    else if(isalpha(character) || isdigit(character))
                    {
                        character = tolower(character);
                        if(temp->wordcount==0)
                        {
                            temp->character = character;
                            temp->wordcount++;
                        } 
                        else if(!listcheckcharacter(head,character))
                        {
                            temp->next = (node*)malloc(sizeof(node));
                            temp = temp->next;
                            temp->character = character;
                            temp->wordcount++;
                        }    
                    }    
                }    
            }    
		    fclose(fp);
        }      
        else if(!(strcmp(argv[i],"-w")==0) && !(strcmp(argv[i],"-c")==0) && !(strcmp(argv[i],"-l")==0) && (numcheck(argv[i])==0) && !(strcmp(argv[i],"--scaled")==0))
        {
            printf("Invalid option [%s]\n",argv[i]);
            print_usage();
            exit(1);
        }  
	}
    if(w)
    { 
       sortWordList(head->next); 
       printwordgraph(head,len);

    }
    else if(c)
    {
        sortCharacterList(head->next);
        printcharagraph(head,len);
    }  
    free(head);
    free(temp);
	return 0;
}
//Function checks whether the word is alpnumeric only, if not converts it to alpnumeric in lowercase
char* wordfix(char word[])
{
    int j,k=0;
    for(j=0;j<strlen(word);)
    {
        if(isalnum(word[j]))
        {
            word[j] = tolower(word[j]);
            j++;
        }
        else
        {
            k=j;
            while(k<strlen(word))
            {
                word[k]=word[k+1];
                k++;
            }
        }       
    }   
    return word;
}

//Function checks whether the word is already in the linked list.
int listcheckwords(node* head,char word[])
{
    node* temp = head->next;   
    while(temp!=NULL)
    {
        if(strcmp(temp->word,word)==0)
        {
            temp->wordcount++;
            return 1;
        }  
        temp = temp->next;
    }
    return 0;
}

//Function checks whether the character is already in the linked list.
int listcheckcharacter(node* head,char character)
{
    node* temp = head->next;
    while(temp!=NULL)
    {
        if(temp->character==character)
        {
            temp->wordcount++;
            return 1;
        }    
        temp=temp->next;
    }    
}

//Function sorts the word list according to word freaquency.
void sortWordList(node* first)
{
    int swap = 1;
    node *new1;
    node *new2 = NULL;
    while (swap)
    {
        swap = 0;
        new1 = first;
        while (new1->next != new2)
        {
            if(new1->wordcount < new1->next->wordcount)
            { 
                linkSwapWord(new1,new1->next);
                swap = 1;                
            }
            new1 = new1->next;   
        }
        new2 = new1;
    }
} 

//Function sorts the character list according to character freaquency.
void sortCharacterList(node* first)
{
    int swap = 1;
    node *new1;
    node *new2 = NULL;
    while (swap)
    {
        swap = 0;
        new1 = first;
        while (new1->next != new2)
        {
            if(new1->wordcount < new1->next->wordcount)
            { 
                linkSwapCharacter(new1,new1->next);
                swap = 1;                
            }
            new1 = new1->next;   
        }
        new2 = new1;
    }
} 

//Function swaps the words in two consecutive nodes.
void linkSwapWord(node *node1, node *node2)
{
    char tmp1[100];
    int tmp2;
    int tmp3;
    strcpy(tmp1,node1->word);
    tmp2 = node1->wordcount;
    tmp3 = node1->length;
    strcpy(node1->word,node2->word);
    node1->wordcount = node2->wordcount;
    node1->length = node2->length;
    strcpy(node2->word,tmp1);
    node2->wordcount = tmp2;
    node2->length = tmp3;
}

//Function swaps the characters in two consecutive nodes.
void linkSwapCharacter(node *node1, node *node2)
{
    char tmp1;
    int tmp2;
    tmp1 = node1->character;
    tmp2 = node1->wordcount;
    node1->character = node2->character;
    node1->wordcount = node2->wordcount;
    node2->character = tmp1;
    node2->wordcount = tmp2;
}

//Function finds the maximum length of a word, in a given range to fix the graph spaces.
int maxwordlength(node* head,int len)
{
    node* current = head->next;
    int i;
    int max=current->length;
    for(i=1;i<=len && current->next!=NULL;i++)
    {
        if(current->length>max)
        {
            max=current->length;
        }    
        current=current->next;
    }  
    return max;  
}

//Funtion prints a bar chart according to word freaquency
void printwordgraph(node* head,int len)
{
    int i,k,z,sum;
    float j,scale = 1;
    float barlength1=0,barlength2=0,maxbar;
    node* current = head->next;
    sum = listsum(head);
    for(j=1;j<=80;j++)
    {
        printf(" ");     
    }
    printf("\n");  
    for(z=1;(z<=len && current!=NULL);z++)
    {   
        barlength1 = ((float)(current->wordcount)/(float)(sum))*100;
        barlength2 = ((float)(current->wordcount)/(float)(head->next->wordcount));
        if(scaled)
        {
            maxbar = (barlength2)*(72-maxwordlength(head,len));
        } 
        else
        {
            maxbar = (barlength1)*(72-maxwordlength(head,len))/100;
        }
        for(i=1;i<=4;i++)
        {
            if(i==2)
            {
                printf(" %s ",current->word); 
                for(k=0;k<(maxwordlength(head,len)-current->length);k++)
                {
                    printf(" ");
                }   
            }
            else
            {
                for(k=0;k<=maxwordlength(head,len)+1;k++)
                {
                    printf(" ");
                }   
            }          
            printf("│");
            if(i<=3)
            {
                for(j=1;j<=maxbar;j++)
                {
                    printf("░");     
                }  
                if(i==2)
                {
                    printf("%.2f%%",barlength1);
                }
            }  
            else
            {
                for(j=1;j<=78-maxwordlength(head,len);j++)
                {
                    printf(" ");     
                }
            }    
            printf("\n");    
        }
        current=current->next;
    } 

    for(k=0;k<=maxwordlength(head,len)+1;k++)
    {
        printf(" ");
    }
    printf("└");
    for(z=0;z<(77-maxwordlength(head,len));z++)
    {
        printf("─");
    }    
    printf("\n");
}

//Funtion prints a bar chart according to character freaquency
void printcharagraph(node* head,int len)
{
    int i,k,z,sum;
    float j;
    float barlength1=0,barlength2=0,maxbar;
    node* current = head->next;
    sum = listsum(head);
    for(j=1;j<=80;j++)
    {
        printf(" ");     
    }
    printf("\n");
    for(z=1;(z<=len && current!=NULL);z++)
    {   
 
        barlength1 = ((float)(current->wordcount)/(float)(sum))*100;
        barlength2 = ((float)(current->wordcount)/(float)(head->next->wordcount));
        if(scaled)
        {
            maxbar = (barlength2)*(71);
        } 
        else
        {
            maxbar = (barlength1)*(71)/100;
        }
        for(i=1;i<=4;i++)
        {
            if(i==2)
            {
                printf(" %c ",current->character); 
            }
            else
            {
                for(k=0;k<3;k++)
                {
                    printf(" ");
                }   
            }          
            printf("│");
            if(i<=3)
            {
                for(j=1;j<=maxbar;j++)
                {
                    printf("░");     
                }  
                if(i==2)
                {
                    printf("%.2f%%",barlength1);
                }
            }  
            else
            {    
                for(j=1;j<=77;j++)
                {
                    printf(" ");      
                }
                
            }    
            printf("\n");    
        }
        current=current->next;
    }
    for(k=0;k<3;k++)
    {
        printf(" ");
    }
    printf("└");
    for(z=0;z<76;z++)
    {
        printf("─");
    }    
    printf("\n");
}

//Function checks whether the given word is a number or not.
int numcheck(char* string)
{   
    while(*string)
    {
        if(isdigit(*string++)==0)
        {
            return 0;
        }   
    }   
    return 1;
}

//Function returns the total number of unique words/characters in the list.
int listsum(node* head)
{
    node* tmp = head->next;
    while(tmp!= NULL)
    {
        sum = sum+tmp->wordcount;
        tmp = tmp->next;
    } 
    return sum;   
}

//Function prints a usage message to terminal.
void print_usage()
{
    printf("usage: freq [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n");
}