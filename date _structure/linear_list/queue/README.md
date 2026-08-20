# Queue 队列
C语言实现三种队列：
1. seq_queue.c：普通顺序队列（数组迁移）
2. circ_queue.c：循环顺序队列
3. link_queue.c：带头结点链式队列

📝学习笔记：[note.md](./note.md)

### 特性
- 完整内存释放，避免内存泄漏
- 接口统一，const只读保护
- 健壮状态返回，区分空队列和元素0
- VS/GCC均可编译运行