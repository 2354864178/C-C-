#include <ctime>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "D:\study\vscode\Project\dsacpp\src\DataStructure\List.hpp"  
#include "D:\study\vscode\Project\dsacpp\src\DataStructure\Vector.hpp"

using namespace std;

// 辅助函数：检查向量是否有序
template <class T>
bool isSorted(const Vector<T>& v) {
    for (int i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) return false;
    }
    return true;
}

// 辅助函数：打印向量内容（类似List的printList）
template <typename T>
void printVector(const Vector<T>& vec, const std::string& name) {
    std::cout << name << " (size=" << vec.size() << "): ";
    if (vec.size() == 0) {
        std::cout << "Empty";
    } else {
        for (int i = 0; i < vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
    }
    std::cout << std::endl;
}

// 测试构造函数
void testConstructor() {
    cout << "=== 测试构造函数 ===" << endl;
    
    // 默认构造
    Vector<int> v1;
    printVector(v1, "默认构造的v1");
    assert(v1.size() == 0);

    // 指定容量、规模和初始值
    Vector<int> v2(5, 3, 2);  // 容量5，规模3，初始值2
    printVector(v2, "指定参数构造的v2");
    assert(v2.size() == 3);
    assert(v2[0] == 2 && v2[1] == 2 && v2[2] == 2);

    // 从数组构造
    int arr[] = {1, 2, 3, 4};
    Vector<int> v3(arr, 4);
    printVector(v3, "从数组构造的v3");
    assert(v3.size() == 4);
    assert(v3[0] == 1 && v3[1] == 2 && v3[2] == 3 && v3[3] == 4);

    // 数组区间构造（[1,3)索引）
    Vector<int> v4(arr, 1, 3);
    printVector(v4, "数组区间构造的v4");
    assert(v4.size() == 2);
    assert(v4[0] == 2 && v4[1] == 3);

    // 拷贝构造
    Vector<int> v5(v3);
    printVector(v5, "拷贝v3构造的v5");
    assert(v5.size() == 4);
    assert(v5[0] == 1 && v5[3] == 4);

    // 拷贝区间构造（v3的[1,3)索引）
    Vector<int> v6(v3, 1, 3);
    printVector(v6, "v3区间构造的v6");
    assert(v6.size() == 2);
    assert(v6[0] == 2 && v6[1] == 3);

    cout << "构造函数测试通过" << endl << endl;
}

// 测试运算符重载
void testOperator() {
    cout << "=== 测试运算符重载 ===" << endl;
    int arr[] = {10, 20, 30};
    Vector<int> v(arr, 3);
    printVector(v, "初始v");
    
    // 测试[]访问
    assert(v[0] == 10 && v[1] == 20);
    cout << "v[2]修改前: " << v[2] << endl;
    v[2] = 300;  // 测试[]修改
    cout << "v[2]修改后: " << v[2] << endl;
    assert(v[2] == 300);
    printVector(v, "修改后的v");

    // 测试赋值运算符
    Vector<int> v2;
    v2 = v;  // 深拷贝
    printVector(v2, "赋值后的v2");
    assert(v2.size() == 3);
    assert(v2[0] == 10 && v2[1] == 20 && v2[2] == 300);
    
    // 验证深拷贝（修改v2不影响v）
    v2[0] = 100;
    printVector(v2, "修改v2[0]后的v2");
    printVector(v, "此时的v（验证深拷贝）");
    assert(v[0] == 10);

    cout << "运算符重载测试通过" << endl << endl;
}

// 测试插入功能
void testInsert() {
    cout << "=== 测试插入功能 ===" << endl;
    Vector<int> v;
    printVector(v, "初始v");
    
    // 尾部插入
    v.insert(5);  // 尾部插入5
    printVector(v, "尾部插入5后的v");
    assert(v.size() == 1 && v[0] == 5);

    // 指定位置插入（索引0）
    v.insert(0, 3);  // 索引0插入3
    printVector(v, "索引0插入3后的v");
    assert(v.size() == 2 && v[0] == 3 && v[1] == 5);

    // 指定位置插入（索引1）
    v.insert(1, 4);  // 索引1插入4
    printVector(v, "索引1插入4后的v");
    assert(v.size() == 3);
    assert(v[0] == 3 && v[1] == 4 && v[2] == 5);

    // 测试扩容（连续尾部插入）
    cout << "开始连续尾部插入（测试扩容）..." << endl;
    v.insert(6);
    v.insert(7);
    v.insert(8);
    v.insert(9);
    printVector(v, "连续插入6,7,8,9后的v");
    assert(v.size() == 7 && v[6] == 9);

    cout << "插入功能测试通过" << endl << endl;
}

// 测试删除功能
void testRemove() {
    cout << "=== 测试删除功能 ===" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    Vector<int> v(arr, 5);
    printVector(v, "初始v");

    // 单元素删除（索引2）
    int removed = v.remove(2);  // 删除索引2的元素
    cout << "删除索引2的元素，返回值: " << removed << endl;
    printVector(v, "删除后的v");
    assert(removed == 3 && v.size() == 4);
    assert(v[0] == 1 && v[1] == 2 && v[2] == 4 && v[3] == 5);

    // 区间删除（[1,3)索引）
    int n = v.remove(1, 3);  // 删除索引1到2的元素
    cout << "删除区间[1,3)的元素，删除数量: " << n << endl;
    printVector(v, "区间删除后的v");
    assert(n == 2 && v.size() == 2);
    assert(v[0] == 1 && v[1] == 5);

    // 测试缩容（删除索引0）
    v.remove(0);  // 删除仅剩的第一个元素
    printVector(v, "删除索引0后的v（测试缩容）");
    assert(v.size() == 1 && v[0] == 5);

    cout << "删除功能测试通过" << endl << endl;
}

// 测试查找功能
void testFind() {
    cout << "=== 测试查找功能 ===" << endl;
    int arr[] = {1, 3, 5, 7, 9};
    Vector<int> v(arr, 5);
    printVector(v, "用于查找的v");

    // 全局查找
    int pos3 = v.find(3);
    int pos7 = v.find(7);
    int pos2 = v.find(2);
    cout << "查找3的位置: " << pos3 << "（预期1）" << endl;
    cout << "查找7的位置: " << pos7 << "（预期3）" << endl;
    cout << "查找2的位置: " << pos2 << "（预期-1）" << endl;
    assert(pos3 == 1 && pos7 == 3 && pos2 == -1);

    // 区间查找（[0,3)索引内找5）
    int pos5 = v.find(5, 0, 3);
    cout << "区间[0,3)查找5的位置: " << pos5 << "（预期2）" << endl;
    // 区间查找（[2,5)索引内找3）
    int pos3_2 = v.find(3, 2, 5);
    cout << "区间[2,5)查找3的位置: " << pos3_2 << "（预期-1）" << endl;
    assert(pos5 == 2 && pos3_2 == -1);

    // 二分查找
    int bin5 = v.binSearch(5, 0, 5);
    cout << "二分查找5的位置: " << bin5 << "（预期2）" << endl;
    assert(bin5 == 2);

    cout << "查找功能测试通过" << endl << endl;
}

// 测试排序功能
void testSort() {
    cout << "=== 测试排序功能 ===" << endl;
    int arr[] = {5, 3, 1, 4, 2};
    
    // 冒泡排序
    Vector<int> v1(arr, 5);
    printVector(v1, "冒泡排序前的v1");
    v1.bubbleSort();
    printVector(v1, "冒泡排序后的v1");
    assert(isSorted(v1));

    // 选择排序
    Vector<int> v2(arr, 5);
    printVector(v2, "选择排序前的v2");
    v2.selectionSort();
    printVector(v2, "选择排序后的v2");
    assert(isSorted(v2));

    // 区间排序（[3,9)索引）
    int arr2[] = {9, 7, 8, 3, 2, 1, 4, 5, 6};
    Vector<int> v5(arr2, 9);
    printVector(v5, "区间排序前的v5");
    v5.bubbleSort(3, 9);  // 仅排序索引3到8的元素
    printVector(v5, "区间[3,9)排序后的v5");
    assert(v5[0] == 9 && v5[1] == 7 && v5[2] == 8);  // 前3个元素不变
    assert(isSorted(Vector<int>(v5, 3, 9)));  // 排序区间有序

    cout << "排序功能测试通过" << endl << endl;
}

// 测试去重功能
void testDeduplicate() {
    cout << "=== 测试去重功能 ===" << endl;
    // 无序去重
    int arr[] = {1, 2, 3, 2, 1, 4, 5, 4};
    Vector<int> v(arr, 8);
    printVector(v, "无序去重前的v");
    int n = v.deduplicate();  // 无序去重
    cout << "无序去重删除的元素数量: " << n << endl;
    printVector(v, "无序去重后的v");
    assert(n == 3 && v.size() == 5);
    assert(v[0] == 1 && v[1] == 2 && v[2] == 3 && v[3] == 4 && v[4] == 5);

    // 有序去重
    int arr2[] = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    Vector<int> v2(arr2, 9);
    printVector(v2, "有序去重前的v2");
    v2.uniquify();  // 有序去重
    printVector(v2, "有序去重后的v2");
    assert(v2.size() == 5);
    assert(v2[0] == 1 && v2[1] == 2 && v2[2] == 3 && v2[3] == 4 && v2[4] == 5);

    cout << "去重功能测试通过" << endl << endl;
}

// 测试置乱功能
void testUnsort() {
    cout << "=== 测试置乱功能 ===" << endl;
    int arr[] = {1, 2, 3, 4, 5, 6};
    Vector<int> v(arr, 6);
    Vector<int> v2(v);  // 备份原始数据
    printVector(v, "置乱前的v");
    v.unsort();  // 全局置乱
    printVector(v, "全局置乱后的v");

    // 验证置乱效果（大概率不同）
    bool same = true;
    for (int i = 0; i < 6; ++i) {
        if (v[i] != v2[i]) {
            same = false;
            break;
        }
    }
    assert(!same);

    // 区间置乱（[1,4)索引）
    Vector<int> v3(arr, 6);
    printVector(v3, "区间置乱前的v3");
    v3.unsort(1, 4);  // 仅置乱索引1到3的元素
    printVector(v3, "区间[1,4)置乱后的v3");
    assert(v3[0] == 1 && v3[4] == 5 && v3[5] == 6);  // 区间外元素不变

    cout << "置乱功能测试通过" << endl << endl;
}

// 测试遍历功能
void testTraverse() {
    cout << "=== 测试遍历功能 ===" << endl;
    int arr[] = {1, 2, 3, 4};
    Vector<int> v(arr, 4);
    printVector(v, "遍历修改前的v");
    
    // 遍历修改元素（每个元素+10）
    auto add10 = [](int& x) { x += 10; };
    v.traverse(add10);
    printVector(v, "遍历+10后的v");
    assert(v[0] == 11 && v[1] == 12 && v[2] == 13 && v[3] == 14);

    cout << "遍历功能测试通过" << endl << endl;
}

//--------------------------------------------------------------------------------
// 辅助函数：打印列表内容
template <typename T>
void printList(const List<T>& list, const std::string& name) {
    std::cout << name << " (size=" << list.size() << "): ";
    if (list.empty()) {
        std::cout << "Empty" << std::endl;
        return;
    }
    
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
}

// 测试默认构造函数和基本属性
void testDefaultConstructor() {
    cout << "\n=== 测试默认构造函数 ===" << endl;
    List<int> list;
    printList(list, "默认构造的列表");
    assert(list.size() == 0);
    assert(list.empty() == true);
    cout << "默认构造函数测试通过" << endl;
}

// 测试插入操作
void testInsertions() {
    cout << "\n=== 测试插入操作 ===" << endl;
    List<int> list;
    printList(list, "初始列表");
    
    // 测试插入到头部
    list.insertAsFirst(1);
    printList(list, "头部插入1后的列表");
    assert(list.size() == 1);
    assert(list[0] == 1);
    
    // 测试插入到尾部
    list.insertAsLast(3);
    printList(list, "尾部插入3后的列表");
    assert(list.size() == 2);
    assert(list[1] == 3);
    
    // 测试插入到中间
    auto p = list.first();  // 指向1
    list.insertAfter(p, 2);
    printList(list, "1后插入2后的列表");
    assert(list.size() == 3);
    assert(list[0] == 1);
    assert(list[1] == 2);
    assert(list[2] == 3);
    
    // 测试在指定节点前插入
    list.insertBefore(list.last(), 4);
    printList(list, "3前插入4后的列表");
    assert(list.size() == 4);
    assert(list[2] == 4);
    assert(list[3] == 3);
    
    cout << "插入操作测试通过" << endl;
}

// 测试查找操作
void test_List_Find() {
    cout << "\n=== 测试查找操作 ===" << endl;
    List<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.insertAsLast(i);
    }
    list.insertAsLast(3);  // 添加一个重复元素
    printList(list, "用于查找测试的列表");
    
    // 查找存在的元素
    auto p1 = list.find(3);
    assert(p1 != nullptr);
    assert(p1->data == 3);
    cout << "查找3的结果: " << p1->data << "（预期3）" << endl;
    
    // 验证找到的是最后一个匹配元素
    assert(p1->succ->data == 4);  // 最后一个3后面应该是4
    
    // 查找不存在的元素
    auto p2 = list.find(10);
    assert(p2 == nullptr);
    cout << "查找10的结果: " << (p2 == nullptr ? "nullptr" : "存在") << "（预期nullptr）" << endl;
    
    cout << "查找操作测试通过" << endl;
}

