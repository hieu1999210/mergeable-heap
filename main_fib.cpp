#include <iostream>
#include "data.h"
#include "fib_node.h"
#include <string>
#include <queue>
#include <vector>
#include <typeinfo>
#include "fibon_heap.h"
template<typename dataT, typename countT>
bool cmp(const dataT & first, const dataT & second) {
    return first < second;
}

bool cmp(const Data & first, const Data & second) {
    return first.value < second.value;
}

int
main () {
    // int a=0, b=1;
    // int * c = &a;
    // int * d = &b;
    // cmp<int>(*c, *d);
    FibHeap<int> heap, heap2;
    FibNode<int>* a[7];
    a[1] = heap.push(1);
    a[2] = heap.push(2);
    a[3] = heap.push(3);
    // heap.consolidate();
    a[4] = heap.push(4);
    a[5] = heap.push(5);
    // a[6] = heap.push(6);
    // heap.consolidate();
    heap.pop();
    // std::cout << heap.top() << std::endl;
    heap.change_value(a[1], 10);
    // std::cout << a[1]->parent;
    heap.display();
    std::cout << heap.tree_num;
    // Data a("test", 0);
    // std::cout << a;
    // int a=1, b=4;
    // FibHeap<Data> heap(cmp);
    // Data a("one", 1);
    // Data b("two", 2);
    // heap.push(a);
    // heap.push(b);
    // heap.display();
    // heap.top().display();
    // std::cout << heap.top();
    // std::ios_base::sync_with_stdio(0);
	// std::cin.tie(0);
    // Data data("head", 0);
    // FibNode<Data> node0(data);
    // node0.display_node();
    // FibNode<Data*> node(new Data("Test", 0));
    // (*(node.data))->display();
    // FibNode<Data> * head = new FibNode<Data>(new Data("head", 0));
    // // head.data = data;
    // FibNode<Data> * current = new FibNode<Data>(new Data("one", 1));
    // head->merge_list(current);
    // current = new FibNode<Data>(new Data("two", 2));
    // head->merge_list(current);
    // current = new FibNode<Data>(new Data("three", 3));
    // head->merge_list(current);
    // current = new FibNode<Data>(new Data("four", 4));
    // head->merge_list(current);
    // current = new FibNode<Data>(new Data("five", 5));
    // head->merge_list(current);
    // head->right->display_list();
    // head.display_node();

    // data->display();
    // Data data = Data("head", 0);
    // data.display();
    // std::priority_queue<Data, std::vector<Data>> Q(cmp);
    // Q.push(data);
    // // Q.push(2);
    // // Q.push
    // Data data2 = Q.top();
    // data2.display();
    // std::cout << Q.top().display();
    // bool (*test)(int *, long &);
    // // std::cout << test;
    // std::cout << typeid(test).name() << '\n';
}