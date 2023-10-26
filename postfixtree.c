#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h> // for isdigit()
		   //
		   // // 定义表达式树节点结构体
		   // struct ExpressionTreeNode {
		   //     char data;
		   //         struct ExpressionTreeNode* left;
		   //             struct ExpressionTreeNode* right;
		   //             };
		   //
		   //             // 创建一个新的表达式树节点
		   //             struct ExpressionTreeNode* createNode(char data) {
		   //                 struct ExpressionTreeNode* newNode = (struct ExpressionTreeNode*)malloc(sizeof(struct ExpressionTreeNode));
		   //                     if (newNode) {
		   //                             newNode->data = data;
		   //                                     newNode->left = NULL;
		   //                                             newNode->right = NULL;
		   //                                                 }
		   //                                                     return newNode;
		   //                                                     }
		   //
		   //                                                     // 判断字符是否为操作符
		   //                                                     bool isOperator(char c) {
		   //                                                         return (c == '+' || c == '-' || c == '*' || c == '/');
		   //                                                         }
		   //
		   //                                                         // 创建表达式树
		   //                                                         struct ExpressionTreeNode* buildExpressionTree(char postfix[]) {
		   //                                                             struct ExpressionTreeNode* stack[100]; // 假设表达式不超过100个字符
		   //                                                                 int top = -1; // 栈顶指针初始化为-1
		   //
		   //                                                                     for (int i = 0; postfix[i] != '\0'; i++) {
		   //                                                                             struct ExpressionTreeNode* newNode = createNode(postfix[i]);
		   //
		   //                                                                                     if (isdigit(postfix[i])) {
		   //                                                                                                 stack[++top] = newNode; // 操作数入栈
		   //                                                                                                         } else if (isOperator(postfix[i])) {
		   //                                                                                                                     newNode->right = stack[top--]; // 第一个操作数出栈并作为右子树
		   //                                                                                                                                 newNode->left = stack[top--]; // 第二个操作数出栈并作为左子树
		   //                                                                                                                                             stack[++top] = newNode; // 新节点入栈
		   //                                                                                                                                                     }
		   //                                                                                                                                                         }
		   //
		   //                                                                                                                                                             return stack[top]; // 返回根节点
		   //                                                                                                                                                             }
		   //
		   //                                                                                                                                                             // 计算表达式树的值
		   //                                                                                                                                                             int evaluateExpressionTree(struct ExpressionTreeNode* root) {
		   //                                                                                                                                                                 if (root->data >= '0' && root->data <= '9') {
		   //                                                                                                                                                                         return root->data - '0'; // 叶子节点是操作数，直接返回其整数值
		   //                                                                                                                                                                             }
		   //
		   //                                                                                                                                                                                 int leftValue = evaluateExpressionTree(root->left);
		   //                                                                                                                                                                                     int rightValue = evaluateExpressionTree(root->right);
		   //
		   //                                                                                                                                                                                         switch (root->data) {
		   //                                                                                                                                                                                                 case '+':
		   //                                                                                                                                                                                                             return leftValue + rightValue;
		   //                                                                                                                                                                                                                     case '-':
		   //                                                                                                                                                                                                                                 return leftValue - rightValue;
		   //                                                                                                                                                                                                                                         case '*':
		   //                                                                                                                                                                                                                                                     return leftValue * rightValue;
		   //                                                                                                                                                                                                                                                             case '/':
		   //                                                                                                                                                                                                                                                                         return leftValue / rightValue;
		   //                                                                                                                                                                                                                                                                                 default:
		   //                                                                                                                                                                                                                                                                                             printf("Error: Invalid operator\n");
		   //                                                                                                                                                                                                                                                                                                         return 0;
		   //                                                                                                                                                                                                                                                                                                             }
		   //                                                                                                                                                                                                                                                                                                             }
		   //
		   //                                                                                                                                                                                                                                                                                                             // 释放表达式树的内存
		   //                                                                                                                                                                                                                                                                                                             void freeExpressionTree(struct ExpressionTreeNode* root) {
		   //                                                                                                                                                                                                                                                                                                                 if (root == NULL) {
		   //                                                                                                                                                                                                                                                                                                                         return;
		   //                                                                                                                                                                                                                                                                                                                             }
		   //
		   //                                                                                                                                                                                                                                                                                                                                 freeExpressionTree(root->left);
		   //                                                                                                                                                                                                                                                                                                                                     freeExpressionTree(root->right);
		   //                                                                                                                                                                                                                                                                                                                                         free(root);
		   //                                                                                                                                                                                                                                                                                                                                         }
		   //
		   //                                                                                                                                                                                                                                                                                                                                         // 测试代码
		   //                                                                                                                                                                                                                                                                                                                                         int main() {
		   //                                                                                                                                                                                                                                                                                                                                             char postfix[] = "34+2*"; // 后缀表达式 3 + 4 * 2
		   //
		   //                                                                                                                                                                                                                                                                                                                                                 struct ExpressionTreeNode* root = buildExpressionTree(postfix);
		   //                                                                                                                                                                                                                                                                                                                                                     int result = evaluateExpressionTree(root);
		   //
		   //                                                                                                                                                                                                                                                                                                                                                         printf("Result of the expression: %d\n", result);
		   //
		   //                                                                                                                                                                                                                                                                                                                                                             freeExpressionTree(root);
		   //                                                                                                                                                                                                                                                                                                                                                                 return 0;
		   //                                                                                                                                                                                                                                                                                                                                                                 }
