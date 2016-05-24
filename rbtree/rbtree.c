/********************************************************************************
    > File Name: rbtree.c
    > Author: liyscut
    > Mail: liyang.nenu@gmail.com 
    > Created Time: Wed 09 Mar 2016 04:36:08 PM CST
********************************************************************************/

/*** 
性质1 : 节点是红色或黑色。
性质2 : 根节点是黑色。
性质3 : 每个叶节点（NIL节点，空节点）是黑色的。
性质4 : 每个红色节点的两个子节点都是黑色。(从每个叶子到根的所有路径上不能有两个连续的红色节点)
性质5 : 从任一节点到其每个叶子的所有路径都包含相同数目的黑色节点。
***/ 
   
#include <stdio.h> 
#include <stdlib.h> 
typedef enum Color //定义红黑树结点颜色颜色类型
{ 
    RED = 0, 
    BLACK = 1 
}Color;
  
typedef struct Node //定义红黑树结点类型 
{ 
    struct Node *parent; 
    struct Node *left; 
    struct Node *right; 
    int value; 
    Color color; 
}Node, *Tree;
Node *nil=NULL; //为了避免讨论结点的边界情况，定义一个nil结点代替所有的NULL 
  
Node* Parent(Node *z) //返回某结点的父母 
{ 
    return z->parent; 
} 
Node* Left(Node *z) //返回左子树 
{ 
    return z->left; 
} 
Node *Right(Node *z) //返回右子树 
{ 
    return z->right; 
}

//左旋转：结点x原来的右子树y旋转成为x的父母
void LeftRotate(Tree &T, Node *x) 
{ 
    if(x->right!=nil) 
    { 
        Node *y=Right(x); 
        x->right=y->left; 
        if(y->left != nil) 
        { 
            y->left->parent=x; 
        } 
        y->parent=x->parent; 
        if(x->parent == nil) 
        { 
            T=y; 
        } 
        else 
        { 
            if(x==Left(Parent(x))) 
            { 
                x->parent->left=y; 
            } 
            else 
            { 
                x->parent->right=y; 
            } 
        } 
        y->left=x; 
        x->parent=y; 
    } 
    else 
    { 
        printf("%s/n","can't execute left rotate due to null right child"); 
    } 
} 
  
void RightRotate(Tree &T, Node *x) //右旋转：结点x原来的左子树y旋转成为x的父母 
{ 
    if(x->left!=nil) 
    { 
        Node *y=Left(x); 
        x->left=y->right; 
        if(y->right!=nil) 
        { 
            y->right->parent=x; 
        } 
        y->parent=x->parent; 
        if(x->parent==nil) 
        { 
            T=y; 
        } 
        else 
        { 
            if(x==Left(Parent(x)))
            { 
                x->parent->left=y; 
            }
            else 
            { 
                x->parent->right=y; 
            } 
        } 
        y->right=x; 
        x->parent=y; 
    } 
    else
    { 
        printf("%s/n","can't execute right rotate due to null left child"); 
    } 
} 
  
void InsertFixup(Tree &T, Node *z) //插入结点后, 要维持红黑树四条性质的不变性 
{
    //如果新点的父结点为黑色结点，那么插入一个红点将不会影响红黑树的平衡，此时插入操作完成。
    //红黑树比AVL树优秀的地方之一在于黑父的情况比较常见，从而使红黑树需要旋转的几率相对AVL树来说会少一些。
    Node *y;//记录y为叔父节点
    //如果新点的父结点为红色，这时就需要进行一系列操作以保证整棵树红黑性质
    while( Parent(z)->color == RED  )
    {
        //如果父节点是祖父节点的左子女
        if( Parent(Parent(z))->left == Parent(z)  )
        {
            y=Parent(Parent(z))->right;
            //case 1: 红叔 
            //当叔父结点为红色时，无需进行旋转操作，只要将父和叔结点变为黑色，将祖父结点变为红色即可。
            //但由于祖父结点的父结点有可能为红色，从而违反红黑树性质。此时必须将祖父结点作为新的判定点继续向上进行平衡操作。 
            if( y->color == RED  )
            { //祖父变为红色，这样子z的祖父结点可能违背性质3,将z上移成z的祖父结点 
                y->color=BLACK; 
                z->parent->color=BLACK; 
                z->parent->parent->color=RED; 
                z=z->parent->parent; 
            }
            //case 2: 黑叔
            //当叔父结点为黑色时，需要进行旋转
            else 
            {
                //case 2-1:如果y的颜色为黑色，并且z是z的父母的右结点，则z左旋转，并且将z变为原来z的parent.
                if(z==z->parent->right) 
                {
                    z=z->parent; 
                    LeftRotate(T, z); 
                }
                
                z->parent->color=BLACK;
                z->parent->parent->color=RED;
                RightRotate(T,z->parent->parent); 
            } 
        }
        //如果父节点是祖父节点的右子女
        else 
        { 
            y=Parent(Parent(z))->left; 
            if( y->color == RED ) 
            { 
                z->parent->color=BLACK; 
                y->color=BLACK; 
                z->parent->parent->color=RED; 
                z=z->parent->parent; 
            } 
            else 
            { 
                if(z==z->parent->left) 
                { 
                    z=z->parent; 
                    RightRotate(T,z); 
                } 
                z->parent->color=BLACK; 
                z->parent->parent->color=RED; 
                LeftRotate(T,z->parent->parent); 
            } 
        } 
    } 
    T->color=BLACK; //最后如果上升为T的根的话，把T的颜色设置为黑色 
}

