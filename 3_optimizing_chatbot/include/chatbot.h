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
    GraphNode *_currentNode;
    GraphNode *_rootNode;
    ChatLogic *_chatLogic;

    // proprietary functions
    int ComputeLevenshteinDistance(string s1, string s2);

public:
    // constructors / destructors
    ChatBot();                // constructor WITHOUT memory allocation
    ChatBot(string filename); // constructor WITH memory allocation
    ~ChatBot();

    // rule of five
    ChatBot(ChatBot &source); // copy constructor
    ChatBot& operator=(ChatBot &source); // copy assignment operator
    ChatBot(ChatBot &&source); // move constructor
    ChatBot& operator=(ChatBot &&source); // move assignment operator

    // getters / setters
    void SetCurrentNode(GraphNode *node);
    void SetRootNode(GraphNode *rootNode) { this->_rootNode = rootNode; }
    void SetChatLogicHandle(ChatLogic *chatLogic) { this->_chatLogic = chatLogic; }
    ChatLogic* GetChatLogicHandle() { return _chatLogic; }
    wxBitmap* GetImageHandle() { return _image; }

    // communication
    void ReceiveMessageFromUser(string message);
};

#endif /* CHATBOT_H_ */
