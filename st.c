#include"string.h"
#include<stdio.h>
#include<stdlib.h>
#include"st.h"

void init_st(st* root){
    *root = NULL;
    return;
}


void zig(st* root, node* key){
    
    node *p = key, *q = key->parent, *temp = NULL;

    temp = p->right;
    p->parent = q->parent;
    if(q->parent){
        if(q->parent->left == q){
            q->parent->left = p;
        }
        else{
            q->parent->right = p;
        }
    }
    q->parent = p;
    p->right = q;
    q->left = temp;
    if(temp){
        temp->parent = q;
    }
    if(p->parent == NULL){
        *root = p;
    }
    return;
}


void zag(st* root, node* key){
    
    node *p = key, *q = key->parent, *temp = NULL;

    temp = p->left;
    p->parent = q->parent;
    if(q->parent){
        if(q->parent->left == q){
            q->parent->left = p;
        }
        else{
            q->parent->right = p;
        }
    }
    q->parent = p;
    p->left = q;
    q->right = temp;
    if(temp){
        temp->parent = q;
    }
    if(p->parent == NULL){
        *root = p;
    }
    return;
}


void zig_zig(st* root, node* key){

    //In this rotation, we first rotate the bond between the parent and the grandparent in right direction. 
    zig(root, key->parent);

    //After that, rotation of bond between the child and the parent occurs in right direction.    
    zig(root, key);
	
	return;

}


void zag_zag(st* root, node* key){

    //In this rotation, we first rotate the bond between the parent and the grandparent in left direction. 
    zag(root, key->parent);

    //After that, rotation of bond between the child and the parent occurs in left direction.    
    zag(root, key);

	return;

}

void zig_zag(st* root, node* key){

    //In this rotation, we first rotate the bond between the child and the parent in right direction. 
    zig(root, key);

    //After that, rotation of bond between the child and the grandparent occurs in left direction.    
    zag(root, key);
    
	return;

}

void zag_zig(st* root, node* key){
    
    //In this rotation, we first rotate the bond between the child and the parent in left direction. 
    zag(root, key);

    //After that, rotation of bond between the child and the grandparent occurs in right direction.    
    zig(root, key);

	return;

}


void Splay(st* root, node* key){

//Splaying consists of 6 cases:
//1. Searched/Newly inserted node is left child of the root - Zig rotation
//2. Searched/Newly inserted node is right child of the root - Zag rotation
//3. Searched/Newly inserted node is left child of the parent and left child of its grandparent - Zig Zig rotation
//4. Searched/Newly inserted node is right child of the parent and right child of its grandparent - Zag Zag rotation
//5. Searched/Newly inserted node is left child of its parent and its parent is right child of its parent - Zig Zag rotation
//6. Searched/Newly inserted node is right child of its parent and its parent is left child of its parent - Zag Zig rotation

	while (key->parent != NULL) {
		if (key->parent->parent != NULL) {
			if (key->parent->left == key) {
				if (key->parent->parent->left == key->parent) {
                    //printf("\nCall to zig_zig function\n");
					zig_zig(root, key);
				} else {
                    //printf("\nCall to zig_zag function\n");
					zig_zag(root, key);
				}
			} else {
				if (key->parent->parent->left == key->parent) {
                    //printf("\nCall to zag_zig function\n");
					zag_zig(root, key);
				} else {
                    //printf("\nCall to zag_zag function\n");
					zag_zag(root, key);
				}
			}
		} 
        else if (key->parent != NULL) {
			if (key->parent->left == key) {
                //printf("\nCall to zig function\n");
				zig(root, key);
			} else {
                //printf("\nCall to zag function\n");
				zag(root, key);
			}
		}
	}
	return;
}

void InsertNode(st* root, char* data, char* mean){

    st nn = (st)malloc(sizeof(node));
    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    strcpy(nn->word, data);
    strcpy(nn->meaning, mean);

    if(!(*root)){
        *root = nn;
        return;
    }

    node *p = NULL, *q = NULL;
    p = *root;
    while(p){
        q = p;
        if(strcmp(p->word, data) > 0)
            p = p->left;
        else if(strcmp(p->word, data) < 0)
            p = p->right;
        else 
            return;
    }
    
    nn->parent = q;
    if(strcmp(q->word, data) > 0){
        q->left = nn;
    }
    else{
        q->right = nn;
    }
    Splay(root, nn);
    return;
}


void Search(st* root, char* data){
    int count = 1;
    node* p = *root;
    if(!p){
        printf("No Details Found !!!\n");
        return;
    }
    while (p != NULL){
        if(strcmp(p->word, data) == 0){
            printf("Word : %s    Meaning : %s\n", p->word, p->meaning);
            printf("Total number of Comparisions : %d\n", count);
            Splay(root, p);
            return;
        }
        else if(strcmp(p->word, data) > 0 ){
            count++;
            p = p->left;
        }
        else if(strcmp(p->word, data) < 0 ){
            count++;
            p = p->right;
        }
    }
    printf("No Details Found !!!\n");
    return;
}


void Delete(st* root, char* data){
    node* p = *root;
    if(!p){
        printf("No Details Found !!!\n");
        return;
    }

    while (p != NULL){

        if(strcmp(p->word, data) == 0){

            Splay(root, p);

            node *del = NULL;

            if(p->left == NULL){
                del = p;
                p = p->right;
                p->parent = NULL;
            }
            else{
                node *q = p->left;

                while (q->right != NULL){
                    q = q->right;
                }

                Splay(&(p->left), q);

                del = p;
                p = p->left;
                p->parent = NULL;
                p->right = del->right;
                del->right->parent = p;
            }
            *root = p;
            free(del);
            return;
        }
        else if(strcmp(p->word, data) > 0 ){
            p = p->left;
        }
        else if(strcmp(p->word, data) < 0 ){
            p = p->right;
        }
    }

    printf("No Details Found !!!\n");
    return;
}


void preorder(node *key, int *n){
	if(!key)
		return;
    printf("| %-3d |  %-16s     |  %-16s      |\n", (*n)++, key->word, key->meaning);
	preorder(key-> left, n);
	preorder(key-> right, n);
	return;
}