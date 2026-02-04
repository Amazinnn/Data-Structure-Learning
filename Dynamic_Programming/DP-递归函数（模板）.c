/*
# P1464 Function

## 题目描述

对于一个递归函数 $w(a,b,c)$
- 如果 $a \le 0$ 或 $b \le 0$ 或 $c \le 0$ 就返回值 $1$。
- 如果 $a>20$ 或 $b>20$ 或 $c>20$ 就返回 $w(20,20,20)$
- 如果 $a<b$ 并且 $b<c$ 就返回 $w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c)$。
- 其它的情况就返回 $w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1)$

这是个简单的递归函数，但实现起来可能会有些问题。当 $a,b,c$ 均为 $15$ 时，
调用的次数将非常的多。你要想个办法才行。
注意：例如 $w(30,-1,0)$ 又满足条件 $1$ 又满足条件 $2$，
请按照最上面的条件来算，答案为 $1$。

### 数据规模与约定
保证输入的数在 $[-9223372036854775808,9223372036854775807]$ 之间，并且是整数。
保证不包括 $-1, -1, -1$ 的输入行数 $T$ 满足 $1 \leq T \leq 10 ^ 5$。
*/

#include <stdio.h>
#define L long long int
#define Min(a,b) ((a<=b)?(a):(b))

L dp[30][30][30]={0};

long long int dfs(L a,L b,L c)
{
	if (a<=0||b<=0||c<=0){
		return 1;
	}
	else if (a>20||b>20||c>20) return dfs(20,20,20);
	else if (dp[a][b][c]) return dp[a][b][c];
	else if (a<b&&b<c){
		L input;
		input=dfs(a,b,c-1)+dfs(a,b-1,c-1)-dfs(a,b-1,c);
		dp[a][b][c]=input;
		return input;
	}
	else {
		L input;
		input=dfs(a-1,b,c)+dfs(a-1,b-1,c)+dfs(a-1,b,c-1)-dfs(a-1,b-1,c-1);
		dp[a][b][c]=input;
		return input;
	}
}

int main(void)
{
	L a,b,c;
	while ((scanf("%lld %lld %lld",&a,&b,&c))==3&&!(a==-1&&b==-1&&c==-1)){
		printf("w(%lld, %lld, %lld) = %lld\n",a,b,c,dfs(a,b,c));
	}
	return 0;
}
















