#include "graphnode.h"
#include "graphedge.h"

GraphEdge::GraphEdge(int id): _id(id) {}

void GraphEdge::SetChildNode(GraphNode *childNode)
{
    this->_childNode = childNode;
}

void GraphEdge::SetParentNode(GraphNode *parentNode)
{
    this->_parentNode = parentNode;
}

void GraphEdge::AddToken(string token)
{
    this->_keywords.emplace_back(token);
}
