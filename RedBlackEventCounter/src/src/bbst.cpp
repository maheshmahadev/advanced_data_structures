#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//define node's structure
struct node
{
   int ID;//ID of the node
   node *parent;//parent of the node
   char color;//color of the node
   node *left;//left child of the node
   node *right;//right child of the node
   int count;//count of the node
};

//define RBtree

class RBtree
{
public :
	node *root;
	node *nil;
	RBtree()
	{
		nil=new node;
		root=nil;
		nil->color='b';
		nil->ID=0;
		nil->count=0;
	}
	void Increase(int, int);
	void Count(int);
	void InRange(int, int);
	void Next(int);
	void Previous(int);
	void Reduce(int, int);
private:
	void insertfix(node *);
	void leftrotate(node *);
	void rightrotate(node *);
	node* successor(node *);
	void delfix(node *);
	int inrange(int, int, node *);
	void transplant(node *, node *);
};

//implement the Increase function

void RBtree::Increase(int theID, int m)
{
	node *p,*q;

	//create new node

	node *t=new node;
	t->ID=theID;
	t->left=nil;
	t->right=nil;
	t->color='r';
	t->count=m;
	p=root;
	q=nil;

	if(root==nil)
	{
		root=t;
		t->parent=nil;
	}
	else
	{
		while(p!=nil)
		{
			q=p;
			if(p->ID==theID) { // theID exists in the tree
				p->count+=m;
				cout<<p->count<<endl;
				return;
			}
			if(p->ID<t->ID)
				p=p->right;
			else
				p=p->left;
		}

		//theID doesn't exist

		t->parent=q;
		if(q->ID<t->ID)
			q->right=t;
		else
			q->left=t;
	}
	cout<<m<<endl;
	insertfix(t);
}

//insert new node

void RBtree::insertfix(node *t)
{
	node *u;
	if(root==t)
	{
		t->color='b';
		return;
	}
	while(t->parent!=nil&&t->parent->color=='r')
	{
		node *g=t->parent->parent;
		if(g->left==t->parent)
		{
			u=g->right;
			if(u!=nil && u->color=='r') //case 1
			{
				t->parent->color='b';
				u->color='b';
				g->color='r';
				t=g;
			}
			else
			{
				if(t->parent->right==t) //case 2(this turns into case 3)
				{
					t=t->parent;
					leftrotate(t);
				}
				t->parent->color='b';
				g->color='r';
				rightrotate(g);
			}
		}
		else //this is the same as above, but switches "left" and "right"
		{
			u=g->left;
			if(u!=nil && u->color=='r')
			{
				t->parent->color='b';
				u->color='b';
				g->color='r';
				t=g;
			}
            else
            {
                if(t->parent->left==t)
                {
                   t=t->parent;
                   rightrotate(t);
                }
                t->parent->color='b';
                g->color='r';
                leftrotate(g);
            }
		}
	}
    root->color='b';
}

void RBtree::transplant(node *u, node *v)
{
	if(u->parent==nil) root=v;
	else if(u==u->parent->left) u->parent->left=v;
	else u->parent->right=v;
	v->parent=u->parent;
}

//implement the Reduce function

void RBtree::Reduce(int theID, int m)
{
	if(root==nil)
	{
		cout<<0<<endl;
		return ;
	}
	node *p;
	p=root;
	node *y=nil;
	node *q=nil;
	int found=0;// found=1 if theID exists
	while(p!=nil&&found==0)
	{
		if(p->ID==theID) found=1;
		if(found==0)
		{
			if(p->ID<theID) p=p->right;
			else p=p->left;
		}
	}
	if(found==0)// theID doesn't exist
	{
		cout<<0<<endl;
		return ;
	}
	else
	{
		p->count-=m;
		if (p->count<0) p->count=0;
		cout<<p->count<<endl;
		if (p->count>0) return;

		//delete the theID (value of it is less than or equal to 0
		y=p;
		char oricolor=y->color;
		if(p->left==nil) {
			q=p->right;
			transplant(p, q);
		} else if (p->right==nil) {
			q=p->left;
			transplant(p, q);
		} else {
			y=p->right;
			while(y->left!=nil) y=y->left;
			oricolor=y->color;
			q=y->right;
			if(y->parent==p) q->parent=y;
			else {
				transplant(y, y->right);
				y->right=p->right;
				y->right->parent=y;
			}
			transplant(p, y);
			y->left=p->left;
			y->left->parent=y;
			y->color=p->color;

		}
	}
}

