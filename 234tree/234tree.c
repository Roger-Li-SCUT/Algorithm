/********************************************************************************
    > File Name: 234.h
    > Author: liyscut
    > Mail: liyang.nenu@gmail.com 
    > Created Time: Sun 08 Nov 2015 06:42:54 PM CST
********************************************************************************/

#include "234tree.h"

//创建节点
TreeNode* node_create(int key,TreeNode *parent)
{
	TreeNode *treenode;
	treenode=(TreeNode*)malloc(sizeof(TreeNode));
	
	treenode->data_l = key;
	treenode->data_m = INT_MAX;
	treenode->data_r = INT_MAX;
	treenode->left_child = NULL;
	treenode->left_mid_child = NULL;
	treenode->right_mid_child = NULL;
	treenode->right_child = NULL;
	treenode->parent = parent;
	return treenode;
}

//判断节点是否为叶节点
bool compare_leaf(Tree treenode)
{
	if(treenode->left_child==NULL)//如果p->left_child为NULL说明此节点为叶结点
		return true;
	else
		return false;
}

//返回插入节点应该插入的位置
int compare(Tree treenode , int key)
{
  	if(key < treenode->data_l) 
   		return 1;
  	else if((key > treenode->data_l) && (key < treenode->data_m))
   		return 2;
  	else if((key > treenode->data_m) && (key < treenode->data_r))
   		return 3;
  	else if(key > treenode->data_r)
   		return 4;
  	else if(key==treenode->data_r||key==treenode->data_m||key==treenode->data_l)
   		return 5;	
}

//判断节点类型
int node_type(Tree treenode)
{
	if(treenode->data_l != INT_MAX && treenode->data_m == INT_MAX && treenode->data_r == INT_MAX)
  		return 2;
 	if(treenode->data_l != INT_MAX && treenode->data_m != INT_MAX && treenode->data_r == INT_MAX)
  		return 3;
  	if(treenode->data_l != INT_MAX && treenode->data_m != INT_MAX && treenode->data_r != INT_MAX)
		return 4;
}

void split_root(Tree &treenode)
{
	TreeNode *lnode,*rnode;

	lnode = node_create(treenode->data_l,treenode);
	rnode = node_create(treenode->data_r,treenode);
	
	lnode->left_child = treenode->left_child;
	lnode->left_mid_child =t reenode->left_mid_child;
	
	rnode->left_child = treenode->right_mid_child;
	rnode->left_mid_child = treenode->right_child;
	
	treenode->data_l = treenode->data_m;
	treenode->data_m = INT_MAX;
	treenode->data_r = INT_MAX;
 	treenode->left_child = lnode;
 	treenode->left_mid_child = rnode;
	treenode->right_mid_child = NULL;
	treenode->right_child = NULL;
	treenode->parent = NULL;
	return;
}

void node2_split(TreeNode *treenode,TreeNode *child)
{
	if (child == parent->left_child)//4-节点为父结点的左孩子
 	{
  		TreeNode *lnode;
  		node_create(lnode,child->data_l);
  		lnode->left_child = child->left_child;
  		lnode->left_mid_child = child->left_mid_child;
		
		parent->data_m = parent->data_l;
  		parent->data_l = child->data_m;
  		parent->data_r = INT_MAX;

		//node_create(rnode,child->data_r);
		child->data_l=child->data_r;
		child->data_m=INT_MAX;
		child->data_r=INT_MAX;
		
  		child->left_child = child->right_mid_child;
  		child->left_mid_child = child->right_child;
  		child->right_mid_child=NULL;
		child->right_child=NULL;

  		parent->right_mid_child = parent->left_mid_child;
  		parent->left_mid_child = child;
  		parent->left_child=lnode;
	}
 	else//4-节点为父结点的左中孩子
 	{
  		TreeNode *lnode;
		
		node_create(lnode,child->data_l);
  		lnode->left_child = child->left_child;
  		lnode->left_mid_child = child->left_mid_child;

		parent->data_m = child->data_m;
  		parent->data_r = INT_MAX;
		
		child->data_l=child->data_r;
		child->data_m=INT_MAX;
		child->data_r=INT_MAX;
  		child->left_child = child->right_mid_child;
  		child->left_mid_child = child->right_child;
   		child->right_mid_child=NULL;
		child->right_child=NULL;
 
  	  	parent->right_mid_child = child;
		parent->left_mid_child=lnode;
 	} 
 	return;
}

