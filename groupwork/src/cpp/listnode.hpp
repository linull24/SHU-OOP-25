#pragma once
#include <string>
#include <vector>

class ListNode {
private:
    int id;
    std::string value;
    ListNode* next;
    
    ListNode(int id, const std::string& val) : id(id), value(val), next(nullptr) {}
    ~ListNode() = default;
    
    friend class LinkedList;
};

class LinkedList {
private:
    ListNode* head;
    int size, nextId;
    std::vector<ListNode*> nodes;  // 维护所有节点的所有权

public:
    LinkedList() : head(nullptr), size(0), nextId(1) {}
    ~LinkedList() { for (auto n : nodes) delete n; }
    
    bool isIdExists(int id) const {
        for (auto c = head; c; c = c->next)
            if (c->id == id) return true;
        return false;
    }
    
    void insertHead(const std::string& value, int customId = -1) {
        int id = (customId > 0 && !isIdExists(customId)) ? customId : nextId;
        auto n = new ListNode(id, value);
        nodes.push_back(n);
        n->next = head;
        head = n;
        size++;
        if (id >= nextId) nextId = id + 1;
    }
    
    void insertTail(const std::string& value, int customId = -1) {
        int id = (customId > 0 && !isIdExists(customId)) ? customId : nextId;
        auto n = new ListNode(id, value);
        nodes.push_back(n);
        if (!head) head = n;
        else {
            auto c = head;
            while (c->next) c = c->next;
            c->next = n;
        }
        size++;
        if (id >= nextId) nextId = id + 1;
    }
    
    void insertAfterId(int targetId, const std::string& value, int customId = -1) {
        auto c = head;
        while (c && c->id != targetId) c = c->next;
        if (!c) return;
        int id = (customId > 0 && !isIdExists(customId)) ? customId : nextId;
        auto n = new ListNode(id, value);
        nodes.push_back(n);
        n->next = c->next;
        c->next = n;
        size++;
        if (id >= nextId) nextId = id + 1;
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
        for (auto n : nodes) delete n;
        nodes.clear();
        head = nullptr;
        size = 0;
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
    

    
    void sortById() {
        if (!head || !head->next) return;
        for (auto i = head; i; i = i->next)
            for (auto j = i->next; j; j = j->next)
                if (i->id > j->id) {
                    std::swap(i->id, j->id);
                    std::swap(i->value, j->value);
                }
    }
    
    void sortByValue() {
        if (!head || !head->next) return;
        for (auto i = head; i; i = i->next)
            for (auto j = i->next; j; j = j->next)
                if (i->value > j->value) {
                    std::swap(i->id, j->id);
                    std::swap(i->value, j->value);
                }
    }
    
    std::string toMermaid() const {
        std::string r = "graph LR\n    head[head]";
        if (!head) return r + " --> null[null]";
        for (auto c = head; c; c = c->next)
            r += " --> n" + std::to_string(c->id) + "[\"" + std::to_string(c->id) + ":" + c->value + "\"]";
        return r + " --> null[null]";
    }
};
