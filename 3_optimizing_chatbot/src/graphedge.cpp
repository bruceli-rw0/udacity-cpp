#include "graphnode.h"
#include "graphedge.h"

GraphEdge::GraphEdge(int id): _id(id) {}

void GraphEdge::SetChildNode(shared_ptr<GraphNode> childNode)
{
    this->_childNode = childNode;
}

void GraphEdge::AddToken(string token)
{
    this->_keywords.emplace_back(token);
}
