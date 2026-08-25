#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* dummyHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyHead->next = head;
    struct ListNode* cur = dummyHead;

    while (cur->next != NULL) {
        if (cur->next->val == val) {
            struct ListNode* temp = cur->next;
            cur->next = cur->next->next;
            free(temp);
        }
        else {
            cur = cur->next;
        }
    }
    struct ListNode* newHead = dummyHead->next;
    free(dummyHead);
    return newHead;
}

//辅助：创建节点
struct ListNode* createNode(int v) {
    struct ListNode* n = (struct ListNode*)malloc(sizeof(struct ListNode));
    n->val = v;
    n->next = NULL;
    return n;
}
//辅助打印链表
void printList(struct ListNode* h) {
    struct ListNode* p = h;
    while (p) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

int main() {
    //构建 1->2->6->3->4->5->6
    struct ListNode* h = createNode(1);
    h->next = createNode(2);
    h->next->next = createNode(6);
    h->next->next->next = createNode(3);
    h->next->next->next->next = createNode(4);
    h->next->next->next->next->next = createNode(5);
    h->next->next->next->next->next->next = createNode(6);

    h = removeElements(h, 6);
    printList(h); //输出 1 2 3 4 5
    return 0;
}
