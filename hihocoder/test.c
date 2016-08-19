/********************************************************************************
    > File Name: test.c
    > Author: liyscut
    > Mail: liyang.nenu@gmail.com 
    > Created Time: 2016年08月19日 星期五 10时14分48秒
********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int length=5;
    char *b=(char*)malloc(2*(length+10)*sizeof(char));
    char a[10]="abc";
    b=a;
    printf("%d\n",strlen(b));
    return 0;
}
