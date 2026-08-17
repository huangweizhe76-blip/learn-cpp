#include <iostream>
using namespace std;

using ElemType = int;

// 双向链表节点，哨兵头结点
struct Node {
    ElemType data;
    Node* next;
    Node* prev;
    Node() : data(0), next(nullptr), prev(nullptr) {}
    explicit Node(ElemType val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head; // 哨兵头结点，不存有效数据
public:
    // 构造：初始化哨兵头
    DoublyLinkedList() {
        head = new Node();
    }

    // 头插
    bool insertHead(ElemType e) {
        Node* p = new Node(e);
        p->prev = head;
        p->next = head->next;
        if (head->next != nullptr) {
            head->next->prev = p;
        }
        head->next = p;
        return true;
    }

    // 获取尾结点
    Node* getTail() {
        Node* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        return p;
    }

    // 尾插
    bool insertTail(ElemType e) {
        Node* tail = getTail();
        Node* p = new Node(e);
        p->prev = tail;
        tail->next = p;
        p->next = nullptr;
        return true;
    }

    // pos从1开始，pos位置插入元素
    bool insertNode(int pos, ElemType e) {
        if (pos < 1) return false;
        Node* p = head;
        int i = 0;
        while (i < pos - 1) {
            p = p->next;
            i++;
            if (p == nullptr) return false;
        }
        Node* q = new Node(e);
        q->prev = p;
        q->next = p->next;
        if (p->next != nullptr) {
            p->next->prev = q;
        }
        p->next = q;
        return true;
    }

    // 删除pos位置结点，pos从1开始
    bool deleteNode(int pos) {
        if (pos < 1) return false;
        Node* p = head;
        int i = 0;
        while (i < pos - 1) {
            p = p->next;
            i++;
            if (p == nullptr) return false;
        }
        if (p->next == nullptr) {
            cout << "要删除的位置错误" << endl;
            return false;
        }
        Node* q = p->next;
        p->next = q->next;
        if (q->next != nullptr) {
            q->next->prev = p;
        }
        delete q;
        return true;
    }

    // 正向遍历打印
    void listPrint() {
        Node* p = head->next;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    // 释放全部节点
    ~DoublyLinkedList() {
        Node* p = head->next;
        while (p != nullptr) {
            Node* q = p->next;
            delete p;
            p = q;
        }
        delete head;
    }

    // 禁止拷贝(可选，防止浅拷贝内存问题)
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
};


int main() {
    DoublyLinkedList list;

    list.insertTail(10);
    list.insertTail(20);
    list.insertTail(30);
    cout << "尾插10 20 30：";
    list.listPrint();

    list.insertNode(2, 15);
    cout << "pos2插入15：";
    list.listPrint();

    list.deleteNode(2);
    cout << "删除pos2：";
    list.listPrint();

    return 0;
}