#ifndef GRAPHNODE_H_
#define GRAPHNODE_H_

#include <vector>
#include <string>
#include <memory>
#include "chatbot.h"
using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::reference_wrapper;

// forward declarations
class GraphEdge;

class GraphNode: public std::enable_shared_from_this<GraphNode>
{
private:
    //// STUDENT CODE
    ////

    // data handles (owned)
    vector<unique_ptr<GraphEdge>> _childEdges;  // edges to subsequent nodes

    // data handles (not owned) 
    ChatBot _chatBot;

    ////
    //// EOF STUDENT CODE

    // proprietary members
    int _id;
    vector<string> _answers;

public:
    // constructor / destructor
    GraphNode(int id);
    ~GraphNode();

    // getter / setter
    int GetID() { return this->_id; }
    int GetNumberOfChildEdges() { return this->_childEdges.size(); }
    reference_wrapper<const unique_ptr<GraphEdge>> GetChildEdgeAtIndex(int index);
    vector<string> GetAnswers() { return this->_answers; }

    // proprietary functions
    void AddToken(string token); // add answers to list
    void AddEdgeToChildNode(unique_ptr<GraphEdge> edge);

    //// STUDENT CODE
    ////

    void MoveChatbotHere(ChatBot chatbot);

    ////
    //// EOF STUDENT CODE

    void MoveChatbotToNewNode(shared_ptr<GraphNode> newNode);
};

#endif /* GRAPHNODE_H_ */
