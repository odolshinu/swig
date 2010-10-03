%module avl
%{
        extern struct tree *root;
%}
        
extern void insert(struct tree *t, int i);
extern void inorder(struct tree *a);
extern void preorder(struct tree *a);
extern void postorder(struct tree *a);
extern struct tree * find(struct tree *a, int i);
extern struct tree * delete_replace(struct tree* victim);
extern void parent_change(struct tree * min,struct tree * p);
extern void p_delete(int item);
extern int bal_fac(struct tree *a, struct tree *origin);
extern void rotate_right(struct tree *head, struct tree *pivot);
extern void rotate_left(struct tree *head, struct tree *pivot);
extern void balance(struct tree *par);
extern void self_bal(int val);
extern void bal_insert(struct tree *a, int val);
extern void bal_delete(struct tree *a, int i);
extern void display(struct tree *ptr,int level);
extern void balance_insert(int i);
extern void traverse(int i);
extern void balance_delete(int i);
