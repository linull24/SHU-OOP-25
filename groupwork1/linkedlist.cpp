#include <emscripten/bind.h>
#include <string>

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    
    void push(int val) {
        Node* node = new Node(val);
        node->next = head;
        head = node;
    }
    
    void append(int val) {
        Node* node = new Node(val);
        if (!head) {
            head = node;
            return;
        }
        Node* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = node;
    }
    
    std::string toString() {
        std::string result = "[";
        Node* curr = head;
        while (curr) {
            result += std::to_string(curr->data);
            if (curr->next) result += " -> ";
            curr = curr->next;
        }
        result += "]";
        return result;
    }
    
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    ~LinkedList() { clear(); }
};

EMSCRIPTEN_BINDINGS(linkedlist) {
    emscripten::class_<LinkedList>("LinkedList")
        .constructor<>()
        .function("push", &LinkedList::push)
        .function("append", &LinkedList::append)
        .function("toString", &LinkedList::toString)
        .function("clear", &LinkedList::clear);
}
