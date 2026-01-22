/*
题目描述
输入一串二叉树，输出其前序遍历。

输入格式
第一行为二叉树的节点数 n。(1≤n≤26)
后面 n 行，第一个字母为节点，后两个字母分别为其左右儿子。
特别地，数据保证第一行读入的节点必为根节点。
空节点用 * 表示

输出格式
二叉树的前序遍历。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char c;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* nodes[256] = {NULL}; // 映射表：字符索引指向节点指针
TreeNode* root = NULL; // 全局根节点

// 前序遍历函数
void preorder(TreeNode* node) {
    if (node != NULL) {
        printf("%c", node->c); // 先输出根节点
        preorder(node->left);  // 然后左子树
        preorder(node->right); // 最后右子树[3,4](@ref)
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        char parent_char, left_char, right_char;
        // 读取一行输入：父节点、左孩子、右孩子
        scanf(" %c %c %c", &parent_char, &left_char, &right_char);
        
        // 获取或创建父节点
        TreeNode* parent = nodes[parent_char];
        if (parent == NULL) {
            parent = (TreeNode*)malloc(sizeof(TreeNode));
            parent->c = parent_char;
            parent->left = parent->right = NULL;
            nodes[parent_char] = parent;
            
            // 设置根节点（第一行输入的是根节点）
            if (root == NULL) {
                root = parent;
            }
        }
        
        // 处理左子节点
        if (left_char != '*') {
            TreeNode* left_child = nodes[left_char];
            if (left_child == NULL) {
                left_child = (TreeNode*)malloc(sizeof(TreeNode));
                left_child->c = left_char;
                left_child->left = left_child->right = NULL;
                nodes[left_char] = left_child;
            }
            parent->left = left_child;
        }
        
        // 处理右子节点（修正点）
        if (right_char != '*') {
            TreeNode* right_child = nodes[right_char];
            if (right_child == NULL) {
                right_child = (TreeNode*)malloc(sizeof(TreeNode));
                right_child->c = right_char;  // 修正：使用right_char而不是left_char
                right_child->left = right_child->right = NULL;
                nodes[right_char] = right_child;
            }
            parent->right = right_child;  // 修正：赋值给right而不是left
        }
    }
    
    // 执行前序遍历
    preorder(root);
    printf("\n"); // 输出换行符
    
    return 0;
}
