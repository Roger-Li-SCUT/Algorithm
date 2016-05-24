/********************************************************************************
    > File Name: 234.cpp
    > Author: liyscut
    > Mail: liyang.nenu@gmail.com 
    > Created Time: Sun 08 Nov 2015 06:40:59 PM CST
********************************************************************************/

#include "234tree.h"

Tree root = NULL;//全局变量
//root = (Tree)malloc(sizeof(Tree));

int node_num=0;

int main()
{
//******************************************************************************************************
//输入测试文件初始化
	FILE *fp;
	char filename[30],ch;
	//printf("请输入你要测试的数据\n");
	//scanf("%s",filename);
	int number,i,count=0;
	char num[30];
	clock_t start,end;
	double duration;
	fp=fopen("/home/b8402-2/suanfa/2-3-4树测试数据.txt","r");
	//fp=fopen(filename,"r");
	if(fp==NULL)
	{
		printf("该文件不存在,请确认后重新输入\n");
		exit(1);
	}
    start = clock();
	while((ch=fgetc(fp))!=EOF)
   	{
		int i=0;
		while(ch<=57&&ch>=48&&ch!=EOF)
		{		
			num[i]=ch;
			i++;
			ch=fgetc(fp);
		}
		number=atoi(num);
        Tree_Insert(root,number);
		
		count++;
		if(count==30000000)
		{
			end=clock();
			duration=double(end-start)/CLOCKS_PER_SEC;
			printf("到3千万级数据!,时间为 %lf s\n",duration);
		}
		if(count==70000000)
		{
			end=clock();
			duration=double(end-start)/CLOCKS_PER_SEC;
			printf("到7千万级数据!,时间为 %lf s\n",duration);
		}
		if(count==90000000)
		{
			end=clock();
			duration=double(end-start)/CLOCKS_PER_SEC;
			printf("到9千万级数据!,时间为 %lf s\n",duration);
		}
	}
    end=clock();
    duration=double(end-start)/CLOCKS_PER_SEC;
    printf("全部数据初始化时间为 %lf s\n",duration);
//******************************************************************************************************
//遍历
	start = clock();
	InOrder_traverse(root);
	end = clock();
	duration=double(end-start)/CLOCKS_PER_SEC;
    printf("全部数据遍历时间为 %lf s,共有 %d 个节点\n",duration,node_num);
	
}
