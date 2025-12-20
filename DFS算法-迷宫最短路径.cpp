/*
递归求解迷宫最短通道的总步长。输入一个迷宫，求从入口通向出口的可行路径中最短的路径长度。
为简化问题，迷宫用二维数组 int maze[10][10]来存储障碍物的分布.
假设迷宫的横向和纵向尺寸的大小是一样的，并由程序运行读入, 若读入迷宫大小的值是n（3<n<=10），
则该迷宫横向或纵向尺寸都是n，规定迷宫最外面的一圈是障碍物，迷宫的入口是maze[1][1]，出口是maze[n-2][n-2],.
若maze[i][j] = 1代表该位置是障碍物，若maze[i][j] = 0代表该位置是可以行走的空位（0<=i<=n-1, 0<=j<=n-1）。
求从入口maze[1][1]到出口maze[n-2][n-2]可以走通的路径上经历的最短的总步长。
要求迷宫中只允许在水平或上下四个方向的空位上行走，走过的位置不能重复走。

输入格式:
输入迷宫大小的整数n, 以及n行和n列的二维数组（数组元素1代表障碍物，0代表空位）

输出格式:
若有可行的通道则输出一个整数，代表求出的通道的最短步长；若没有通道则输出"No solution"
*/

#include <stdio.h>
#include <stdbool.h>

typedef struct place{
	bool visited;							//该点是否已经访问过 
	bool isWall;							//该点是否存在墙以阻挡前进 
} table;
int min=-1,n;
int direc[4][2]={{-1,0},{1,0},{0,-1},{0,1}};//方向数组 
table a[10][10];							//将迷宫数组设定为全局变量，确保递归函数的每一层均能查看到已行驶路径的 
											//实时状况，确保路径不重复 
bool isSet(int x,int y)						//检验该点是否能够踏足 
{
	if (x>=1&&x<=n-2){
		if (y>=1&&y<=n-2){
			if (a[x][y].isWall==0&&a[x][y].visited==0) return true;
		}
	}
	else return false;
}

void shortcut(int x,int y,int steps)		//将步数传递给下一层递归，然后在抵达终点时求出总步数
{											//有些递归函数是等所有递归均完成再输出，但这个不同 
	if (isSet(x,y)==false) return;
	else if (x==n-2&&y==n-2){
		if (min==-1||steps<min) min=steps;
		return;
	}
	else {
		if (min!=-1&&steps>min) return;
		a[x][y].visited=true;
		for (int i=0;i<4;i++){				//四个方向 
			int x_new=x+direc[i][0];
			int y_new=y+direc[i][1];
			shortcut(x_new,y_new,steps+1);
		}
		a[x][y].visited=false;				//回退一步，同时消去痕迹 
	}
}

int main(void)
{
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			scanf("%d",&a[i][j].isWall);	//输入迷宫结构：墙体的位置 
			a[i][j].visited=false;			//初始化，令所有点均未被路过 
		}
	}
	if (a[1][1].isWall==true||a[n-2][n-2].isWall==true){
		printf("No solution");
		return 0;
	}
	else {
		shortcut(1,1,0);
		if (min==-1){
			printf("No solution");
			return 0;
		}
		else {
			printf("%d",min);
			return 0;
		}
	}
	return 0;
}