//3-节点与4-节点相连
void node3_split(TreeNode *parent,TreeNode *child)
{
	TreeNode *lnode;
	node_create(lnode,child->data_l);
	if (child == parent->left_child)//4-节点为父结点的左孩子
 	{
		lnode->left_child = child->left_child;
  		lnode->left_mid_child = child->left_mid_child;
   		parent->data_r = parent->data_m;
  		parent->data_m = parent->data_l;
  		parent->data_l = child->data_m;  
		
		child->data_l=child->data_r;
		child->data_m=INT_MAX;
		child->data_r=INT_MAX;	
		child->left_child = child->right_mid_child;
  		child->left_mid_child = child->right_child;
  		child->right_mid_child = NULL;
		child->right_child = NULL;
 
  		parent->left_child = lnode;
		parent->left_mid_child = child;
  		parent->right_mid_child = parent->left_mid_child;
  		parent->right_child = parent->right_mid_child;

 	}
	else if (child == parent->left_mid_child)//4-节点为父结点的左中孩子
 	{
  		lnode->left_child = child->left_child;
  		lnode->left_mid_child = child->left_mid_child;
  		
		parent->data_r = parent->data_m;
  		parent->data_m = child->data_m;
 		
 		child->data_l=child->data_r;
		child->data_m=INT_MAX;
		child->data_r=INT_MAX; 
 		child->left_child = child->right_mid_child;
  		child->left_mid_child = child->right_child;
		child->right_mid_child = NULL;
		child->right_child = NULL;
    
  		parent->left_mid_child = lnode;
  		parent->right_mid_child = child;
  		parent->right_child = parent->right_mid_child;

 	}
 	else//4-节点为父结点的右中孩子
 	{
  		lnode->left_child = child->left_child;
  		lnode->left_mid_child = child->left_mid_child;
		parent->data_r = child->data_m;
		child->data_l=child->data_r;
		child->data_m=INT_MAX;
		child->data_r=INT_MAX; 
		child->left_child = child->right_mid_child;
  		child->left_mid_child = child->right_child;
  		child->right_mid_child = NULL;
		child->right_child = NULL;
  		  
		parent->right_mid_child = lnode;
  		parent->right_child = child;
 	}
 	return;
}


void Node_Insert(Tree &treenode , int key)//将元素插入叶结点
{
	
	if(treenode->data_m == INT_MAX)//叶结点是2-节点
 	{
  		if (key < treenode->data_l)
  		{
   			treenode->data_r = INT_MAX;
   			treenode->data_m = treenode->data_l;
   			treenode->data_l = key;
   			treenode->right_mid_child = NULL;
  		}
  		else
  		{
  			treenode->data_r = INT_MAX;
  	 		treenode->data_m = key;
   			treenode->right_mid_child = NULL;
  		}
 	}
 	else//叶结点是3-节点
 	{
  		if (key < treenode->data_l)
  		{
   			treenode->data_r = treenode->data_m;
   			treenode->data_m = treenode->data_l;
   			treenode->data_l = key;
   			treenode->right_child = NULL;
  		}
  		else if ((key > treenode->data_l) && (key < treenode->data_m))
  		{
   			treenode->data_r = treenode->data_m;
   			treenode->data_m = key;
   			treenode->right_child = NULL;
  		}
  		else
  		{
   			treenode->data_r = key;
   			treenode->right_child = NULL;
  		}   
 	}
 	return;
}

void Tree_Insert(Tree &tree , int key)
{
	
	//234树为空，创建根节点
	if(tree == NULL)
	{
		tree=node_create(key,NULL);
		return;
	}
	else//如果234树为非空
	{
		TreeNode *x=tree;
		
		if(x->parent==NULL && compare_leaf(x))
		{
			if(node_type(x)==4)
			{
				split_root(x);
				Tree_Insert(x,key);
			}
			else
			{
				Node_Insert(x,key);
				return;
			}
		}
		else
		{
			while(!compare_leaf(x))
			{
				if(node_type(x) == 4)
				{
					if(node_type(x->parent) == 2)
						node2_split(x->parent,x);
					else if(node_type(x->parent) == 3)
						node3_split(x->parent,x);
					Tree_Insert(x->parent,key);
				}
				switch (compare(x,key))
   				{
    				case 5: return;
    				case 1: x = x->left_child;
					break;
        			case 2: x = x->left_mid_child;
         			break;
    				case 3: x = x->right_mid_child;
           			break;
    				case 4: x = x->right_child;
					break;
   				}
			}
			Node_Insert(x,key);
		}
	}
	return;
}

void InOrder_traverse(Tree root)
{  
	if(root!=NULL)
	{
		if(root->left_child)
			InOrder_traverse(root->left_child);
		if(root->data_l!=INT_MAX)
			node_num++;
		if(root->left_mid_child)
			InOrder_traverse(root->left_mid_child);
		if(root->data_m!=INT_MAX)
			node_num++;
		if(root->right_mid_child)
			InOrder_traverse(root->right_mid_child);
		if(root->data_r!=INT_MAX)
			node_num++;
		if(root->right_child)
			InOrder_traverse(root->right_child);
	}
	return;
}
