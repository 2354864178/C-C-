#include "../include/ListNode.hpp"
#include "../include/List.hpp"
#include <iostream>
#include <cassert>
using Rank=int; 
// 打印列表内容
template <typename T>
void printList(const List<T>& list, const std::string& name) {
    std::cout << name << " elements: ";
    if (list.empty()) {
        std::cout << "Empty list" << std::endl;
        return;
    }
    ListNodePosi(T) p = list.first();
    while (list.valid(p)) {
        std::cout << p->data << " ";
        p = p->succ;
    }
    std::cout << "(size: " << list.size() << ")" << std::endl;
}

// 测试构造函数和基本功能
void testConstructorAndBasic() {
    std::cout << "\n=== Testing Constructor and Basic Functions ===" << std::endl;
    
    // 测试默认构造函数
    List<int> list1;
    assert(list1.empty() && list1.size() == 0);
    printList(list1, "list1 (default constructor)");
    
    // 测试插入功能
    list1.insertAsFirst(1);
    list1.insertAsLast(3);
    list1.insertAfter(list1.first(), 2);
    printList(list1, "list1 after insertions");
    assert(list1.size() == 3 && list1[0] == 1 && list1[1] == 2 && list1[2] == 3);
    
    // 测试拷贝构造函数
    List<int> list2(list1);
    printList(list2, "list2 (copy of list1)");
    assert(list2.size() == 3 && list2[0] == 1 && list2[2] == 3);
    
    // 测试区间构造函数
    List<int> list3(list1.first()->succ, 2); // 从2开始，取2个元素
    printList(list3, "list3 (range constructor)");
    assert(list3.size() == 2 && list3[0] == 2 && list3[1] == 3);
    
    // 测试带范围的构造函数
    List<int> list4(list1, 1, 2); // 从索引1开始，取2个元素
    printList(list4, "list4 (range constructor with index)");
    assert(list4.size() == 2 && list4[0] == 2 && list4[1] == 3);
}

// 测试删除和清空功能
void testRemoveAndClear() {
    std::cout << "\n=== Testing Remove and Clear ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; ++i) list.insertAsLast(i);
    printList(list, "Original list");
    
    // 测试remove方法
    int removed = list.remove(list.first()->succ); // 删除2
    printList(list, "After removing 2");
    assert(removed == 2 && list.size() == 4 && list[1] == 3);
    
    // 测试clear方法
    int oldSize = list.clear();
    printList(list, "After clear");
    assert(oldSize == 4 && list.empty());
}

// 测试查找功能
void testFind() {
    std::cout << "\n=== Testing Find Functions ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; ++i) list.insertAsLast(i);
    printList(list, "Test list");
    
    // 测试find
    ListNodePosi(int) p1 = list.find(3);
    assert(p1 != nullptr && p1->data == 3);
    
    ListNodePosi(int) p2 = list.find(6);
    assert(p2 == nullptr);
    
    // 测试区间find
    ListNodePosi(int) p3 = list.find(2, 2, list.last()); // 在最后2个元素前找2
    assert(p3 != nullptr && p3->data == 2);
}

// 测试去重功能
void testUnique() {
    std::cout << "\n=== Testing Unique Functions ===" << std::endl;
    
    // 测试deduplicate（无序列表去重）
    List<int> list1;
    list1.insertAsLast(3);
    list1.insertAsLast(1);
    list1.insertAsLast(3);
    list1.insertAsLast(2);
    list1.insertAsLast(1);
    printList(list1, "list1 before deduplicate");
    int removed1 = list1.deduplicate();
    printList(list1, "list1 after deduplicate");
    assert(removed1 == 2 && list1.size() == 3);
    
    // 测试uniquify（有序列表去重）
    List<int> list2;
    list2.insertAsLast(1);
    list2.insertAsLast(1);
    list2.insertAsLast(2);
    list2.insertAsLast(2);
    list2.insertAsLast(3);
    printList(list2, "list2 before uniquify");
    int removed2 = list2.uniquify();
    printList(list2, "list2 after uniquify");
    assert(removed2 == 2 && list2.size() == 3);
}

// 测试排序功能
void testSort() {
    std::cout << "\n=== Testing Sort Functions ===" << std::endl;
    
    // 测试插入排序
    List<int> list1;
    list1.insertAsLast(3);
    list1.insertAsLast(1);
    list1.insertAsLast(4);
    list1.insertAsLast(2);
    printList(list1, "list1 before insertion sort");
    list1.insertionsort();
    printList(list1, "list1 after insertion sort");
    assert(list1.disordered() == true);
    
    // 测试选择排序
    List<int> list2;
    list2.insertAsLast(5);
    list2.insertAsLast(3);
    list2.insertAsLast(8);
    list2.insertAsLast(6);
    list2.insertAsLast(2);
    printList(list2, "list2 before selection sort");
    list2.selectionsort();
    printList(list2, "list2 after selection sort");
    assert(list2.disordered() == true);
}

// 测试反转功能
void testReverse() {
    std::cout << "\n=== Testing Reverse ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; ++i) list.insertAsLast(i);
    printList(list, "Before reverse");
    list.reverse();
    printList(list, "After reverse");
    assert(list[0] == 5 && list[1] == 4 && list[2] == 3 && list[3] == 2 && list[4] == 1);
}

// 测试异常处理
void testException() {
    std::cout << "\n=== Testing Exception Handling ===" << std::endl;
    
    List<int> list;
    list.insertAsLast(1);
    
    try {
        int val = list[1]; // 越界访问
        std::cout << "Failed: No exception thrown for index 1" << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Passed: Caught out_of_range exception as expected" << std::endl;
    }
}

// 测试search功能（有序列表）
void testSearch() {
    std::cout << "\n=== Testing Search Functions ===" << std::endl;
    
    List<int> list;
    for (int i = 1; i <= 5; i += 2) list.insertAsLast(i); // 1,3,5
    printList(list, "Sorted list for search");
    
    ListNodePosi(int) p1 = list.search(3);
    assert(p1 != nullptr && p1->data == 3);
    
    ListNodePosi(int) p2 = list.search(4); // 找不大于4的最大元素
    assert(p2 != nullptr && p2->data == 3);
    
    ListNodePosi(int) p3 = list.search(0); // 小于所有元素
    assert(p3 == nullptr);
}

// 测试最大元素查找
void testSelectMax() {
    std::cout << "\n=== Testing Select Max ===" << std::endl;
    
    List<int> list;
    list.insertAsLast(3);
    list.insertAsLast(5);
    list.insertAsLast(2);
    list.insertAsLast(7);
    list.insertAsLast(1);
    printList(list, "List for selectMax");
    
    ListNodePosi(int) maxNode = list.selectMax();
    assert(maxNode != nullptr && maxNode->data == 7);
    
    ListNodePosi(int) maxNode2 = list.selectMax(list.first(), 3); // 前3个元素中的最大值
    assert(maxNode2 != nullptr && maxNode2->data == 5);
}

void run_list_test() {
    std::cout << "===== Starting List Tests =====" << std::endl;
    
    testConstructorAndBasic();
    testRemoveAndClear();
    testFind();
    testSearch();
    testSelectMax();
    testUnique();
    testSort();
    testReverse();
    testException();
    
    std::cout << "\n===== All Tests Passed Successfully =====" << std::endl;
}