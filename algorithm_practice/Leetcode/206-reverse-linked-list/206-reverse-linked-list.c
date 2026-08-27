#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* pre = NULL;
    struct ListNode* cur = head;
    struct ListNode* temp;

    while (cur != NULL) {
        temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    return pre;
}

//工具函数
struct ListNode* createNode(int v) {
    struct ListNode* n = (struct ListNode*)malloc(sizeof(struct ListNode));
    n->val = v;
    n->next = NULL;
    return n;
}

void printList(struct ListNode* h) {
    struct ListNode* p = h;
    while (p) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}

int main() {
    //构建链表 1->2->3->4->5
    struct ListNode* h = createNode(1);
    h->next = createNode(2);
    h->next->next = createNode(3);
    h->next->next->next = createNode(4);
    h->next->next->next->next = createNode(5);

    h = reverseList(h);
    printList(h); //输出 5 4 3 2 1
    return 0;
}
