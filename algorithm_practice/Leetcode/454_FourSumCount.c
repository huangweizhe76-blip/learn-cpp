#include <stdio.h>
#include <stdlib.h>

// 简单哈希结构体
typedef struct HashNode {
    int key;
    int count;
    struct HashNode* next;
} HashNode;

#define HASH_SIZE 100000

// 插入哈希
void hashInsert(HashNode** table, int key) {
    int hashIdx = (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    HashNode* p = table[hashIdx];
    while (p) {
        if (p->key == key) {
            p->count++;
            return;
        }
        p = p->next;
    }
    // 没找到，新建节点
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->count = 1;
    newNode->next = table[hashIdx];
    table[hashIdx] = newNode;
}

// 查询哈希
int hashGet(HashNode** table, int key) {
    int hashIdx = (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    HashNode* p = table[hashIdx];
    while (p) {
        if (p->key == key) {
            return p->count;
        }
        p = p->next;
    }
    return 0;
}

// 释放哈希
void hashFree(HashNode** table) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* p = table[i];
        while (p) {
            HashNode* temp = p;
            p = p->next;
            free(temp);
        }
    }
}

int fourSumCount(int* nums1, int nums1Size, int* nums2, int nums2Size, int* nums3, int nums3Size, int* nums4, int nums4Size) {
    HashNode* hashTable[HASH_SIZE] = { NULL };

    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums2Size; j++) {
            int sum = nums1[i] + nums2[j];
            hashInsert(hashTable, sum);
        }
    }

    int res = 0;
    for (int k = 0; k < nums3Size; k++) {
        for (int l = 0; l < nums4Size; l++) {
            int target = -(nums3[k] + nums4[l]);
            res += hashGet(hashTable, target);
        }
    }

    hashFree(hashTable);
    return res;
}

int main()
{
    int nums1[] = { 1,2 };
    int nums2[] = { -2,-1 };
    int nums3[] = { -1,2 };
    int nums4[] = { 0,2 };
    int n = sizeof(nums1) / sizeof(int);
    int ans = fourSumCount(nums1, n, nums2, n, nums3, n, nums4, n);
    printf("ans=%d\n", ans);
    return 0;
}
