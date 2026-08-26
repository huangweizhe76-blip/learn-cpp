#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    struct ListNode* cur = dummy;

    while (cur->next != NULL && cur->next->next != NULL) {
        struct ListNode* node1 = cur->next;
        struct ListNode* node2 = cur->next->next;

        cur->next = node2;
        node1->next = node2->next;
        node2->next = node1;

        cur = node1;
    }
    struct ListNode* newHead = dummy->next;
    free(dummy);
    return newHead;
}

// 创建节点
struct ListNode* createNode(int v) {
    struct ListNode* n = (struct ListNode*)malloc(sizeof(struct ListNode));
    n->val = v;
    n->next = NULL;
    return n;
}
// 打印链表
void printList(struct ListNode* h) {
    struct ListNode* p = h;
    while (p) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

int main() {
    // 构建 1->2->3->4
    struct ListNode* h = createNode(1);
    h->next = createNode(2);
    h->next->next = createNode(3);
    h->next->next->next = createNode(4);

    h = swapPairs(h);
    printList(h); //输出：2 1 4 3
    return 0;
}