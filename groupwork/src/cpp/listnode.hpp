#pragma once
#include <string>
#include <vector>

struct ListNode {
    int id;
    std::string value;
    ListNode* next;
    ListNode(int id, const std::string& val) : id(id), value(val), next(nullptr) {}
};

class LinkedList {
private:
    ListNode* head;
    int size, nextId;
    std::vector<ListNode*> registered;

public:
    LinkedList() : head(nullptr), size(0), nextId(1) {}
    ~LinkedList() { for (auto n : registered) delete n; }
    
    void insertHead(const std::string& value) {
        auto n = new ListNode(nextId++, value);
        n->next = head;
        head = n;
        registered.push_back(n);
        size++;
    }
    
    void insertTail(const std::string& value) {
        auto n = new ListNode(nextId++, value);
        if (!head) head = n;
        else {
            auto c = head;
            while (c->next) c = c->next;
            c->next = n;
        }
        registered.push_back(n);
        size++;
    }
    
    void insertAfterId(int targetId, const std::string& value) {
        auto c = head;
        while (c && c->id != targetId) c = c->next;
        if (!c) return;
        auto n = new ListNode(nextId++, value);
        n->next = c->next;
        c->next = n;
        registered.push_back(n);
        size++;
    }
    
    bool deleteById(int id) {
        if (!head) return false;
        if (head->id == id) { head = head->next; size--; return true; }
        auto c = head;
        while (c->next && c->next->id != id) c = c->next;
        if (c->next) { c->next = c->next->next; size--; return true; }
        return false;
    }
    
    void clear() {
        for (auto n : registered) delete n;
        head = nullptr;
        registered.clear();
        size = nextId = 0;
        nextId = 1;
    }
    
    int count() const { return size; }
    
    std::string getMinValue() const {
        if (!head) return "";
        std::string minVal = head->value;
        int minId = head->id;
        for (auto c = head->next; c; c = c->next)
            if (c->value < minVal) { minVal = c->value; minId = c->id; }
        return minVal + " (ID: " + std::to_string(minId) + ")";
    }
    
    std::string getMaxValue() const {
        if (!head) return "";
        std::string maxVal = head->value;
        int maxId = head->id;
        for (auto c = head->next; c; c = c->next)
            if (c->value > maxVal) { maxVal = c->value; maxId = c->id; }
        return maxVal + " (ID: " + std::to_string(maxId) + ")";
    }
    
    bool isSingleChain() const {
        if (!head) return true;
        auto slow = head, fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return false;
        }
        return true;
    }
    
    void reverse() {
        ListNode* prev = nullptr;
        for (auto c = head; c; ) {
            auto next = c->next;
            c->next = prev;
            prev = c;
            c = next;
        }
        head = prev;
    }
    

    
    std::string toMermaid() const {
        std::string r = "graph LR\n    head[head]";
        if (!head) return r + " --> null[null]";
        for (auto c = head; c; c = c->next)
            r += " --> n" + std::to_string(c->id) + "[\"" + std::to_string(c->id) + ":" + c->value + "\"]";
        return r + " --> null[null]";
    }
};
