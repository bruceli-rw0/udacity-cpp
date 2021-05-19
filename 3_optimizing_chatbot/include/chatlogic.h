#ifndef CHATLOGIC_H_
#define CHATLOGIC_H_

#include <vector>
#include <string>
#include <memory>
#include "chatgui.h"
#include "chatbot.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::unique_ptr;

// forward declarations
// class ChatBot;
class GraphEdge;
class GraphNode;

class ChatLogic
{
private:
    //// STUDENT CODE
    ////

    // data handles (owned)
    vector<shared_ptr<GraphNode>> _nodes;

    ////
    //// EOF STUDENT CODE

    // data handles (not owned)
    ChatBot* _chatBot;
    ChatBotPanelDialog *_panelDialog;

    // proprietary type definitions
    typedef vector<std::pair<string, string>> tokenlist;

    // proprietary functions
    template <typename T>
    void AddAllTokensToElement(string tokenID, tokenlist &tokens, T &element);

public:
    // constructor / destructor
    ChatLogic();
    ~ChatLogic();

    // getter / setter
    void SetPanelDialogHandle(ChatBotPanelDialog *panelDialog);
    void SetChatbotHandle(ChatBot *chatbot);

    // proprietary functions
    void LoadAnswerGraphFromFile(string filename);
    void SendMessageToChatbot(string message);
    void SendMessageToUser(string message);
    wxBitmap* GetImageFromChatbot();
};

#endif /* CHATLOGIC_H_ */
