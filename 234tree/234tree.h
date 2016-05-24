/********************************************************************************
    > File Name: 234.h
    > Author: liyscut
    > Mail: liyang.nenu@gmail.com 
    > Created Time: Sun 08 Nov 2015 06:42:54 PM CST
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>//malloc和free提供函数原型
#include <string.h>
#include <limits.h>//定义了一些常量比如INT_MAX

typedef struct treenode
{
	int data_l;
 	int data_m;
 	int data_r;
 	treenode* left_child;
 	treenode* left_mid_child;
 	treenode* right_mid_child;
 	treenode* right_child;
 	treenode* parent;
	//int flag=0;//标记根节点
}TreeNode,*Tree;

//初始化节点
void node_create(Tree &treenode,int key);

//判断节点是否为叶节点
bool compare_leaf(Tree treenode);

//返回插入节点应该插入的位置
int compare(Tree treenode , int key);

//判断节点类型
int node_type(Tree treenode);

void split_root(Tree &treenode);


void node2_split(TreeNode *parent,TreeNode *child);

//3-节点与4-节点相连
void node3_split(TreeNode *parent,TreeNode *child);


void Node_Insert(Tree &treenode , int key);//将元素插入叶结点


void Tree_Insert(Tree &treenode , int key);


void InOrder_traverse(Tree root);