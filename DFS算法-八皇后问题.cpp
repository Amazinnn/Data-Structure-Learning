/*
会下国际象棋的人都很清楚：皇后可以在横、竖、斜线上不限步数地吃掉其他棋子。
如何将8个皇后放在棋盘上（有8 * 8个方格），使它们谁也不能被吃掉！这就是著名的八皇后问题。
对于某个满足要求的8皇后的摆放方法，定义一个皇后串a与之对应，即a=b1b2...b8，其中bi为相应摆法中第i行皇后所处的列数。
已经知道8皇后问题一共有92组解（即92个不同的皇后串）。
给出一个数b，要求输出第b个串。串的比较是这样的：皇后串x置于皇后串y之前，当且仅当将x视为整数时比y小。

输入格式:
第1行是测试数据的组数n，后面跟着n行输入。每组测试数据占1行，包括一个正整数b(1 <= b <= 92)

输出格式:
输出有n行，每行输出对应一个输入。输出应是一个正整数，是对应于b的皇后串。
*/ 

#include <stdio.h>
#include <stdbool.h>
bool chess[9][9]={false};
long int array[92];
int count=0;

bool Coexist(int placed,int direct)    //输入已经放置的棋子数、即将放置的棋子纵坐标
{                                       //判断能否放置
    for (int i=placed+1;i>=1;i--) if (chess[i][direct]) return 0;							//同一纵列检测是否存在皇后 
    for (int i=1;placed+1-i>=1&&direct-i>=1;i++) if (chess[placed+1-i][direct-i]) return 0;	//主对角线（及其平行线）检测是否存在皇后 
    for (int i=1;placed+1-i>=1&&direct+i<=8;i++) if (chess[placed+1-i][direct+i]) return 0;	//副对角线（及其平行线）检测是否存在皇后 
    return 1;
}

void search(int placed) 						//输入已经放置的棋子数
{
    if (placed==8){
        long int sum=0;
        for (int i=1;i<=8;i++){
            for (int j=1;j<=8;j++){
                if (chess[i][j]!=0){
                    sum=sum*10+j;				//逐行统计皇后纵坐标，并将纵坐标串以长整型存储 
                    break;
                }
            }
        }
        array[count++]=sum;
        return;
    }
    else if (placed==0){
        for (int i=1;i<=8;i++){
            chess[1][i]=1;						//第一个棋子，无需检测是否冲突 
            search(1);
            chess[1][i]=0;						//擦除痕迹 
        }
        return;
    }
    else {
        for (int i=1;i<=8;i++){
            if (!Coexist(placed,i)) continue;    //剪枝:冲突的情况
            else {
                chess[placed+1][i]=1;
                search(placed+1);
                chess[placed+1][i]=0;
            }
        }
    }
}

int main(void)
{
    search(0);
    int n,b;
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",&b);
        printf("%ld\n",array[b-1]);
    }
    return 0;
}
