#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id): _id(id) {}

void GraphNode::AddToken(std::string token)
{
    this->_answers.emplace_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    this->_parentEdges.emplace_back(edge);
}

void GraphNode::AddEdgeToChildNode(unique_ptr<GraphEdge> edge)
{
    this->_childEdges.emplace_back(std::move(edge));
}

void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    this->_chatBot = std::move(chatbot);
    this->_chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(std::move(this->_chatBot)); // move chatbot to newNode
}

GraphEdge* GraphNode::GetChildEdgeAtIndex(int index)
{
    return this->_childEdges[index].get();
}
