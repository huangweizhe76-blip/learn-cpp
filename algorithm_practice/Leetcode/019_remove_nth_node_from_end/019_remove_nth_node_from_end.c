#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    struct ListNode* fast = dummy;
    struct ListNode* slow = dummy;

    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    struct ListNode* del = slow->next;
    slow->next = slow->next->next;
    free(del);

    struct ListNode* ans = dummy->next;
    free(dummy);
    return ans;
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
    //测试用例1 [1,2,3,4,5],n=2 →输出1 2 3 5
    struct ListNode* h = createNode(1);
    h->next = createNode(2);
    h->next->next = createNode(3);
    h->next->next->next = createNode(4);
    h->next->next->next->next = createNode(5);

    h = removeNthFromEnd(h, 2);
    printList(h);

    return 0;
}
