#ifndef CHATBOT_H_
#define CHATBOT_H_

#include <wx/bitmap.h>
#include <string>
#include <memory>
using std::string;
using std::shared_ptr;

class GraphNode; // forward declaration
class ChatLogic; // forward declaration

class ChatBot
{
private:
    // data handles (owned)
    wxBitmap *_image; // avatar image

    // data handles (not owned)
    shared_ptr<GraphNode> _currentNode;
    shared_ptr<GraphNode> _rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(string s1, string s2);

public:
    // constructors / destructors
    ChatBot();                     // constructor WITHOUT memory allocation
    ChatBot(string filename); // constructor WITH memory allocation
    ~ChatBot();

    //// STUDENT CODE
    ////

    ChatBot(ChatBot &&source); // move constructor
    ChatBot& operator=(ChatBot &&source); // move assignment operator

    ////
    //// EOF STUDENT CODE

    // getters / setters
    void SetCurrentNode(shared_ptr<GraphNode> node);
    void SetRootNode(shared_ptr<GraphNode> rootNode) { this->_rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { this->_chatLogic = chatLogic; }
    ChatLogic* GetChatLogicHandle() { return _chatLogic; }
    wxBitmap* GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(string message);
};

#endif /* CHATBOT_H_ */
