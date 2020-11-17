#pragma once

#include "GraphNode.h"
#include "NodeData.h"
#include <queue>
#include <list>

template<class NodeType, class ArcType>
class NodeComparator
{
public:
	bool operator()(GraphNode<NodeType, ArcType>* n1, GraphNode<NodeType, ArcType>* n2)
	{
		//Compearer for Priority Que
		return (n1->m_data.m_g + n1->m_data.m_h) > (n2->m_data.m_g + n2->m_data.m_h);

	}
};