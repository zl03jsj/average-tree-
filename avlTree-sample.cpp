#include "avltree.h"
#include <stdio.h>


int cmp(const int &t1,const int &t2)
{
	if (t1>t2)
	{
		return lh;
	}
	else if (t1<t2)
	{
		return rh;
	}
	else
	{
		return eh;
	}
}

void visit(const int &t)
{
	printf("%2d,",t);	
};

#define Z_DELETE_TAG "!Z_DELETE_TAG!"
#define ZPDF_SIGN_CONTENT_STRING ""##Z_DELETE_TAG"123"

int main(void)
{
	printf(ZPDF_SIGN_CONTENT_STRING);

	ZMath_BBT<int> zBBT(cmp,visit);
	for (int i=0;i<28;i++)
	{
		zBBT.BBTInsertNode(i);
	}
	printf("开始中序遍历平衡二叉树_______________\n");
	zBBT.BBTInOrderTraverse(visit);
	printf("\n\n");
	printf("开始在测试查找功能!!!:_______________\n");
	ZMath_BBTNode<int> * pBBTNode = NULL;
	pBBTNode = zBBT.BBTSearchNode(101);
	if ( pBBTNode )
	{
		printf("zBBT.BBTSearchNode(101)->tValue结果为%d:\n",pBBTNode->t);
	}
	else
	{
		printf("zBBT.BBTSearchNode(101)->tValue结果失败!\n");
	}
	pBBTNode = zBBT.BBTSearchNode(25);
	if ( pBBTNode )
	{
		printf("zBBT.BBTSearchNode(25)->tValue结果为%d:\n",pBBTNode->t);
	}
	else
	{
		printf("zBBT.BBTSearchNode(25)->tValue结果失败!\n");
	}
	printf("测试查找功能完成!!!!!:_______________\n\n");
	printf("测试删除功能__________________________\n");
	for (i=20;i>=0;i--)
	{
		printf("开始删除节点:%2d\n",i);
		pBBTNode = zBBT.BBTDeleteNode(i);
		printf("删除后中序遍历二叉树:");
		zBBT.BBTInOrderTraverse();
		printf("\n");
		if (pBBTNode)
		{
			delete pBBTNode;
			pBBTNode = NULL;
		}
	}
	printf("测试删除功能__________________________\n");
	return 0;
}




