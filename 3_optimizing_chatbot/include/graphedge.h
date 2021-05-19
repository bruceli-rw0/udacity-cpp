#ifndef GRAPHEDGE_H_
#define GRAPHEDGE_H_

#include <vector>
#include <string>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr;

class GraphNode; // forward declaration

class GraphEdge
{
private:
    // data handles (not owned)
    shared_ptr<GraphNode> _childNode;

    // proprietary members
    int _id;
    vector<string> _keywords; // list of topics associated with this edge
    

public:
    // constructor / desctructor
    GraphEdge(int id);

    // getter / setter
    int GetID() { return _id; }
    void SetChildNode(shared_ptr<GraphNode> childNode);
    shared_ptr<GraphNode> GetChildNode() { return this->_childNode; }
    vector<string> GetKeywords() { return this->_keywords; }

    // proprietary functions
    void AddToken(string token);
};

#endif /* GRAPHEDGE_H_ */
