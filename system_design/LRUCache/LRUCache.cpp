#include <iostream>
#include <unordered_map>

using namespace std;

class LRUCache {
    private:
    // 双向链表节点
    struct DLinkedNode {
        int key, value;
        DLinkedNode* prev;
        DLinkedNode* next;
        DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
        DLinkedNode(int k, int v): key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    unordered_map<int, DLinkedNode*> cache; // 哈希表
    DLinkedNode* head; // 双向链表头节点
    DLinkedNode* tail; // 双向链表尾节点
    int size; // 缓存大小
    int capacity; // 缓存容量

    public:
    LRUCache(int capacity): capacity(capacity) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        while (head != nullptr) {
            DLinkedNode* node = head;
            head = head->next;
            delete node;
        }
    }

    int get(int key) {
        if (capacity == 0) {
            return -1;
        }
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value){
        if (capacity == 0) {
            return;
        }
        if (cache.find(key) == cache.end()) {
            DLinkedNode* node = new DLinkedNode(key, value);
            addToHead(node);
            cache[key] = node;
            size++;
        }
        else {
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
        if (size > capacity) {
            DLinkedNode* node = removeTail();
            cache.erase(node->key);
            delete node;
            size--;
        }
    }

    // 将节点添加到头部
    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    // 删除节点
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 将节点移动到头部
    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    // 删除尾部节点
    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }

};

int main() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);       // 返回 1
    cout << cache.get(1) << endl;
    cache.put(3, 3);    // 淘汰 key 2
    cache.get(2);       // 返回 -1 (未找到)
    cout << cache.get(2) << endl;
    cache.put(4, 4);    // 淘汰 key 1
    cache.get(1);       // 返回 -1
    cout << cache.get(1) << endl;
    cache.get(3);       // 返回 3
    cout << cache.get(3) << endl;
    cache.get(4);       // 返回 4
    cout << cache.get(4) << endl;
    return 0;
}