// 测试删除操作
void test_List_Remove() {
    cout << "\n=== 测试删除操作 ===" << endl;
    List<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.insertAsLast(i);
    }
    printList(list, "删除前的列表");
    
    // 删除第一个元素
    int val = list.remove(list.first());
    cout << "删除的第一个元素: " << val << "（预期1）" << endl;
    printList(list, "删除第一个元素后的列表");
    assert(val == 1);
    assert(list.size() == 4);
    assert(list[0] == 2);
    
    // 删除中间元素
    val = list.remove(list.first()->succ);  // 删除3
    cout << "删除的中间元素: " << val << "（预期3）" << endl;
    printList(list, "删除中间元素后的列表");
    assert(val == 3);
    assert(list.size() == 3);
    assert(list[0] == 2);
    assert(list[1] == 4);
    
    cout << "删除操作测试通过" << endl;
}

// 测试拷贝构造函数
void testCopyConstructor() {
    cout << "\n=== 测试拷贝构造函数 ===" << endl;
    List<int> original;
    for (int i = 1; i <= 5; ++i) {
        original.insertAsLast(i);
    }
    printList(original, "原始列表");
    
    // 测试完整拷贝
    List<int> copy1(original);
    printList(copy1, "完整拷贝的列表");
    assert(copy1.size() == original.size());
    for (int i = 0; i < original.size(); ++i) {
        assert(copy1[i] == original[i]);
    }
    
    // 测试范围拷贝
    List<int> copy2(original, 1, 3);  // 从索引1开始，拷贝3个元素
    printList(copy2, "范围拷贝的列表");
    assert(copy2.size() == 3);
    assert(copy2[0] == original[1]);
    assert(copy2[1] == original[2]);
    assert(copy2[2] == original[3]);
    
    cout << "拷贝构造函数测试通过" << endl;
}

