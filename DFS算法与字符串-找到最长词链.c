/*
魔族现在使用一种新型的密码系统。每一个密码都是一个给定的仅包含小写字母的英文单词表，
每个单词至少包含 1 个字母，至多 75 个字母。
如果在一个由一个词或多个词组成的表中，除了最后一个以外，
每个单词都被其后的一个单词所包含，即前一个单词是后一个单词的前缀，
则称词表为一个词链。例如下面单词组成了一个词链：
i；
int；
integer。

但下面的单词不组成词链：
integer；
intern。

现在你要做的就是在一个给定的单词表中取出一些词，组成最长的词链，
就是包含单词数最多的词链。将它的单词数统计出来，就得到密码了。

输入格式
这些文件的格式是，第一行为单词表中的单词数 N（1≤N≤2000），
下面每一行有一个单词，按字典顺序排列，中间也没有重复的单词。

输出格式
输出共一行，一个整数，表示密码。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 2000

int maxlen=1;

typedef struct node {
	char s[76];
	struct node *next[N];
	int occupy;
	bool check;					//若该单词已经被检查过，则无需再以该单词为开头重复路径
								//当然，必须保留长路径覆盖短路径的情况 
} node;

void link(node *a,node *b)
{
	char *pa=a->s,*pb=b->s;
	//bool isSubset=1;
	while (*pa!='\0'&&*pb!='\0'){
		if (*pa!=*pb){
			//isSubset=0;
			return ;
		}
		else {
			pa++;
			pb++;
		}
	}
	if (*pa=='\0'){
		a->next[a->occupy++]=b;
	}
	else {
		b->next[b->occupy++]=a;
	}
}

void search(node *prev,int len)
{
	prev->check=true;
	if (prev->occupy==0){
		if (len>maxlen) maxlen=len;
		return ;
	}
	else {
		for (int i=0;i<prev->occupy;i++){
			search(prev->next[i],len+1);
		}
		return ;
	}
} 

int main(void)
{
	int n;
	scanf("%d",&n);
	node *dic[n];
	for (int i=0;i<n;i++){
		node *temp=NULL;
		temp=(node *)malloc(sizeof(node));
		temp->check=false;
		scanf("%s",temp->s);
		//temp->next={NULL};		//初始化指针数组，确保全为空指针
		temp->occupy=0;				//已经建立的词链连接数 
		dic[i]=temp; 
	}
	for (int i=0;i<n-1;i++){
		for (int j=i+1;j<n;j++){
			link(dic[i],dic[j]);	//两两判断单词之间是否存在包含关系 
		}
	}
	for (int i=0;i<n;i++){
		if (!dic[i]->check) search(dic[i],1);			//对每一个节点搜寻，找到最长路径 
	}
	printf("%d",maxlen);
	return 0;
}

/*
后续出现的错误以及更正：

在Dev-C++中编译成功但在在线评测系统（OJ）上编译失败，
这通常是因为本地编译器（如Dev-C++使用的GCC/MinGW）对C语言标准的检查相对宽松，
而OJ的编译器（如GCC）则采用了更严格的标准。错误信息指向了结构体类型的使用和指针类型不匹配问题。

错误原因分析：
结构体类型名使用问题：
错误未知的类型名‘node’表明编译器不认识node这个类型。
在代码中，虽然使用了typedef struct node {...} node;，
但在C语言中，结构体标签（struct node）和typedef定义的类型名（node）
在某些上下文或编译器设置下可能被视为不同的命名空间。
在线评测系统的编译器可能更严格遵循C标准，
要求在结构体内部使用struct node *来声明指向自身类型的指针，而不能直接使用node *。
你的代码中node *next[N];这行直接使用了node，编译器在解析结构体定义时，尚未完成typedef，因此不认识node。

指针类型不匹配：
错误assignment to ‘int *’ from incompatible pointer type ‘node *’和传递‘search’的
第 1 个参数时在不兼容的指针类型间转换，是因为编译器将next数组的元素错误地推断为int *类型，
而你的代码试图将node *类型的值赋给它或传递给期望node *参数的函数。
这根本上是由于上述类型名问题导致的连锁反应。

解决方案： 
修正结构体内的指针声明：
将结构体中next数组成员的数据类型从node *改为struct node *。这是最关键的修改，它明确了类型。
*/ 
