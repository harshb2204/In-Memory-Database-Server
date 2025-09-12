#include "tree.h"


Tree root = {
    .n = {
    .tag = (TagNode | TagRoot),
    .north = (Node*) &root,
    .west = 0,
    .east = 0,
    .path = "/"

    }
    
};
void zero(int8 *str, int16 size){
    int8 *p;
    int16 n;
    for(n = 0, p=str;n<size;p++,n++){
            *p = 0;
    }
    return;
    //Takes a pointer to memory (int8 *str) and a size in bytes (int16 size).
    //Iterates through each byte of that memory.
    //Writes 0 into each byte.
    //zero() is just a manual implementation of memset(..., 0, ...).
}


Node *create_node(Node *parent, int8 *path){
    Node *n;
    int16 size;

    errno = NoError;
    size = sizeof(struct s_node); 
    assert(parent);
    n = (Node *)malloc((int)size); 
    zero((int8 *)n, size); //This makes sure all fields of the new struct are initialized to 0 (or NULL for pointers).

    parent->west = n;
    n->tag = TagNode;
    n->north = parent;
    strncpy((char*) n->path, (char*)path, 255);
    return n;

}

Leaf *find_last_linear(Node *parent){
    Leaf *l;
    errno = NoError;

    assert(parent);
    if(!parent->east){
        reterr(NoError);

    }
    for(l = parent->east; l->east; l = l->east);
    assert(l);

    return l;

}

Leaf *create_leaf(Node *parent, int8 *key, int8 *value, int16 count){
    Leaf *l, *new;
   
    int16 size;


    
    
    assert(parent);
    // NODE -- leaf1 -- leaf2 -- leaf3
    l = find_last(parent);
    size = sizeof(struct s_leaf);
    new = (Leaf *) malloc(size);
    if(!l){
        //directly connected 
        parent-> east = new;
    }
    else{
        // l is a leaf
        l-> east = new;
    }

    zero((int8 *)new, size);
    new->tag = TagLeaf;
    new->west = (!l) ?
        (Tree *) parent :
        (Tree *) l;
    
    strncpy((char*)new->key, (char*)key, 127);
    new->value = (int8 *)malloc(count);
    zero(new->value, count);
    assert(new->value);
    strncpy((char *)new->value, (char*)value, count);
    new->size = count;
    return new;
}   

int main(){
    Node *n, *n2;

    Leaf *l1, *l2;
    int8 *key, *value;
    int16 size;

    n = create_node(( Node*) &root, (int8 *)"/Users");
    assert(n);
    n2 = create_node(n, (int8 *)"/Users/Login");
    assert(n2);
    key = (int8 *)"harsh";
    value = (int8 *)"abc1234aa";
    size = (int16)strlen((char*) value);
    l1 = create_leaf(n2, key, value, size);
    assert(l1);
    printf("%s\n", l1->value);
    
    key = (int8 *)"abc";
    value = (int8 *)"2b412bi";
    size = (int16)strlen((char*) value);
    l2 = create_leaf(n2, key, value,size );
    assert(l2);
    printf("%s\n", l2->value);

    printf("%p  %p\n", n, n2);
    free(n2);
    free(n);
    
    
    // printf("%p\n",  (void *)&root);

}