// 测试异常处理
void testExceptions() {
    cout << "\n=== 测试异常处理 ===" << endl;
    List<int> list;
    for (int i = 1; i <= 3; ++i) {
        list.insertAsLast(i);
    }
    printList(list, "用于异常测试的列表");
    
    // 测试越界访问
    bool exceptionThrown = false;
    try {
        int val = list[10];
    } catch (const std::out_of_range& e) {
        exceptionThrown = true;
        cout << "捕获到预期的异常: " << e.what() << endl;
    }
    assert(exceptionThrown);
    
    cout << "异常处理测试通过" << endl;
}

// 测试清空操作
void testClear() {
    cout << "\n=== 测试清空操作 ===" << endl;
    List<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.insertAsLast(i);
    }
    printList(list, "清空前的列表");
    
    int oldSize = list.clear();
    cout << "清空的元素数量: " << oldSize << "（预期5）" << endl;
    printList(list, "清空后的列表");
    assert(oldSize == 5);
    assert(list.size() == 0);
    assert(list.empty() == true);
    
    cout << "清空操作测试通过" << endl;
}

// 辅助函数：检查列表是否有序
template <typename T>
bool isListSorted(const List<T>& list) {
    if (list.size() <= 1) return true;
    for (int i = 0; i < list.size() - 1; ++i) {
        if (list[i] > list[i + 1]) return false;
    }
    return true;
}

