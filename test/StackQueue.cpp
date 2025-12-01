#include "../include/Stack_and_Quene.hpp"
#include <iostream>
#include <cassert>

using namespace std;

// 运行时详细输出控制
static bool isVerbose() {
    static int v = getenv("TEST_VERBOSE") ? 1 : 0;
    return v;
}

void run_stackqueue_test() {
    cout << "\n===== 开始 栈/队列 测试 =====" << endl;

    // Stack 测试
    {
        Stack<int> s;
        if (isVerbose()) cout << "Stack: 初始 size=" << s.size() << '\n';
        assert(s.size() == 0);
        if (isVerbose()) cout << "Stack: push 10" << '\n';
        s.push(10);
        if (isVerbose()) cout << "Stack: push 20" << '\n';
        s.push(20);
        if (isVerbose()) cout << "Stack: push 30" << '\n';
        s.push(30);
        if (isVerbose()) cout << "Stack: size=" << s.size() << '\n';
        assert(s.size() > 0);
        assert(s.top() == 30);
        int popped = s.pop();
        if (isVerbose()) cout << "Stack: pop=" << popped << " top=" << s.top() << '\n';
        assert(popped == 30);
        assert(s.top() == 20);
        if (isVerbose()) cout << "Stack: top=" << s.top() << '\n';
        s.pop(); s.pop();
        if (isVerbose()) cout << "Stack: after pops size=" << s.size() << '\n';
        assert(s.size() == 0);
    }

    // Queue 测试
    {
        Queue<int> q;
        if (isVerbose()) cout << "Queue: 初始 size=" << q.size() << '\n';
        assert(q.size() == 0);
        if (isVerbose()) cout << "Queue: enqueue 1" << '\n';
        q.enqueue(1);
        if (isVerbose()) cout << "Queue: enqueue 2" << '\n';
        q.enqueue(2);
        if (isVerbose()) cout << "Queue: enqueue 3" << '\n';
        q.enqueue(3);
        if (isVerbose()) cout << "Queue: size=" << q.size() << " front=" << q.front() << '\n';
        assert(q.size() > 0);
        assert(q.front() == 1);
        int v = q.dequeue();
        if (isVerbose()) cout << "Queue: dequeue=" << v << '\n';
        assert(v == 1);
        if (isVerbose()) cout << "Queue: front=" << q.front() << '\n';
        assert(q.front() == 2);
        if (isVerbose()) cout << "Queue: dequeue rest" << '\n';
        q.dequeue(); q.dequeue();
        if (isVerbose()) cout << "Queue: after dequeues size=" << q.size() << '\n';
        assert(q.size() == 0);
    }

    cout << "===== 栈/队列 测试通过 =====" << endl << endl;
}
