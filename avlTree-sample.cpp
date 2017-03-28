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
	printf("��ʼ�������ƽ�������_______________\n");
	zBBT.BBTInOrderTraverse(visit);
	printf("\n\n");
	printf("��ʼ�ڲ��Բ��ҹ���!!!:_______________\n");
	ZMath_BBTNode<int> * pBBTNode = NULL;
	pBBTNode = zBBT.BBTSearchNode(101);
	if ( pBBTNode )
	{
		printf("zBBT.BBTSearchNode(101)->tValue���Ϊ%d:\n",pBBTNode->t);
	}
	else
	{
		printf("zBBT.BBTSearchNode(101)->tValue���ʧ��!\n");
	}
	pBBTNode = zBBT.BBTSearchNode(25);
	if ( pBBTNode )
	{
		printf("zBBT.BBTSearchNode(25)->tValue���Ϊ%d:\n",pBBTNode->t);
	}
	else
	{
		printf("zBBT.BBTSearchNode(25)->tValue���ʧ��!\n");
	}
	printf("���Բ��ҹ������!!!!!:_______________\n\n");
	printf("����ɾ������__________________________\n");
	for (i=20;i>=0;i--)
	{
		printf("��ʼɾ���ڵ�:%2d\n",i);
		pBBTNode = zBBT.BBTDeleteNode(i);
		printf("ɾ�����������������:");
		zBBT.BBTInOrderTraverse();
		printf("\n");
		if (pBBTNode)
		{
			delete pBBTNode;
			pBBTNode = NULL;
		}
	}
	printf("����ɾ������__________________________\n");
	return 0;
}




