#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id): _id(id) {}

GraphNode::~GraphNode()
{
    //// STUDENT CODE
    ////

    // delete _chatBot;

    ////
    //// EOF STUDENT CODE
}

void GraphNode::AddToken(std::string token)
{
    this->_answers.emplace_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    this->_parentEdges.emplace_back(edge);
}

void GraphNode::AddEdgeToChildNode(GraphEdge *edge)
{
    this->_childEdges.emplace_back(edge);
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    _chatBot = chatbot;
    _chatBot->SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    newNode->MoveChatbotHere(_chatBot); // move chatbot to newNode
    this->_chatBot = nullptr; // invalidate pointer at source
}
////
//// EOF STUDENT CODE

GraphEdge* GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    return this->_childEdges[index];

    ////
    //// EOF STUDENT CODE
}
