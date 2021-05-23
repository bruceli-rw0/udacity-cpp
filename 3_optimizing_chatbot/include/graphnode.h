#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>
#include "chatbot.h"
using std::string;
using std::vector;
using std::unique_ptr;

// forward declarations
class GraphEdge;

class GraphNode
{
private:
    // data handles (owned)
    vector<unique_ptr<GraphEdge>> _childEdges;  // edges to subsequent nodes

    // data handles (not owned) 
    vector<GraphEdge *> _parentEdges;  // edges to preceding nodes 
    ChatBot _chatBot;

    // proprietary members
    int _id;
    vector<string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode() {};

    // getter / setter
    int GetID() { return this->_id; }
    int GetNumberOfChildEdges() { return this->_childEdges.size(); }
    GraphEdge* GetChildEdgeAtIndex(int index);
    vector<string> GetAnswers() { return this->_answers; }

    // proprietary functions
    void AddToken(string token); // add answers to list
    void AddEdgeToParentNode(GraphEdge *edge);
    void AddEdgeToChildNode(unique_ptr<GraphEdge> edge);

    void MoveChatbotHere(ChatBot chatbot);
    void MoveChatbotToNewNode(GraphNode* newNode);
};

#endif /* GRAPHNODE_H_ */
