typedef struct node{
    char word[20], meaning[20];
    struct node *left, *right, *parent;
}node;

typedef node* st;

void init_st(st *root);

void InsertNode(st* root, char* data, char* mean);

void Search(st* root, char* data);

void Delete(st* root, char* data);

void zig(st* root, node* key);

void zag(st* root, node* key);

void zig_zig(st* root, node* key);

void zag_zag(st* root, node* key);

void zig_zag(st* root, node* key);

void zag_zig(st* root, node* key);

void Splay(st* root, node* key);

void preorder(st key, int *n);