#include <iostream>
using namespace std;

const int MAXSIZE = 100;
using ElemType = int;

class SeqList
{
private:
    ElemType* data;     // 动态数组
    int length;         // 当前有效元素个数
public:
    // 构造函数：初始化顺序表，替代C语言initList()
    SeqList();

    // 析构函数：自动释放内存，替代destroyList()，对象销毁自动调用
    ~SeqList();

    // 清空顺序表，逻辑清空，不释放内存
    void clearList();

    // 尾部追加元素，成功返回true，失败false
    bool appendElem(ElemType e);

    // 遍历打印
    void listElem() const;

    // pos为逻辑位置，从1开始插入
    bool insertElem(int pos, ElemType e);

    // 删除pos位置元素，e保存被删除的值
    bool deleteElem(int pos, ElemType& e);

    // 查找第一个匹配元素，返回逻辑位置；找不到返回0
    int findFirstElem(ElemType e) const;

    // 打印全部等于e的元素位置
    void findAllElem(ElemType e) const;

    // 根据逻辑位置获取元素
    bool getElem(int pos, ElemType& e) const;

    // 获取当前长度
    int getLength() const { return length; }
};

// 构造函数实现
SeqList::SeqList()
{
    data = new ElemType[MAXSIZE];
    length = 0;
}

// 析构函数实现
SeqList::~SeqList()
{
    delete[] data;
}

void SeqList::clearList()
{
    length = 0;
}

bool SeqList::appendElem(ElemType e)
{
    if (length >= MAXSIZE)
    {
        cout << "顺序表已满，无法追加元素!" << endl;
        return false;
    }
    data[length] = e;
    length++;
    return true;
}

void SeqList::listElem() const
{
    if (length == 0)
    {
        cout << "[空顺序表]";
    }
    for (int i = 0; i < length; ++i)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

bool SeqList::insertElem(int pos, ElemType e)
{
    if (length >= MAXSIZE)
    {
        cout << "顺序表已满，无法插入!" << endl;
        return false;
    }
    // pos合法范围：1 ~ length+1，支持表尾插入
    if (pos < 1 || pos > length + 1)
    {
        cout << "插入位置" << pos << "非法，合法范围1~" << length + 1 << endl;
        return false;
    }
    // 元素后移
    for (int i = length - 1; i >= pos - 1; --i)
    {
        data[i + 1] = data[i];
    }
    data[pos - 1] = e;
    length++;
    return true;
}

bool SeqList::deleteElem(int pos, ElemType& e)
{
    if (length == 0)
    {
        cout << "空表，不能删除!" << endl;
        return false;
    }
    if (pos < 1 || pos > length)
    {
        cout << "删除位置" << pos << "非法，合法范围1~" << length << endl;
        return false;
    }
    e = data[pos - 1];
    // 元素向前移动
    for (int i = pos; i < length; ++i)
    {
        data[i - 1] = data[i];
    }
    length--;
    return true;
}

int SeqList::findFirstElem(ElemType e) const
{
    for (int i = 0; i < length; ++i)
    {
        if (data[i] == e)
        {
            return i + 1;
        }
    }
    return 0;
}

void SeqList::findAllElem(ElemType e) const
{
    bool flag = false;
    cout << "值" << e << "所有位置：";
    for (int i = 0; i < length; ++i)
    {
        if (data[i] == e)
        {
            cout << i + 1 << " ";
            flag = true;
        }
    }
    if (!flag)
        cout << "不存在";
    cout << endl;
}

bool SeqList::getElem(int pos, ElemType& e) const
{
    if (pos < 1 || pos > length)
        return false;
    e = data[pos - 1];
    return true;
}

// main测试，和C版本测试逻辑完全一样
int main()
{
    SeqList list;

    cout << "初始化成功，当前有效长度：" << list.getLength() << endl;
    cout << "数据数组总内存大小：" << MAXSIZE * sizeof(ElemType) << " 字节" << endl;

    // 尾部添加
    list.appendElem(88);
    list.appendElem(67);
    list.appendElem(40);
    list.appendElem(8);
    list.appendElem(23);
    cout << "\n尾部追加5个元素后：";
    list.listElem();

    // 位置1插入
    list.insertElem(1, 18);
    cout << "在位置1插入18后：";
    list.listElem();

    // 删除位置2
    ElemType delData;
    list.deleteElem(2, delData);
    cout << "删除位置2的数据：" << delData << endl;
    cout << "删除之后顺序表：";
    list.listElem();

    // 查找
    int pos = list.findFirstElem(40);
    cout << "元素40第一次出现的逻辑位置：" << pos << endl;

    list.findAllElem(18);

    // 表尾插入
    list.insertElem(list.getLength() + 1, 999);
    cout << "在表尾插入999：";
    list.listElem();

    // 对象离开作用域，析构函数自动调用释放内存，不需要手动free

    return 0;
}