//delete the node

void RBtree::delfix(node *p)
{
    node *s;
    while(p!=root && p->color=='b')
	{
		if(p->parent->left==p)
        {
			s=p->parent->right;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                leftrotate(p->parent);
                s=p->parent->right;
        	}
            if(s->right->color=='b' && s->left->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->right->color=='b')
                {
                    s->left->color=='b';
                    s->color='r';
                    rightrotate(s);
                    s=p->parent->right;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->right->color='b';
                leftrotate(p->parent);
                p=root;
            }
        }
        else
        {
            s=p->parent->left;
            if(s->color=='r')
            {
                s->color='b';
                p->parent->color='r';
                rightrotate(p->parent);
                s=p->parent->left;
            }
            if(s->left->color=='b' && s->right->color=='b')
            {
                s->color='r';
                p=p->parent;
            }
            else
            {
                if(s->left->color=='b')
                {
                    s->right->color='b';
                    s->color='r';
                    leftrotate(s);
                    s=p->parent->left;
                }
                s->color=p->parent->color;
                p->parent->color='b';
                s->left->color='b';
                rightrotate(p->parent);
                p=root;
            }
        }
    }
    root->color='b';
}

//leftrotate the tree according to node p

void RBtree::leftrotate(node *p)
{
	if(p->right==nil)
		return ;
	else
    {
		node *y=p->right;
		p->right=y->left;
		if(y->left!=nil) y->left->parent=p;
		y->parent=p->parent;
        if(p->parent==nil)
            root=y;
        else
        {
            if(p==p->parent->left) p->parent->left=y;
            else p->parent->right=y;
        }
        y->left=p;
        p->parent=y;
    }
}

//rightrotate the tree accordint to node p

void RBtree::rightrotate(node *p)
{
	if(p->left==nil)
        return ;
    else
    {
        node *y=p->left;
        p->left=y->right;
        if(y->right!=nil) y->right->parent=p;
        y->parent=p->parent;
        if(p->parent==nil)
        	root=y;
        else
        {
            if(p==p->parent->left) p->parent->left=y;
            else p->parent->right=y;
        }
        y->right=p;
        p->parent=y;
    }
}

//find the successor of node p

node* RBtree::successor(node *p)
{
	node *y=nil;
	if(p->left!=nil)
	{
		y=p->left;
		while(y->right!=nil)
			y=y->right;
	}
	else
	{
		y=p->right;
		while(y->left!=nil)
			y=y->left;
	}
	return y;
}

//implement the Count function

void RBtree::Count(int theID)
{
	if(root==nil)
	{
		cout<<0<<endl ;
		return;
	}
	node *p=root;
	int found=0;
	while(p!=nil && found==0)
	{
		if(p->ID==theID) found=1;
		if(found==0)
		{
			if(p->ID<theID)
				p=p->right;
			else
				p=p->left;
		}
	}
	if(found==0)
		cout<<0<<endl;
	else
	{
		cout<<p->count<<endl;
	}
}

//implement the Next function

void RBtree::Next(int theID)
{
	if(root==nil)
	{
		cout<<0<<" "<<0<<endl;
		return;
	}
	node *p=root;
	bool found=0;
	while(found==0)
	{
		if(p->ID==theID)
			found=1;
		if(found==0)
		{
			if(p->ID<theID) {
				if (p->right==nil) break;
				p=p->right;
			} else {
				if (p->left==nil) break;
				p=p->left;
			}
		}
	}

	if(found==1 || p!=nil && p->ID<theID)
	{
		if (p->right==nil)
		{
			while(p->parent!=nil && (p->parent)->right==p) p=p->parent;
			p=p->parent;
		}
		else
		{
			p=p->right;
			while(p->left!=nil)
				p=p->left;
		}
	}

	if (p==nil)
		cout<<0<<" "<<0<<endl;
	else
	{
		cout<<p->ID<<" "<<p->count<<endl;
	}
}

