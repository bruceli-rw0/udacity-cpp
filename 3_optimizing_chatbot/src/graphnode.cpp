#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id): _id(id) {}

GraphNode::~GraphNode() {}

void GraphNode::AddToken(std::string token)
{
    this->_answers.emplace_back(token);
}

void GraphNode::AddEdgeToChildNode(unique_ptr<GraphEdge> edge)
{
    this->_childEdges.emplace_back(std::move(edge));
}

//// STUDENT CODE
////
void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
    this->_chatBot = std::move(chatbot);
    this->_chatBot.SetCurrentNode(shared_from_this());
}

void GraphNode::MoveChatbotToNewNode(shared_ptr<GraphNode> newNode)
{
    newNode->MoveChatbotHere(std::move(this->_chatBot)); // move chatbot to newNode
}
////
//// EOF STUDENT CODE

reference_wrapper<const unique_ptr<GraphEdge>> GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////

    return this->_childEdges[index];

    ////
    //// EOF STUDENT CODE
}