// 测试列表排序功能
void testListSorting() {
    cout << "\n=== 测试列表排序功能 ===" << endl;
    
    // 测试插入排序
    List<int> list1;
    list1.insertAsLast(5);
    list1.insertAsLast(3);
    list1.insertAsLast(1);
    list1.insertAsLast(4);
    list1.insertAsLast(2);
    printList(list1, "插入排序前的列表");
    list1.insertionsort();
    printList(list1, "插入排序后的列表");
    assert(isListSorted(list1));
    
    // 测试选择排序
    List<int> list2;
    list2.insertAsLast(9);
    list2.insertAsLast(7);
    list2.insertAsLast(8);
    list2.insertAsLast(3);
    list2.insertAsLast(2);
    list2.insertAsLast(1);
    printList(list2, "选择排序前的列表");
    list2.selectionsort();
    printList(list2, "选择排序后的列表");
    assert(isListSorted(list2));
    
    // 测试区间插入排序
    List<int> list3;
    for (int i = 1; i <= 10; ++i) {
        list3.insertAsLast(i);
    }
    // 在有序列表中插入无序元素
    list3.insertAfter(list3.first()->succ->succ, 15);
    list3.insertAfter(list3.first()->succ->succ, 12);
    list3.insertAfter(list3.first()->succ->succ, 14);
    printList(list3, "区间排序前的列表");
    // 对前6个元素进行排序
    list3.insertionsort(list3.first(), 6);
    printList(list3, "区间插入排序后的列表");
    // 验证前6个元素有序
    bool first6Sorted = true;
    for (int i = 0; i < 5; ++i) {
        if (list3[i] > list3[i + 1]) {
            first6Sorted = false;
            break;
        }
    }
    assert(first6Sorted);
    
    // 测试区间选择排序
    List<int> list4;
    list4.insertAsLast(5);
    list4.insertAsLast(3);
    list4.insertAsLast(7);
    list4.insertAsLast(1);
    list4.insertAsLast(9);
    list4.insertAsLast(2);
    list4.insertAsLast(8);
    list4.insertAsLast(4);
    list4.insertAsLast(6);
    printList(list4, "区间选择排序前的列表");
    // 对中间5个元素进行排序
    ListNodePosi(int) p = list4.first()->succ; // 从第二个元素开始
    list4.selectionsort(p, 5);
    printList(list4, "区间选择排序后的列表");
    // 验证排序区间有序
    bool mid5Sorted = true;
    for (int i = 1; i < 5; ++i) {  // 索引1到5的元素
        if (list4[i] > list4[i + 1]) {
            mid5Sorted = false;
            break;
        }
    }
    assert(mid5Sorted);
    
    cout << "列表排序功能测试通过" << endl;
}

int main() {
    cout << "=====================================" << endl;
    cout << "          开始测试Vector类           " << endl;
    cout << "=====================================" << endl;
    srand(time(0)); // 初始化随机数种子
    testConstructor();
    testOperator();
    testInsert();
    testRemove();
    testFind();
    testSort();
    testDeduplicate();
    testUnsort();
    testTraverse();
    cout << "=====================================" << endl;
    cout << "        Vector类所有测试通过！       " << endl;
    cout << "=====================================" << endl;


    cout << "\n=====================================" << endl;
    cout << "           开始测试List类            " << endl;
    cout << "=====================================" << endl;
    testDefaultConstructor();
    testInsertions();
    test_List_Find();
    test_List_Remove();
    testCopyConstructor();
    testExceptions();
    testClear();
    testListSorting();
    cout << "\n=====================================" << endl;
    cout << "         所有测试均通过！            " << endl;
    cout << "=====================================" << endl;
    
    return 0;
}