//implement the InRange function

void RBtree::InRange(int ID1, int ID2)
{
	node *p=root;
	cout<<inrange(ID1, ID2, p)<<endl;
}

int RBtree::inrange(int ID1, int ID2, node *p)
{
	if(p==nil) return 0;
	if(ID1>ID2) return 0;
	if(p->ID<ID1) return inrange(ID1, ID2, p->right);
	if(p->ID>ID2) return inrange(ID1, ID2, p->left);
	int res=p->count;
	res+=inrange(ID1,p->ID-1, p->left);
	res+=inrange(p->ID+1, ID2, p->right);
	return res;
}

//implement the Previous function

void RBtree::Previous(int theID)
{
	if(root==nil)
	{
		cout<<0<<" "<<0<<endl;
		return;
	}
	node *p=root;
	bool found=0;
	while(found==0)
	{
		if(p->ID==theID)
			found=1; //theID exists
		if(found==0)
		{
			if(p->ID<theID) {
				if (p->right==nil) break;
				p=p->right;
			} else {
				if (p->left==nil) break;
				p=p->left;
			}
		}
	}
	if(found==1 || p->ID>theID)
	{
		if (p->left==nil) //go upwards
		{
			while(p->parent!=nil && (p->parent)->left==p) p=p->parent;
			p=p->parent;
		}
		else	//go downwards
		{
			p=p->left;
			while(p->right!=nil)
				p=p->right;
		}
	}
	if (p==nil)
		cout<<0<<" "<<0<<endl;
	else
	{
		cout<<p->ID<<" "<<p->count<<endl;
	}

}

#define MAXN 100001000 //maximal number of the nodes
RBtree obj;
int n, ID[MAXN], count[MAXN], H;

//n-number of initial nodes
//H-height of initial tree

//construct the initial tree

node* Initialize(int dp, int low, int high)
{
	int N, mid;
	N=high-low+1;
	if(N<=0) return obj.nil;
	mid=low-1+(N+1)/2;
	node *u=new node;
	u->left=Initialize(dp+1, low, mid-1);
	u->left->parent = u;
	u->right=Initialize(dp+1, mid+1, high);
	u->right->parent = u;
	u->ID=ID[mid];
	u->count=count[mid];
	if(dp==H) u->color='r';//the node whose height is H only has color 'r'
	else u->color='b';
	return u;
}

//main function

int main(int argc, char **argv)
{

    int i, theID, m, ID1, ID2;
    char resp[20];

	FILE *f;
	if(argc>1)
        f=fopen(argv[1],"r");
    else
        f=fopen("bbst_in.txt","r");
    if(argc>2)
        freopen(argv[2],"r",stdin);
    if(argc>3)
        freopen(argv[3],"w",stdout);
	fscanf(f, "%d", &n);//get the initial tree's information
	for (i=0; i<n; i++)
		fscanf(f, "%d%d", ID+i, count+i);

	H=0;
	while((1<<H)<=n) H++;//calculate the height of the initial tree

	obj.root=Initialize(1, 0, n-1);//initialize the tree
	obj.root->parent = obj.nil;

    while (true)
    {
        cin>>resp;
        if (!strcmp(resp, "increase")) {
        	cin>>theID>>m;
        	obj.Increase(theID, m);
		} else if (!strcmp(resp, "reduce")) {
			cin>>theID>>m;
			obj.Reduce(theID, m);
 		} else if (!strcmp(resp, "count")) {
			cin>>theID;
			obj.Count(theID);
		} else if (!strcmp(resp, "inrange")) {
			cin>>ID1>>ID2;
			obj.InRange(ID1, ID2);
		} else if (!strcmp(resp, "next")) {
			cin>>theID;
			obj.Next(theID);
		} else if (!strcmp(resp, "previous")) {
			cin>>theID;
			obj.Previous(theID);
		} else if (!strcmp(resp, "quit")){
			exit(0);
		}
    }
    return 1;
}


