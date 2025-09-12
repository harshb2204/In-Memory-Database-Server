


# Designing your own database in C
- You need to decide how to store data inside memory (not disk; in memory).
- Here, a binary tree is going to be used.
- Nodes are the hubs or connectors (they make up the structure of the tree). They don't have any actual data; leaves, however, contain one single element, and these elements could be one `int`, one `char`, one `struct`, or a `char` pointer with a string inside.
![](/Diagrams/dbdesign.png)
```c
union u_tree{
    struct s_node n;
    struct s_leaf l;

};
```
- This looks like a `struct` (we have a name and different variables inside).
- However, the thing that is different is that if it were a `struct`, the `s_node` would take up some memory and `s_leaf` would take up some of the structure's memory, so basically we could define `n` and `l` at the same time. In a `union`, we only have one of them at the same time: we either define `n` or `l` (the union either consists of a node or a leaf).


## Node 
- A node is a `struct s_node` (it's a structure).
```c
struct s_node{
    struct s_node *up;
    struct s_node *left;
    struct s_leaf *right;
    Tag tag; // to define what kind of structure it is, so we can differentiate data between leaf and node 
}
```
- `char path[255]`: a string containing the path to this node so we can access it at the user level. When the user connects to the database, let's say to the TCP port, and inputs `create /users/`, it should create one of these structures above and put this `users` inside of this path.

## Leaf
```c
struct s_leaf{
    struct s_tree *left;
    // each leaf will have a key that distinguishes it
    char key[255]; // standard null-terminated string
    char *value;  
    int count;
    Tag tag;

}
```
- In computer networking terms, the nodes can be the router, and the leaves would be the switch.

- A hash is a string that you fold into a number.
- A hash table is a 2D array pointing toward specific memory addresses of different points in a tree, and we use our hash number to index into that array.


