//算法思想：
//将字符串ABCBCCAAA转化成A0B0C0B0C0C0A0A0A0,然后在0位置分别插入A、B、C，注意如果一定要分别插入A、B、C，如BBBAB情况
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compute(char a[]);

int compute(char a[])
{
    //printf("%s\n",a);
    bool delete_flag=false,do_flag=true;
    int i=0,j,length;
    int count=0;
    length=strlen(a);
    while(do_flag==true)
    {
        bool flag=false;
        while(i<length-1)
        {
            if(a[i]!='0')
            {
                for(j=i+1;j<length;j++)
                {
                    if(a[j]=='0')
                        continue;
                    else if(a[j]!=a[i])
                        break;
                    else if(a[j]==a[i])
                        {
                            delete_flag=true;
                            flag=true;
                            count++;
                            a[j]='0';
                        }
                }
                if(delete_flag==true)
                {
                    a[i]='0';
                    count++;
                    delete_flag=false;
                }
                i=j;
            }
            else
                i++;
        }
        //printf("%s\n",a);
        if(flag==false)
            do_flag=false;
        else
        {
            i=0;
        }
    }
    return count;
}

int main()
{
    int n;
    scanf("%d",&n);
    while(n>0)
    {
        int count,max_count=0;
        int i,length;
        char a[110];
        scanf("%s",a);
        length=strlen(a);
        
        char *b=(char*)malloc(2*(length+10)*sizeof(char));
        for(i=0;i<length;i++)
        {
            b[2*i]=a[i];
            b[2*i+1]='0';
        }
        b[strlen(b)+1]='\0';
        
        for(i=0;i<length;i++)
        {
            char c[230]="";
            int j;
            for(j=0;j<strlen(b);j++)
                c[j]=b[j];
            c[j]='\0';
            for(int k=0;k<3;k++)
            {
                c[2*i+1]='A'+k;
                count=compute(c);
                if(count>max_count)
                    max_count=count;
                for(j=0;j<strlen(b);j++)
                    c[j]=b[j];
                c[j]='\0';
            }
            //printf("%s\n",c);
            
        }
        printf("%d\n",max_count);
        n--;
    }
    return 0;
}