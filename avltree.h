/******************************************
// 文件名称:avltree.h
// 文件描述:平衡二叉查找树,插入,删除,遍历!!!!
// 版本信息:2010-11-11 21:58:48 By zl
// 电子邮箱:88911562@qq.com
//			 _____________________
//__________|平衡二叉树性质说明!!!|______________________________________
//	1:假设平衡二叉树的节点数量为N,其深度为log^N同数量级;
//	其平均查找长度,平均插入长度,平均删除长度,也都与log^N同数量级
//
//	2:(*CMPPROC)(const T &t1,const T &t2),比较T大小的函数类型指针
//	按[**t1>t2,CMPPROC返回1|t1<t2,CMPPROC返回-1|t1=t2,CMPPROC返回0**]的规则
//  先左后右中序遍历,可以实现从小到大的排序
//	先右后左中序遍历,可以实现从大到大的排序
//////////////////////////////////////////////////////////////////////////
******************************************/
#ifndef avltree_h__
#define avltree_h__
#include <memory.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

//#define Z_DebugOutPut	1
#define lh	1	//左高
#define eh	0	//等高
#define rh -1	//右高

template <typename T>
struct ZMath_BBTNode
{
	T t;	//数据
	int bf;	//平衡因子
	ZMath_BBTNode<T> *p_lc, *p_rc;
};

template <typename T>
class ZMath_BBT
{
	typedef int  (*CMPPROC)(const T &,const T &);
	typedef void (*VISIT)(const T &);
public:
	//cmpPtr:int cmp(t1,t2){ (t1>t2 return 1;)  (t1<t2 return -1;) (t1==t2 return 0;)}
	ZMath_BBT(CMPPROC cmpPtr=NULL,VISIT visit=NULL);
	~ZMath_BBT(){BBTClear();};
	ZMath_BBTNode<T> * BBTInsertNode(const T & t);
	ZMath_BBTNode<T> * BBTSearchNode(const T & t);
	ZMath_BBTNode<T> * BBTDeleteNode(const T & t);
	void BBTInOrderTraverse();
	void BBTInOrderTraverse(VISIT customVisit);
	void BBTClear();
protected:
	void Clear(ZMath_BBTNode<T>* &nodePtr);
	void InOrderTraverse(ZMath_BBTNode<T> * nodePtr);
	void InOrderTraverse(ZMath_BBTNode<T> * nodePtr,VISIT customVist);
	void l_rotate (ZMath_BBTNode<T> * &nodePtr);
	void r_rotate (ZMath_BBTNode<T> * &nodePtr);
	void l_balance(ZMath_BBTNode<T> * &nodePtr);
	void r_balance(ZMath_BBTNode<T> * &nodePtr);
	void rdel_balance(ZMath_BBTNode<T> * &nodePtr,bool &shorter);
	void ldel_balance(ZMath_BBTNode<T> * &nodePtr,bool &shorter);
	ZMath_BBTNode<T> * DeleteNode(ZMath_BBTNode<T> * &nodePtr,const T & t,bool &shorter);
	ZMath_BBTNode<T> * CreateNode(const T & t);
	ZMath_BBTNode<T> * InsertNode(ZMath_BBTNode<T>* & nodePtr,const T & t,bool & taller);
	ZMath_BBTNode<T> * SearchNode(const T & t,const ZMath_BBTNode<T> * nodePtr);
protected:
	ZMath_BBTNode<T> * _pRootNode;
	CMPPROC _cmpPtr;
	VISIT	_visit;
};

template <typename T>
ZMath_BBTNode<T> * ZMath_BBT<T>::BBTDeleteNode(const T & t)
{
	ZMath_BBTNode<T> * nodePtr = NULL;
	bool shorter = false;
	nodePtr = DeleteNode(_pRootNode,t,shorter);
	return nodePtr;
}

template <typename T>
void ZMath_BBT<T>::ldel_balance(ZMath_BBTNode<T> * &nodePtr,bool &shorter)
{
    ZMath_BBTNode<T> * p_lc = nodePtr->p_lc;
    switch ( p_lc->bf )
    {
	case lh:
		nodePtr->bf = p_lc->bf = eh;
		r_rotate(nodePtr);
        break;
    case rh:
		{
			ZMath_BBTNode<T> * p_rd = p_lc->p_rc;
			switch( p_rd->bf )
			{
			case lh:
				{
					nodePtr->bf=rh;
					p_lc->bf=eh;
					break;
				}
			case eh:
				{
					nodePtr->bf = p_lc->bf = eh;
				}
				break;
			case rh:
				{
					nodePtr->bf=eh;
					p_lc->bf=lh;
				}
				break;
			}
			p_rd->bf=eh;
			l_rotate(p_lc);
			r_rotate(nodePtr);
		}
        break;
    case eh:
		shorter = false;
        nodePtr->bf = lh;
        p_lc->bf = rh;
        r_rotate(nodePtr);
        break;
    }
}

