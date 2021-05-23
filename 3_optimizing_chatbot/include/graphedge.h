#ifndef GRAPHEDGE_H_
#define GRAPHEDGE_H_

#include <vector>
#include <string>
#include <memory>
using std::string;
using std::vector;

class GraphNode; // forward declaration

class GraphEdge
{
private:
    // data handles (not owned)
    GraphNode *_childNode;
    GraphNode *_parentNode;

    // proprietary members
    int _id;
    vector<string> _keywords; // list of topics associated with this edge
    

public:
    // constructor / desctructor
    GraphEdge(int id);

    // getter / setter
    int GetID() { return _id; }
    void SetChildNode(GraphNode *childNode);
    void SetParentNode(GraphNode *parentNode);
    GraphNode* GetChildNode() { return this->_childNode; }
    vector<string> GetKeywords() { return this->_keywords; }

    // proprietary functions
    void AddToken(string token);
};

#endif /* GRAPHEDGE_H_ */
