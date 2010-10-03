#include<stdio.h>
#include<stdlib.h>

struct tree{
	int value;
	struct tree *pr, *pl, *parent;
}*root=0;


void insert(struct tree *t, int i)
{
	if ((t == root) && (root == 0))
	{
		root = (struct tree *) malloc(sizeof(struct tree));
		root -> value = i;
		root -> pr = 0;
		root -> pl = 0;
		root -> parent = 0;
	}
	else if ((i < t -> value) && (t -> pl != 0)) return insert(t -> pl, i);
	else if ((i > t -> value) && (t -> pr != 0)) return insert(t -> pr, i);
	else if (i < t -> value)
	{
		t -> pl = (struct tree *) malloc(sizeof(struct tree));
		t -> pl -> value = i;
		t -> pl -> parent = t;
		t -> pl -> pl = 0;
		t -> pl -> pr = 0;
	}
	else if (i > t -> value)
	{
		t -> pr = (struct tree *) malloc(sizeof(struct tree));
		t -> pr -> value = i;
		t -> pr -> parent = t;
		t -> pr -> pl = 0;
		t -> pr -> pr = 0;
	}
}

struct tree * delete_replace(struct tree* victim)
{
		struct tree* t;
		if((!victim -> pr) && (!victim -> pl)) return victim;
		else if(victim -> pr)
		{
				if(!victim -> pr -> pl) return victim -> pr;
				else{
						for(t = victim -> pr; t -> pl != 0; t = t -> pl);
						return t;} 
		}
		else if(victim -> pl)
		{
				if(!victim -> pl -> pr) return victim -> pl;
				else{
						for(t = victim -> pl; t -> pr != 0;t = t -> pr);
						return t;}
		}
}
		
void parent_change(struct tree * min,struct tree * p)
{
		min -> parent = p -> parent;
		if(p -> parent && p == p -> parent -> pr) p -> parent -> pr = min;
		else if(p -> parent && p == p -> parent ->pl) p -> parent -> pl = min;
		else root = min;
}

struct tree *find(struct tree *, int);
void p_delete(int item)
{
		struct tree *p,*min,*temp;
		p = find(root,item);
		min = delete_replace(p);
		if(p -> pr)
		{
			if(min != p->pr){
				min -> parent -> pl = 0;
				min -> pr = p -> pr; 
				min -> pr -> parent = min;}
			if(p -> pl){
			min -> pl = p -> pl;
			min-> pl -> parent = min;}
			parent_change(min, p);
		}
		else if(min == p -> pl){
				min -> pr = 0;
				parent_change(min, p);}
		else
		{
			if(p -> parent){
			if(p == p -> parent -> pr) p -> parent -> pr = 0;
			else p -> parent -> pl = 0;}
		}
		free(p);
}

void inorder(struct tree *a)
{
	if (a) {
	inorder(a -> pl);
	printf("%d\t", a -> value);
	inorder(a -> pr);
	}
}

void preorder(struct tree *a)
{
	if (a) {
		printf("%d\t", a-> value);
		preorder(a -> pl);
		preorder(a -> pr);
	}
}

void postorder(struct tree *a)
{
	if (a) {
	inorder(a -> pl);
	inorder(a -> pr);
	printf("%d\t", a -> value);
	}
}

struct tree * find(struct tree *a, int i)
{
	struct tree *p;
	if (a -> value == i)
		return a;
	else if (i < a -> value)
		p = find(a -> pl, i);
	else
		p = find(a -> pr, i);
}

int bal_fac(struct tree *a, struct tree *origin)
{
	int l = 0, r = 0;
	if ((a -> pl != 0) || (a -> pr != 0))
	{
		if (a -> pl != 0)
			l = 1 + bal_fac(a -> pl, origin);
		if (a -> pr != 0)
			r = 1 + bal_fac(a -> pr, origin);
	}
	else
		return 0;
	if (a -> value == origin -> value) {
		return (l - r); }
	else
		return (l > r ? l : r);
}


void rotate_right(struct tree *head, struct tree *pivot)
{
	struct tree *temp, *hold = 0;
	temp = head;
	pivot -> parent = head -> parent;
	if (head -> parent != 0 && head == head -> parent -> pr)
		head -> parent -> pr = pivot;
	else if(head -> parent != 0 && head == head -> parent -> pl)
		head -> parent -> pl = pivot;
	else
	{
		pivot -> parent = 0;
		root = pivot;
	}
	if (pivot -> pr)
		hold = pivot -> pr;
	pivot -> pr = head;
	pivot -> pr -> pl = hold;
	if (hold)
		hold -> parent = pivot -> pr;
	head -> parent = pivot;
}

void rotate_left(struct tree *head, struct tree *pivot)
{
	struct tree *temp, *hold = 0;
	temp = head;
	pivot -> parent = head -> parent;
	if (head -> parent != 0 && head == head -> parent -> pl)
		head -> parent -> pl = pivot;
	else if(head -> parent != 0 && head == head -> parent -> pr)
		head -> parent -> pr = pivot;
	else
	{
		pivot -> parent = 0;
		root = pivot;
	}
	if (pivot -> pl)
		hold = pivot -> pl;
	pivot -> pl = head;
	pivot -> pl -> pr = hold;
	if (hold)
		hold -> parent = pivot -> pl;
	head -> parent = pivot;
}

void balance(struct tree *par)
{
	int bal;
	bal = bal_fac(par, par);
	if (bal == -2)
	{
		if (bal_fac(par -> pr, par -> pr) <= 0)
			rotate_left(par, par -> pr);
		else
		{
			rotate_right(par -> pr, par -> pr -> pl);
			rotate_left(par, par -> pr);
		}
	}
	else if (bal == 2)
	{
		if (bal_fac(par -> pl, par -> pl) >= 0)
			rotate_right(par, par -> pl);
		else
		{
			rotate_left(par -> pl, par -> pl -> pr);
			rotate_right(par, par -> pl);
		}
	}

}

void self_bal(int val)
{
	int bal;
	struct tree *p, *par;
	p = find(root, val);
//	par = p -> parent;
	while(p -> parent != 0)
	{
		balance(p -> parent);
		if (p -> parent)
			p = p -> parent;
	}
}

void bal_insert(struct tree *a, int val)
{
	insert(a, val);
	self_bal(val);
}

void display(struct tree *ptr,int level)
{
        int i;
        if (ptr)
	{       
		display(ptr -> pr, level + 1);
                printf("\n");
                for (i = 0; i < level; i++)
                	printf("  ");
                printf("%d", ptr -> value);
                display(ptr -> pl, level + 1);
         }
}

void bal_delete(struct tree *a, int i)
{
	struct tree *p;
	p = find(a, i);
	p_delete(i);
	if(p -> parent)
		self_bal(p -> parent -> value);
}

void balance_insert(int i)
{
	bal_insert(root, i);
}

void traverse(int i)
{
	if (i == 1)
		inorder(root);
	else if (i == 2)
		preorder(root);
	else if (i == 3)
		postorder(root);
	else if (i == 4)
		display(root, 0);
}

void balance_delete(int i)
{
	bal_delete(root, i);
}

main()
{
	struct tree *p;
	int i;

	balance_insert(23);
	bal_insert(root,41);
	bal_insert(root,17);
	bal_insert(root,16);
	bal_insert(root,19);
	bal_insert(root,18);	
	bal_insert(root,85);	
	bal_insert(root,14);	
	bal_insert(root,12);
	traverse(2);
	//traverse(4);
	printf("\n");
	printf("\n");
	bal_delete(root, 41);
	//display(root, 0);
	printf("\n");
	printf("\n");
	preorder(root);
}

