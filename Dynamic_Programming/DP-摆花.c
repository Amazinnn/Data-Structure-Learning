/*
# P1077 [NOIP 2012 普及组] 摆花

## 题目描述

小明的花店新开张，为了吸引顾客，他想在花店的门口摆上一排花，共 $m$ 盆。
通过调查顾客的喜好，小明列出了顾客最喜欢的 $n$ 种花，从 $1$ 到 $n$ 标号。
为了在门口展出更多种花，规定第 $i$ 种花不能超过 $a_i$ 盆，
摆花时同一种花放在一起，且不同种类的花需按标号的从小到大的顺序依次摆列。
试编程计算，一共有多少种不同的摆花方案。

## 输入格式

第一行包含两个正整数 $n$ 和 $m$，中间用一个空格隔开。
第二行有 $n$ 个整数，每两个整数之间用一个空格隔开，依次表示 $a_1,a_2, \cdots ,a_n$。

## 输出格式
一个整数，表示有多少种方案。注意：因为方案数可能很多，请输出方案数对 $10^6+7$ 取模的结果。

## 说明/提示

【数据范围】

对于 $20\%$ 数据，有 $0<n \le 8,0<m \le 8,0 \le a_i \le 8$。
对于 $50\%$ 数据，有 $0<n \le 20,0<m \le 20,0 \le a_i \le 20$。
对于 $100\%$ 数据，有 $0<n \le 100,0<m \le 100,0 \le a_i \le 100$。

NOIP 2012 普及组 第三题
*/
#include <stdio.h>
#define MOD 1000007
// 定义动态规划数组，f[i][j]表示用前i种花，摆j盆花的方案数
// 数组大小为101x101是因为n,m最大为100，需要0~100共101个位置
long long int f[101][101];       

int main(void)
{
    int n, Total;
    								// 读取花的种类数n和总共要摆的盆数Total
    scanf("%d %d", &n, &Total);
    int flower[n+1];  				// flower[i]表示第i种花最多能摆的盆数
    
    // 读取每种花最多能摆的盆数
    for (int i = 1; i <= n; i++)
        scanf("%d", &flower[i]);
    
    // 初始化动态规划数组
    // 1. 当有0种花时，摆i盆花（i>0）的方案数为0
    for (int i = 0; i <= Total; i++)
        f[0][i] = 0;
    
    // 2. 用前i种花摆0盆花的方案数为1（什么都不摆）
    for (int i = 0; i <= n; i++)
        f[i][0] = 1;
    
    // 注意：上面两个初始化的顺序很重要，f[0][0]被先设为0，然后设为1
    // 最终f[0][0]=1，表示"用0种花摆0盆"是1种方案，这是正确的
    
    // 动态规划主过程
    for (int Type = 1; Type <= n; Type++) {         		// 外层循环：遍历花的种类
        for (int Picked = 1; Picked <= Total; Picked++) {  	// 中层循环：遍历要摆的总盆数
            f[Type][Picked] = 0;  // 初始化当前状态为0
            
            // 内层循环：枚举当前种类（Type）的花摆多少盆
            // 当前种类花最多能摆min(flower[Type], Picked)盆
            // 因为不能超过该种花的上限flower[Type]，也不能超过要摆的总盆数Picked
            for (int FlowersOfI = 0; 
                 FlowersOfI <= ((flower[Type] >= Picked) ? Picked : flower[Type]);
                 FlowersOfI++) {
                // 状态转移方程：
                // 如果第Type种花摆了FlowersOfI盆
                // 那么前Type-1种花需要摆Picked-FlowersOfI盆
                // 累加所有可能的FlowersOfI对应的方案数
                f[Type][Picked] += f[Type-1][Picked-FlowersOfI];
                
                // 每一步都要取模，防止溢出
                f[Type][Picked] %= MOD;
            }
        }
    }
    
    // 输出结果：用前n种花摆Total盆的总方案数
    // 注意：f数组是long long int类型，应该用%lld格式输出
    printf("%lld", f[n][Total]);  // 修正：%ld改为%lld
    
    return 0;
}