template <typename T>
void ZMath_BBT<T>::rdel_balance(ZMath_BBTNode<T> * &nodePtr,bool &shorter)
{
    ZMath_BBTNode<T> * p_rc = nodePtr->p_rc;
    switch ( p_rc->bf )
    {
	case lh:
		{
			ZMath_BBTNode<T> * p_rd = p_rc->p_rc;
			switch( p_rd->bf )
			{
			case lh:
				{
					nodePtr->bf=rh;
					p_rc->bf=eh;
					break;
				}
			case eh:
				{
					nodePtr->bf = p_rc->bf = eh;
				}
				break;
			case rh:
				{
					nodePtr->bf=eh;
					p_rc->bf=lh;
				}
				break;
			}
			p_rd->bf=eh;
			r_rotate(p_rc);
			l_rotate(nodePtr);
		}

        break;
    case rh:
		{
			nodePtr->bf = p_rc->bf = eh;
			l_rotate(nodePtr);
		}
        break;
    case eh:
		shorter = false;
        nodePtr->bf = rh;
        p_rc->bf = lh;
        l_rotate(nodePtr);
        break;
    }	
}

template <typename T>
ZMath_BBTNode<T> * ZMath_BBT<T>::DeleteNode(ZMath_BBTNode<T> * &nodePtr,const T & t,bool &shorter)
{
    if ( !nodePtr ) 
		return NULL;
	ZMath_BBTNode<T> * p_tNode = NULL;
	switch ( _cmpPtr(t, nodePtr->t) )
	{
	case eh:
		{
			if ( !nodePtr->p_lc && !nodePtr->p_rc )
			{
				shorter = true;
				p_tNode = nodePtr;
				nodePtr = NULL;	
			}
			else if ( nodePtr->p_lc && !nodePtr->p_rc )
			{
				shorter = true;
				p_tNode = nodePtr;
				nodePtr = nodePtr->p_lc;
			}
			else if ( !nodePtr->p_lc && nodePtr->p_rc )
			{
				shorter = true;
				p_tNode = nodePtr;
				nodePtr = nodePtr->p_rc;
			}
			else if ( nodePtr->p_lc && nodePtr->p_rc )
			{
				T t_temp;
				ZMath_BBTNode<T> * p_loopNode = nodePtr->p_rc;;
				while (p_loopNode->p_lc)
				{
					p_loopNode = p_loopNode->p_lc;
				}
				//与其右子树中最小的节点交换值!!!!
				memcpy(&t_temp,	&nodePtr->t, sizeof(T));
				memcpy(&nodePtr->t, &p_loopNode->t, sizeof(T));
				memcpy(&p_loopNode->t, &t_temp, sizeof(T));
				//在右子树中查找节点!!
				p_tNode = DeleteNode(nodePtr->p_rc, t, shorter);
				if ( shorter )
				{
					switch ( nodePtr->bf )
					{
					case lh:
						ldel_balance(nodePtr, shorter);
						break;
					case rh:
						nodePtr->bf = eh;
						break;
					case eh:
						shorter = false;
						nodePtr->bf = lh;
						break;
					}
				}
			}
		}
		break;
	case lh:
		{
			p_tNode = DeleteNode(nodePtr->p_rc, t, shorter);
			if ( shorter )
			{
				switch ( nodePtr->bf )
				{
				case lh:
					ldel_balance(nodePtr,shorter);
					break;
				case rh:
					nodePtr->bf = eh;
					break;
				case eh:
					shorter = false;
					nodePtr->bf = lh;
					break;
				}
			}
		}
		break;
	case rh:
		{
			p_tNode = DeleteNode(nodePtr->p_lc, t, shorter);
			if ( shorter ) 
			{
				switch (nodePtr->bf)
				{
				case lh:
					nodePtr->bf = eh;
					break;
				case rh:
					rdel_balance(nodePtr,shorter);
					break;
				case eh:
					shorter = false;
					nodePtr->bf = rh;
					break;
				}
			}
		}
		break;
	}
	return p_tNode;
}
template <typename T>
void ZMath_BBT<T>::BBTClear()
{
#ifdef Z_DebugOutPut
	printf("开始按后序遍历删除节点!______________\n");
#endif
	Clear(_pRootNode);
#ifdef Z_DebugOutPut
	printf("\n按后序遍历删除节点完成!______________\n");
#endif
}

