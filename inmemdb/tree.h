#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#pragma GCC diagnostic ignored "-Wstringop-truncation"

#define TagRoot 1 //00 01
#define TagNode 2 //00 10
#define TagLeaf 3 //00 11

#define NoError 0
#define ExampleFile "./wl.txt"

#define find_last(x) find_last_linear(x)

#define find_leaf(x,y) find_leaf_linear(x,y)

#define lookup(x, y) lookup_linear(x, y)

#define find_node(x) find_node_linear(x)
#define reterr(x) \
    errno = (x); \
    return NULL


#define Print(x) \
        zero(buf, 256); \
        strncpy((char*)buf,(char *) (x), 255 ); \
        size = (int16)strlen((char*)buf); \
        if(size) \
            (void)write(fd, (char*)buf, size)
        

/*

/
  /users/
  /users/harsh
  /users/a

        /users/login/

if we keep copies of string at each it might add a few kb, but will make our parsing easier
*/

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;
typedef unsigned char Tag;


struct s_node {
    Tag tag;
    struct s_node *north;
    struct s_node *west;
    struct s_leaf *east;
    int8 path[256];

};

typedef struct s_node Node;

struct s_leaf {
    Tag tag;
    union u_tree *west;
    struct s_leaf *east;
    int8 key[128];
    int8 *value; // this can be large
    int16 size;

};
typedef struct s_leaf Leaf;

union u_tree {
    Node n;
    Leaf l;
};
//all var in union share the same memory space
typedef union u_tree Tree;

int8 *indent(int8);
void print_tree(int, Tree*);
void zero(int8*, int16);
Leaf *find_leaf_linear(int8*, int8*);
int8 *lookup_linear(int8*, int8*);
Node *find_node_linear(int8*);
Node *create_node(Node*, int8*);
Leaf *find_last_linear(Node*);
Leaf *create_leaf(Node*, int8*, int8*, int16);
int8 *example_path(int8);
Tree *example_tree(void);
int32 example_leaves(void);
int8 *example_duplicate(int8 *);
int main(void);