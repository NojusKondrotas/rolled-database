//programming implementation

#include "tree.h"

Tree root = {
    .n = {
        .tag = (TagRoot | TagNode),
        .north = (Node *)&root,
        .west = 0,
        .east = 0,
        .path = "/"
    }
};

void zero(int8 *str, int16 size){
    int8 *p;
    int16 n;
    
    for(n=0, p=str; n < size; p++, n++)
        *p = 0;

    return;
}

Node *create_node(Node *parent, int8 *path){
    Node *n;
    int16 size;

    errno = NoError;
    assert(parent);
    size = sizeof(struct s_node);
    n = (Node *)malloc((int)size);
    zero((int8 *)n, size);

    parent->west = n;
    n->tag = TagNode;
    n->north = parent;
    strncpy((char *)n->path, (char *)path, 255);

    return n;
}

Leaf *find_last_linear(Node *parent){
    Leaf *l;

    errno = NoError;
    assert(parent);
    if(!parent->east)
        reterr(NoError);

    for(l = parent->east; l->east; l = l->east);

    assert(l);

    return l;
}

Leaf *create_leaf(Node *parent, int8 *key,
  int8 *value, int16 count){
    Leaf *l, *new;
    int16 size;

    assert(parent);
    l = find_last(parent);

    size = sizeof(struct s_leaf);
    new = (Leaf *)malloc(size);
    assert(new);

    if(!l)
        parent->east = new;
        // directly connected
    else
        l->east = new;
        // l is a leaf

    zero((int8 *)new, size);
    new->tag = TagLeaf;
    new->west = (!l) ? (Tree *)parent : (Tree *)l;

    strncpy((char *)new->key, (char *)key, 127);
    new->value = (int8 *)malloc(count);
    zero(new->value, count);
    assert(new->value);
    strncpy((char *)new->value, (char *)value, count);
    new->size = count;

    return l;
}

int main(){
    Node *n, *n2;

    n = create_node((Node *)&root, (int8 *)"/Users");
    assert(n);
    n2 = create_node(n, (int8 *)"/Users/login");
    assert(n2);

    printf("%p %p\n", n, n2);
    free(n2);
    free(n);

    return 0;
}