template <typename T>
void ZMath_BBT<T>::Clear(ZMath_BBTNode<T>* &nodePtr)
{
	if ( nodePtr )
	{
		if ( nodePtr->p_lc )
		{
			Clear(nodePtr->p_lc);
		}
		if ( nodePtr->p_rc )
		{
			Clear(nodePtr->p_rc);
		}
#ifdef Z_DebugOutPut 
		_visit(nodePtr->t);
#endif
		delete nodePtr;
		nodePtr = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
//			 __________________________
//__________|遍历平衡树使用默认访问方法|______________________________________
template <typename T>
void ZMath_BBT<T>::BBTInOrderTraverse()
{
	if ( !_visit )
	{
		return ;
	}
	InOrderTraverse(_pRootNode);
}

template <typename T>
void ZMath_BBT<T>::InOrderTraverse(ZMath_BBTNode<T> * nodePtr)
{
	if ( !nodePtr )
	{
		return ;
	}
	if ( nodePtr->p_lc )
	{
		InOrderTraverse(nodePtr->p_lc);
	}
	_visit(nodePtr->t);
	if ( nodePtr->p_rc )
	{
		InOrderTraverse(nodePtr->p_rc);
	}
}
//////////////////////////////////////////////////////////////////////////
//			 __________________________
//__________|遍历平衡树使用其它访问方法|______________________________________
template <typename T>
void ZMath_BBT<T>::BBTInOrderTraverse(VISIT customVisit)
{
	if ( !customVisit )
	{
		return ;
	}
	InOrderTraverse(_pRootNode,customVisit);
}
template <typename T>
void ZMath_BBT<T>::InOrderTraverse(ZMath_BBTNode<T> * nodePtr,VISIT visit)
{
	if ( !nodePtr )
	{
		return;
	}
	if ( nodePtr->p_lc )
	{
		InOrderTraverse(nodePtr->p_lc,visit);
	}
	visit(nodePtr->t);
	if ( nodePtr->p_rc )
	{
		InOrderTraverse(nodePtr->p_rc,visit);
	}	
}

template <typename T>
ZMath_BBTNode<T> * ZMath_BBT<T>::BBTSearchNode(const T & t)
{
	return SearchNode(t,_pRootNode);
}

template <typename T>
ZMath_BBTNode<T> * ZMath_BBT<T>::SearchNode(const T &t,const ZMath_BBTNode<T> * nodePtr)
{
	ZMath_BBTNode<T> * pt = NULL;
	if ( NULL==nodePtr )
	{
		pt = NULL;
	}
	else
	{
		switch( _cmpPtr(t, nodePtr->t) )
		{
		case lh:
			{
				pt = SearchNode(t,nodePtr->p_rc);
			}
			break;
		case rh:
			{
				pt = SearchNode(t,nodePtr->p_lc);
			}
			break;
		case eh:
			{
				pt = (ZMath_BBTNode<T>*)nodePtr;
			}
			break;
		}
	}
	return pt;
}


template <typename T>
ZMath_BBTNode<T> * ZMath_BBT<T>::BBTInsertNode(const T & t)
{
	ZMath_BBTNode<T> * nodePtr = NULL;
	bool taller = false;
	
	if ( _pRootNode==NULL )
	{
		nodePtr = CreateNode(t);
		_pRootNode = nodePtr;
	}
	else
	{
		nodePtr = InsertNode(_pRootNode, t, taller);
	}
	return nodePtr;
}

template <typename T>
ZMath_BBTNode<T> * ZMath_BBT<T>::InsertNode(ZMath_BBTNode<T>* & nodePtr,const T & t,bool & taller)
{
	ZMath_BBTNode<T>* t_nodePtr = NULL;
	if( !nodePtr )
	{
		t_nodePtr = nodePtr = CreateNode(t);
		taller = true;
	}
	else
	{
		switch( _cmpPtr(t,nodePtr->t) )
		{
		case lh:
			{
				t_nodePtr = InsertNode(nodePtr->p_rc,t,taller) ;
				if ( t_nodePtr && taller )
				{
					switch( nodePtr->bf )
					{
					case lh:
						{
							nodePtr->bf = eh;
							taller = false;
						}
						break;
					case rh:
						{
							r_balance(nodePtr);
							nodePtr->bf = eh;
							taller = false;			
						}
						break;
					case eh:
						{
							nodePtr->bf = rh;
							taller = true;
						}
						break;
					}
				}
			}
			break;
		case rh:
			{
				t_nodePtr = InsertNode(nodePtr->p_rc,t,taller) ;
				if ( t_nodePtr && taller )
				{
					switch( nodePtr->bf )
					{
					case lh:
						{
							l_balance(nodePtr);
							nodePtr->bf = eh;
							taller = false;
							
						}
						break;
					case rh:
						{
							nodePtr->bf = eh;
							taller = false;
						}
						break;
					case eh:
						{
							nodePtr->bf = lh;
							taller = true;
						}
						break;
					}
				}
			}
			break;
		case eh:
			{
				t_nodePtr = NULL;
				taller = false;
			}
			break;
		}
	}
	return t_nodePtr;
}

template <typename T>
ZMath_BBTNode<T> * ZMath_BBT<T>::CreateNode(const T & t)
{
	ZMath_BBTNode<T> * pBSTNode = new ZMath_BBTNode<T>;
	pBSTNode->bf = eh;
	pBSTNode->p_lc = NULL;
	pBSTNode->p_rc = NULL;
	memcpy(pBSTNode, &t, sizeof(T));
	return pBSTNode;
}

template <typename T>
ZMath_BBT<T>::ZMath_BBT(CMPPROC cmpPtr/*=NULL*/,VISIT visit/*=NULL*/)
{
	_cmpPtr = cmpPtr;
	_visit = visit;
	_pRootNode = NULL;
}

template <typename T>
void ZMath_BBT<T>::l_balance(ZMath_BBTNode<T> * &nodePtr)
{
    ZMath_BBTNode<T> * lc = nodePtr->p_lc;
    switch(lc->bf)
    {
    case lh:
		{
			nodePtr->bf = lc->bf = eh;
			r_rotate( nodePtr );
		}
        break;
    case rh:
		{
			ZMath_BBTNode<T> * rd = lc->p_rc;
			switch( rd->bf )
			{
			case lh:
				{
					nodePtr->bf=rh;
					lc->bf=eh;
					break;
				}
			case eh:
				{
					nodePtr->bf = lc->bf = eh;
				}
				break;
			case rh:
				{
					nodePtr->bf=eh;
					lc->bf=lh;
				}
				break;
			}
			rd->bf=eh;
			l_rotate( nodePtr->p_lc );
			r_rotate( nodePtr );
		}
        break;
    }		
}

template <typename T>
void ZMath_BBT<T>::r_balance(ZMath_BBTNode<T> * &nodePtr)
{
	ZMath_BBTNode<T> * rc = nodePtr->p_rc;
	switch( nodePtr->bf )
	{
	case rh:
		{
			nodePtr->bf = rc->bf=eh;
			l_rotate(nodePtr);
			break;
		}
		break;
	case lh:
		{
			ZMath_BBTNode<T> * ld = rc->p_lc;
			switch(ld->bf)
			{
			case rh:
				{
					nodePtr->bf = lh;
					rc->bf = eh;
				}
				break;
			case eh:
				{
					nodePtr->bf = rc->bf = eh;
				}

				break;
			case lh:
				{
					nodePtr->bf = eh;
					rc->bf = rh;
				}
				break;
			}
			ld->bf=eh;
			r_rotate( nodePtr->p_rc );
			l_rotate( nodePtr );
		}
		break;
	}
}
template <typename T>
void ZMath_BBT<T>::l_rotate(ZMath_BBTNode<T> * &nodePtr)
{
	ZMath_BBTNode<T> * p_rc = nodePtr->p_rc;
	nodePtr->p_rc = p_rc->p_lc;
	p_rc->p_lc = nodePtr;
	nodePtr = p_rc;
}
template <typename T>
void ZMath_BBT<T>::r_rotate(ZMath_BBTNode<T> * &nodePtr)
{
	ZMath_BBTNode<T> * p_lc = nodePtr->p_lc;
	nodePtr->p_lc = p_lc->p_rc;
	p_lc->p_rc = nodePtr;
	nodePtr = p_lc;
}
#endif // avltree_h__



//非递归中序遍历
//void InOrderTraverseWithNoRecursive(ZMath_BBTNode<T> * nodePtr);
// template <typename T>
// void ZMath_BBT<T>::InOrderTraverseWithNoRecursive(ZMath_BBTNode<T> * nodePtr)
// {
// 	while ( nodePtr || !StackEmpty(s) )
// 	{
// 		if (nodePtr)
// 		{
// 			Push(nodePtr);
// 			nodePtr = nodePtr->p_lchild;
// 		}
// 		else
// 		{
// 			_visit( Pop(s) );
// 			nodePtr = nodePtr->p_rchild;
// 		}
// 	}
// }