void Insert(Tree &T, int val) //插入结点 
{
    //初始化工作：如果根尚不存在，那么new一个新结点给根，同时new一个新结点给nil
    //根为黑色节点，叶子节点即nil节点也为黑色节点
    if(T == NULL) 
    {
        //printf("create tree!\n");
        T=(Tree)malloc(sizeof(Node)); 
        nil=(Node*)malloc(sizeof(Node)); 
        nil->color=BLACK;
        T->left=nil; 
        T->right=nil; 
        T->parent=nil; 
        T->value=val; 
        T->color=BLACK;
        //printf("create tree done!\n");
    }
    //如果此树已经不为空，那么从根开始，从上往下查找插入点
    else 
    {
        //printf("insert node!\n");
        Node *x=T; //用x保存当前节点
        Node* x_temp; //用于记录当前节点的父节点  
        while(x!=nil) //如果val小于当前结点的value值，则从左边下去，否则从右边下去 
        {
            x_temp=x;
            if(val<x->value ) 
            { 
                x=x->left; 
            } 
            else if(val>x->value) 
            { 
                x=x->right; 
            } 
            else 
            { 
                printf("%s %d/n","duplicate value",val); //如果查找到与val值相同的结点，则什么也不做，直接返回 
                return; 
            } 
        }

        Node* new_node=(Node*)malloc(sizeof(Node));
        new_node->color=RED; //新插入的结点颜色设置为红色 
        new_node->left=nil;
        new_node->right=nil;
        new_node->parent=x_temp;
        new_node->value=val;
        x=new_node;
        if(val<x_temp->value) 
        {
            x_temp->left = x;
        } 
        else 
        {
            x_temp->right = x; 
        }
        //printf("insert node done!\n");
        InsertFixup(T, x); //插入后对树进行调整 
    } 
} 

//寻找结点x的中序后继  
Node* Successor(Tree T, Node *x)
{
    //如果x的右子树不为空，那么其中序后继为右子树中最左边的结点
    //注意从delete函数传入时，x的左右子树均不为空
    if(x->right!=nil) 
    { 
        Node *p=x->right; 
        while(p->left!=nil) 
        {
            p=p->left; 
        } 
        return p; 
    }
}

