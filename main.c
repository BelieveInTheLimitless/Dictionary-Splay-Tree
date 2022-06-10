#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include"st.h"

int main(){

    st root;
    init_st(&root);
    char word[100];
    char meaning[100];
    FILE *fp;
    fp=fopen("data.txt","r");
    if(!fp){
        printf("Can't Open File");
    }
    for(int i = 1; i<101; i++){
        fscanf(fp, "%s - %s", word, meaning);
        InsertNode(&root, word, meaning); 
    }
    fclose(fp);

    int option;
    int n;

    do{
        int a = 1;
        
        printf("\nChoose any of the following options : \n");
		printf("1. Search for word/s\n");
		printf("2. Insert new word and its meaning\n");
        printf("3. Delete word/s\n");
		printf("4. Preorder traversal\n");
		printf("5. Exit.\n");
		printf("Enter option : ");
		scanf("%d", &option);
		printf("\n");

        switch (option)
        {
        case 1:
        {
            while(a){
			    printf("\nEnter the word you want to search : ");
                scanf("%s", word);
        		Search(&root, word);
                printf("\nDo you want to search more words? If Yes enter 1, else 0: ");
			    scanf("%d", &a);
		    }
            break;
                
        }

        case 2:
        {
        	while(a){
			    printf("\nEnter the word to be inserted : ");
                scanf("%s", word);
                printf("Enter its meaning : ");
                scanf("%s", meaning);
        		InsertNode(&root, word, meaning); 
                printf("\nDo you want to insert more words? If Yes enter 1, else 0: ");
			    scanf("%d", &a);
		    }
            break;
        }

        case 3:
        {
            while(a){
			    printf("\nEnter the word to be deleted : ");
                scanf("%s", word); 
                Delete(&root, word);
                printf("\nDo you want to delete more words? If Yes enter 1, else 0: ");
			    scanf("%d", &a);
		    }
            break;
        }

        case 4:
        {
            int n = 1;
            printf("|------------------------------------------------------|\n");
            printf("| No. |  %-16s     |  %-16s      |\n", "Word", "Meaning");
            printf("|------------------------------------------------------|\n");
    		preorder(root, &n);
            printf("|------------------------------------------------------|\n");
    		break;
        }

        case 5:
        {
            exit(0);
            break;
        }

        default:
            printf("Please choose valid option!\n");
        }
    }while(option> 0 && option <6);
}