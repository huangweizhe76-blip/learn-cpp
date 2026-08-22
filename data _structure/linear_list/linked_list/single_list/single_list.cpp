#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cmath>
using namespace std;

typedef int ElemType;

struct Node
{
    ElemType data;
    Node* next;
    Node(ElemType e = 0) : data(e), next(nullptr) {}
};

class SingleList
{
private:
    Node* m_head; //头结点
public:
    //构造：创建头结点
    SingleList()
    {
        m_head = new Node(0);
    }

    //析构：释放全部节点
    ~SingleList()
    {
        Node* p = m_head->next;
        while (p != nullptr)
        {
            Node* q = p->next;
            delete p;
            p = q;
        }
        delete m_head;
        m_head = nullptr;
    }

    //获取头结点指针（供外部算法使用，如相交、环操作）
    Node* getHead()
    {
        return m_head;
    }

    //头插
    int insertHead(ElemType e)
    {
        Node* p = new Node(e);
        p->next = m_head->next;
        m_head->next = p;
        return 1;
    }

    //遍历打印
    void listNode()
    {
        Node* p = m_head->next;
        while (p != nullptr)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

    //获取尾结点
    Node* get_tail()
    {
        Node* p = m_head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        return p;
    }

    //尾插，返回新尾结点
    Node* insertTail(Node* tail, ElemType e)
    {
        if (tail == nullptr) return nullptr;
        Node* p = new Node(e);
        tail->next = p;
        p->next = nullptr;
        return p;
    }

    //把已有节点接尾部
    Node* insertTailWithNode(Node* tail, Node* node)
    {
        if (tail == nullptr || node == nullptr) return nullptr;
        tail->next = node;
        node->next = nullptr;
        return node;
    }

    //pos从1开始指定位置插入
    int insertNode(int pos, ElemType e)
    {
        if (pos < 1) return 0;
        Node* p = m_head;
        int i = 0;
        while (i < pos - 1)
        {
            p = p->next;
            i++;
            if (p == nullptr)
                return 0;
        }
        Node* q = new Node(e);
        q->next = p->next;
        p->next = q;
        return 1;
    }

    //删除pos位置结点，pos从1开始
    int deleteNode(int pos)
    {
        if (pos < 1) return 0;
        Node* p = m_head;
        int i = 0;
        while (i < pos - 1)
        {
            p = p->next;
            i++;
            if (p == nullptr)
                return 0;
        }
        if (p->next == nullptr)
        {
            cout << "要删除的位置错误" << endl;
            return 0;
        }
        Node* q = p->next;
        p->next = q->next;
        delete q;
        return 1;
    }

    //获取有效数据结点长度，不包含头结点
    int listLength()
    {
        Node* p = m_head->next;
        int len = 0;
        while (p != nullptr)
        {
            p = p->next;
            len++;
        }
        return len;
    }

    //查找倒数第k个结点
    int findNodeFS(int k)
    {
        if (k < 1) return 0;
        int len = listLength();
        if (k > len)
        {
            cout << "k超过链表长度！" << endl;
            return 0;
        }
        Node* fast = m_head->next;
        Node* slow = m_head->next;
        for (int i = 0; i < k; ++i)
        {
            fast = fast->next;
        }
        while (fast != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }
        cout << "倒数第" << k << "个节点值为：" << slow->data << endl;
        return 1;
    }

    //删除绝对值重复结点，n为最大绝对值上限
    void removeNode(int n)
    {
        if (n <= 0) return;
        Node* p = m_head;
        int* arr = new int[n + 1] {0};
        while (p->next != nullptr)
        {
            int index = abs(p->next->data);
            if (index > n)
            {
                p = p->next;
                continue;
            }
            if (arr[index] == 0)
            {
                arr[index] = 1;
                p = p->next;
            }
            else
            {
                Node* temp = p->next;
                p->next = temp->next;
                delete temp;
            }
        }
        delete[] arr;
    }

    //反转链表，复用原头结点
    void reverseList()
    {
        if (m_head->next == nullptr)
            return;
        Node* first = nullptr;
        Node* second = m_head->next;
        Node* third;
        while (second != nullptr)
        {
            third = second->next;
            second->next = first;
            first = second;
            second = third;
        }
        m_head->next = first;
    }

    //删除中间结点
    int delMiddleNode()
    {
        if (m_head->next == nullptr)
            return 0;
        Node* fast = m_head->next;
        Node* slow = m_head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        Node* q = slow->next;
        slow->next = q->next;
        delete q;
        return 1;
    }

    //重排链表：后半反转交替合并
    void reOrderList()
    {
        if (m_head->next == nullptr || m_head->next->next == nullptr)
            return;
        Node* fast = m_head;
        Node* slow = m_head;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        Node* first = nullptr;
        Node* second = slow->next;
        slow->next = nullptr;
        Node* third;
        //反转后半段
        while (second != nullptr)
        {
            third = second->next;
            second->next = first;
            first = second;
            second = third;
        }
        //交替合并
        Node* p1 = m_head->next;
        Node* q1 = first;
        Node* p2, * q2;
        while (p1 != nullptr && q1 != nullptr)
        {
            p2 = p1->next;
            q2 = q1->next;
            p1->next = q1;
            q1->next = p2;
            p1 = p2;
            q1 = q2;
        }
    }

    //判断是否有环
    int isCycle()
    {
        Node* fast = m_head;
        Node* slow = m_head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
                return 1;
        }
        return 0;
    }

    //找环入口结点，返回结点指针，无环返回nullptr
    Node* findBegin()
    {
        Node* fast = m_head;
        Node* slow = m_head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
            {
                Node* p = fast;
                int count = 1;
                while (p->next != slow)
                {
                    count++;
                    p = p->next;
                }
                fast = m_head;
                slow = m_head;
                for (int i = 0; i < count; ++i)
                {
                    fast = fast->next;
                }
                while (fast != slow)
                {
                    fast = fast->next;
                    slow = slow->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};

//全局函数：求两个链表相交结点
Node* findIntersectionNode(SingleList& la, SingleList& lb)
{
    Node* headA = la.getHead();
    Node* headB = lb.getHead();
    int lenA = la.listLength();
    int lenB = lb.listLength();

    Node* m = headA->next;
    Node* n = headB->next;
    int step;
    if (lenA > lenB)
    {
        step = lenA - lenB;
        for (int i = 0; i < step; i++)
            m = m->next;
    }
    else
    {
        step = lenB - lenA;
        for (int i = 0; i < step; i++)
            n = n->next;
    }
    while (m != nullptr && n != nullptr && m != n)
    {
        m = m->next;
        n = n->next;
    }
    return m;
}

int main()
{
    SingleList list;
    Node* tail = list.get_tail();

    tail = list.insertTail(tail, 1);
    tail = list.insertTail(tail, 2);
    tail = list.insertTail(tail, 3);
    Node* three = tail;
    tail = list.insertTail(tail, 4);
    tail = list.insertTail(tail, 5);
    tail = list.insertTail(tail, 6);
    tail = list.insertTail(tail, 7);
    tail = list.insertTail(tail, 8);

    //构造环：8 -> 3
    tail->next = three;

    Node* p = list.findBegin();
    if (p != nullptr)
    {
        cout << "环入口节点data = " << p->data << endl;
    }
    else
    {
        cout << "链表无环" << endl;
    }

    //重要：有环链表析构前，必须断开环，否则析构死循环！
    tail->next = nullptr;

    return 0;
}