//节点交换
void Transplant(Tree &T,Node *u,Node *v)
{
    if(u->parent==nil)
        T=v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    if(v!=nil)
        v->parent=u->parent;
    return;
}
//删除黑色结点后，导致黑色缺失，违背性质4,故对树进行调整
void DeleteFixup(Tree &T, Node *x) 
{ 
    printf("调整开始\n");
    while(x!=T&&(x==nil||x->color==BLACK)) 
    { 
        if(x==x->parent->left) //如果x是其父结点的左子树 
        { 
            Node *w=x->parent->right; //设w是x的兄弟结点，设p为w的父亲 
            //case 1:x的兄弟w为红色，则w的儿子必然全黑，w父亲p也为黑 
            //做法：改变p与w的颜色，同时对p做一次左旋转，这样将情况1转换成2、3、4中的一种
            if( w->color == RED  ) 
            { 
                w->color=BLACK; 
                x->parent->color=RED; 
                LeftRotate(T, x->parent); 
                w=x->parent->right; 
            }
            //case 2: w的颜色为黑色，x与w的父亲颜色可红可黑，其左右子树的颜色都为黑色
            //做法：将w置为红色，new x为x与w的父亲
            if( (w->left==nil||w->left->color == BLACK) && (w->right==nil||w->right->color == BLACK) ) 
            { 
                w->color=RED; 
                x=x->parent; 
            }
            //case 3: w为黑色，w左孩子红色，右孩子黑色
            //做法： 交换w与左孩子的颜色，对w进行右旋。转换为情况4
            else if( w->right==nil||w->right->color == BLACK  ) 
            { 
                w->color=RED;
                if(w->left!=nil)
                    w->left->color=BLACK; 
                RightRotate(T, w); 
                w=x->parent->right; 
            }
            //case 4: w为黑色，w的右子树是红色
            //做法：交换w与父亲p颜色，同时对p做左旋，将w的右儿子置黑
            w->color=x->parent->color;
            x->parent->color=BLACK;
            if(w->right!=nil) 
                w->right->color=BLACK; 
            LeftRotate(T,x->parent); 
            x=T; 
        } 
        else //对称情况，如果x是其父结点的右子树 
        { 
            Node *w=x->parent->left; 
            if(w->color==RED) 
            { 
                w->color=BLACK; 
                x->parent->color=RED; 
                RightRotate(T,x->parent); 
                w=x->parent->left; 
            } 
            if((w->left==nil||w->left->color==BLACK) && (w->right==nil||w->right->color==BLACK) )
            { 
                w->color=RED; 
                x=x->parent; 
            } 
            else if((w->left==nil)||w->left->color==BLACK) 
            { 
                w->color=RED; 
                if(w->right!=nil)
                    w->right->color=BLACK; 
                LeftRotate(T, w); 
                w=x->parent->left; 
            }
            w->color=x->parent->color; 
            x->parent->color=BLACK; 
            if(w->left!=nil)
                w->left->color=BLACK; 
            RightRotate(T,x->parent); 
            x=T; 
        } 
    } 
    x->color=BLACK;
    printf("调整结束\n");
}

void Delete(Tree &T, Node *z) //在红黑树T中删除结点z 
{ 
    Node *x; //x指向实际要被删除的结点
    Node *y=z;
    //如果z有一个子树为空的话，那么将直接删除z,即y指向z
    if(z->left==nil)  
    { 
        x=z->right;
        Transplant(T,z,z->right);
    }
    else if(z->right==nil)
    {
        x=z->left;
        Transplant(T,z,z->left);
    }
    else 
    { 
        y=Successor(T, z);//如果z的左右子树皆不为空的话，则寻找z的中序后继x
        x=y->right;
        if(y->parent==z)
            x->parent=y;
        else
        {
            Transplant(T,y,y->parent);
            y->right=z->right;
            y->right->parent=y;
        }
        Transplant(T,z,y);
        y->left=z->left;
        y->left->parent=y;
        y->color=z->color;
    }
    //如果被删除的结点y的颜色为红色，则不需要进行红黑节点的转换
    if(y->color==BLACK)  
    { 
        DeleteFixup(T, x); 
    }
    //free(x);
    
}


Node* Search(Tree T, int val) 
{ 
    if(T!=nil) 
    { 
        if(val<T->value) 
        { 
            Search(T->left,val); 
        } 
        else if (val>T->value) 
        { 
            Search(T->right,val); 
        } 
        else
        {
            printf("found\n");
            return T; 
        }
    }
}
  
void MidTranverse(Tree T) 
{ 
    if( T != NULL && T != nil  ) 
    { 
        MidTranverse(T->left); 
        printf("%d %d\n",T->value,T->color); 
        MidTranverse(T->right); 
    }
    else
    {
        printf("NULL\n");
    }
}

int main() 
{ 
    Tree t=NULL;
    int a[20]={12,1,9,2,0,11,7,19,4,15,18,5,14,13,10,16,6,3,8,17};
    //int a[30]={12,20,1,21,9,2,22,0,11,23,7,24,19,25,4,26,15,27,18,28,5,14,13,29,10,16,6,3,8,17};
    for(int i=0;i<20;i++)
        Insert(t,a[i]);
    MidTranverse(t); 
    /*printf("删除\n");
    Delete(t,Search(t,12)); 
    Delete(t,Search(t,1));
    Delete(t,Search(t,9));
    Delete(t,Search(t,2));
    MidTranverse(t);*/ 
    return 0; 
}
