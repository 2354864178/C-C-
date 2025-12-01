#include "../include/ListNode.hpp"
#include "../include/List.hpp"
#include <iostream>
#include <cstdlib>
#include <cassert>

using Rank=int; 
// 运行时是否启用详细输出（通过环境变量 TEST_VERBOSE=1 控制）
static bool isVerbose() {
    static int v = getenv("TEST_VERBOSE") ? 1 : 0;
    return v;
}
namespace {
// 打印列表内容（内部链接，避免命名冲突）
template <typename T>
void printList(const List<T>& list, const std::string& name) {
    std::cout << name << " 元素：";
    if (list.empty()) {
        std::cout << "空列表" << std::endl;
        return;
    }
    ListNodePosi(T) p = list.first();
    while (list.valid(p)) {
        std::cout << p->data << " ";
        p = p->succ;
    }
    std::cout << "(大小: " << list.size() << ")" << std::endl;
}

// 测试构造函数和基本功能
void testConstructorAndBasic() {
    if (isVerbose()) std::cout << "\n=== 测试：构造与基本功能 ===" << std::endl;
    
    // 测试默认构造函数
    List<int> list1;
    assert(list1.empty() && list1.size() == 0);
    if (isVerbose()) printList(list1, "list1 (默认构造)");
    
    // 测试插入功能
    list1.insertAsFirst(1);
    list1.insertAsLast(3);
    list1.insertAfter(list1.first(), 2);
    if (isVerbose()) printList(list1, "list1 插入后");
    assert(list1.size() == 3 && list1[0] == 1 && list1[1] == 2 && list1[2] == 3);
    
    // 测试拷贝构造函数
    List<int> list2(list1);
    if (isVerbose()) printList(list2, "list2 (list1 的拷贝)");
    assert(list2.size() == 3 && list2[0] == 1 && list2[2] == 3);
    
    // 测试区间构造函数
    List<int> list3(list1.first()->succ, 2); // 从2开始，取2个元素
    if (isVerbose()) printList(list3, "list3 (区间构造)");
    assert(list3.size() == 2 && list3[0] == 2 && list3[1] == 3);
    
    // 测试带范围的构造函数
    List<int> list4(list1, 1, 2); // 从索引1开始，取2个元素
    if (isVerbose()) printList(list4, "list4 (按索引区间构造)");
    assert(list4.size() == 2 && list4[0] == 2 && list4[1] == 3);
}

// 测试删除和清空功能
void testRemoveAndClear() {
    if (isVerbose()) std::cout << "\n=== 测试：删除与清空 ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; ++i) list.insertAsLast(i);
    if (isVerbose()) printList(list, "原始列表");
    
    // 测试remove方法
    int removed = list.remove(list.first()->succ); // 删除2
    if (isVerbose()) printList(list, "删除后的列表");
    assert(removed == 2 && list.size() == 4 && list[1] == 3);
    
    // 测试clear方法
    int oldSize = list.clear();
    if (isVerbose()) printList(list, "清空后的列表");
    assert(oldSize == 4 && list.empty());
}

// 测试查找功能
void testFind() {
    if (isVerbose()) std::cout << "\n=== 测试：查找功能 ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; ++i) list.insertAsLast(i);
    if (isVerbose()) printList(list, "查找测试列表");
    
    // 测试find
    ListNodePosi(int) p1 = list.find(3);
    assert(p1 != nullptr && p1->data == 3);
    
    ListNodePosi(int) p2 = list.find(6);
    assert(p2 == nullptr);
    
    // 测试区间find
    // 在从最后元素向前数的4个节点范围里查找 2（包含 4,3,2,1）
    ListNodePosi(int) p3 = list.find(2, 4, list.last());
    assert(p3 != nullptr && p3->data == 2);
}

// 测试去重功能
void testUnique() {
    if (isVerbose()) std::cout << "\n=== 测试：去重功能 ===" << std::endl;
    
    // 测试deduplicate（无序列表去重）
    List<int> list1;
    list1.insertAsLast(3);
    list1.insertAsLast(1);
    list1.insertAsLast(3);
    list1.insertAsLast(2);
    list1.insertAsLast(1);
    if (isVerbose()) printList(list1, "去重前（无序）");
    int removed1 = list1.deduplicate();
    if (isVerbose()) printList(list1, "去重后（无序）");
    assert(removed1 == 2 && list1.size() == 3);
    
    // 测试uniquify（有序列表去重）
    List<int> list2;
    list2.insertAsLast(1);
    list2.insertAsLast(1);
    list2.insertAsLast(2);
    list2.insertAsLast(2);
    list2.insertAsLast(3);
    if (isVerbose()) printList(list2, "去重前（有序）");
    int removed2 = list2.uniquify();
    if (isVerbose()) printList(list2, "去重后（有序）");
    assert(removed2 == 2 && list2.size() == 3);
}

// 测试排序功能
void testSort() {
    if (isVerbose()) std::cout << "\n=== 测试：排序功能 ===" << std::endl;
    
    // 测试插入排序
    List<int> list1;
    list1.insertAsLast(3);
    list1.insertAsLast(1);
    list1.insertAsLast(4);
    list1.insertAsLast(2);
    if (isVerbose()) printList(list1, "插入排序前(list1)");
    list1.insertionsort();
    if (isVerbose()) printList(list1, "插入排序后(list1)");
    assert(list1.disordered() == true);
    
    // 测试选择排序
    List<int> list2;
    list2.insertAsLast(5);
    list2.insertAsLast(3);
    list2.insertAsLast(8);
    list2.insertAsLast(6);
    list2.insertAsLast(2);
    if (isVerbose()) printList(list2, "选择排序前(list2)");
    list2.selectionsort();
    if (isVerbose()) printList(list2, "选择排序后(list2)");
    assert(list2.disordered() == true);
}

// 测试反转功能
void testReverse() {
    if (isVerbose()) std::cout << "\n=== 测试：反转 ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; ++i) list.insertAsLast(i);
    if (isVerbose()) {
        printList(list, "反转前");
        std::cout << "  first()=" << list.first() << " last()=" << list.last() << std::endl;
    }
    list.reverse();
    if (isVerbose()) {
        printList(list, "反转后");
        std::cout << "  first()=" << list.first() << " last()=" << list.last() << std::endl;
    }
    assert(list[0] == 5 && list[1] == 4 && list[2] == 3 && list[3] == 2 && list[4] == 1);
}

// 测试异常处理
void testException() {
    if (isVerbose()) std::cout << "\n=== 测试：异常处理 ===" << std::endl;
    
    List<int> list;
    list.insertAsLast(1);
    
    try {
        list[1]; // 越界访问（不保存返回值，以免编译器警告未使用变量）
        if (isVerbose()) std::cout << "失败：未抛出越界异常(index 1)" << std::endl;
    } catch (const std::out_of_range& e) {
        if (isVerbose()) std::cout << "通过：已捕获 out_of_range 异常" << std::endl;
    }
}

// 测试search功能（有序列表）
void testSearch() {
    if (isVerbose()) std::cout << "\n=== 测试：search 功能 ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; i += 2) list.insertAsLast(i); // 1,3,5
    if (isVerbose()) printList(list, "供 search 使用的有序列表");
    
    ListNodePosi(int) p1 = list.search(3);
    if (isVerbose()) std::cout << "p1=" << p1 << (p1 ? (std::string(" data=") + std::to_string(p1->data)) : std::string(" (null)")) << std::endl;
    assert(p1 != nullptr && p1->data == 3);
    
    ListNodePosi(int) p2 = list.search(4); // 找不大于4的最大元素
    if (isVerbose()) std::cout << "p2=" << p2 << (p2 ? (std::string(" data=") + std::to_string(p2->data)) : std::string(" (null)")) << std::endl;
    assert(p2 != nullptr && p2->data == 3);
    
    ListNodePosi(int) p3 = list.search(0); // 小于所有元素
    if (isVerbose()) std::cout << "p3=" << p3 << (p3 ? (std::string(" data=") + std::to_string(p3->data)) : std::string(" (null)")) << std::endl;
    assert(p3 == nullptr);
}

// 测试最大元素查找
void testSelectMax() {
    if (isVerbose()) std::cout << "\n=== 测试：查找最大元素 ===" << std::endl;
    
    List<int> list;
    list.insertAsLast(3);
    list.insertAsLast(5);
    list.insertAsLast(2);
    list.insertAsLast(7);
    list.insertAsLast(1);
    if (isVerbose()) printList(list, "供 selectMax 使用的列表");
    
    ListNodePosi(int) maxNode = list.selectMax();
    assert(maxNode != nullptr && maxNode->data == 7);
    
    ListNodePosi(int) maxNode2 = list.selectMax(list.first(), 3); // 前3个元素中的最大值
    assert(maxNode2 != nullptr && maxNode2->data == 5);
}
}
// end anonymous namespace

void run_list_test() {
    std::cout << "\n===== 开始 列表 测试 =====" << std::endl;
    
    testConstructorAndBasic();
    testRemoveAndClear();
    testFind();
    testSearch();
    testSelectMax();
    testUnique();
    testSort();
    testReverse();
    testException();
    
    std::cout << "===== 列表 测试通过 =====" << std::endl;
}