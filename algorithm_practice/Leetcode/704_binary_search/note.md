\# LeetCode 704 二分查找 

🔗题目链接：https://leetcode.cn/problems/binary-search/ 

## 核心信息 - 解法：左闭右闭区间 `[left, right]` 

- 时间复杂度：$O(\log n)$ 

- 空间复杂度：$O(1)$

   ## 关键点 

  1. 循环条件：`left <= right`

  2. mid防溢出写法：`mid = left + (right‑left)/2` 

  3. 边界更新：`left = mid+1`，`right = mid‑1` 

     区间、循环条件、边界更新三者必须成套，禁止混搭

      ## 踩坑 

     - ❌错误：`while(left < right)`，单元素测试用例直接翻车 

     - ❌错误：`mid=(left+right)/2`，大数会整型溢出

        ## 测试边界用例 

       1. 单元素匹配 `[5], target=5` 
       2. 单元素不匹配 `[5], target=2`
       3. target在数组头部、尾部、超出数组范围

\# LeetCode 704 Binary Search 🔗 Problem Link: https://leetcode.com/problems/binary-search/ ## Basic Info - Approach: closed interval `[left, right]` - Time Complexity: $O(\log n)$ - Space Complexity: $O(1)$ ## Key Points 1. Loop condition: `left <= right` 2. Safe mid calculation: `mid = left + (right - left) / 2` to prevent integer overflow 3. Boundary update: `left = mid + 1`, `right = mid - 1` > Interval definition, loop condition and boundary updates must match. Do NOT mix different interval styles. ## Common Pitfalls - ❌ Bug: `while(left < right)`. Fails test case with single element array. - ❌ Bug: `mid = (left + right) / 2`. Risk of integer overflow for large values. ## Critical Test Cases 1. Single element match: `[5], target = 5` 2. Single element no‑match: `[5], target = 2` 3. Target at array head / tail 4. Target out of array range