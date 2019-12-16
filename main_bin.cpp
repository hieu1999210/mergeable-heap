// #include "bin_node.h"
#include "bin_heap.h"
#include "data.h"

bool cmp(const Data & first, const Data & second) {
    return first.value < second.value;
}

int
main () {
    // BinNode<int> node1(1);
    // BinNode<int> node2(2);
    // BinNode<int> node3(3);
    // BinNode<int> node6(6);
    // BinNode<int> node4(4);
    // BinNode<int> node5(5);
    // node1.display_node();
    // std::cout << std::endl;
    // node1.display_tree();
    // node1.merge_tree(&node2);
    // node1.merge_tree(&node3);
    // node1.merge_tree(&node4);
    // node1.merge_tree(&node5);
    // node1.display_tree();
    // BinHeap<int> heap;
    // BinNode<int> * node = heap.push(1);
    // heap.push(2);
    // heap.push(3);
    // heap.push(4);
    // heap.pop();
    // heap.display();
    // heap.change_value(node, 9);
    // heap.display();
    // std::cout << heap.top();

    BinHeap<Data> heap(cmp);
    // Data a("one", 1);
    heap.push(* new Data("one", 1));
    heap.push(* new Data("two", 2));
    heap.push(* new Data("three", 3));
    heap.push(* new Data("four", 4));
    heap.push(* new Data("five", 5));
    heap.push(* new Data("six", 6));
    heap.display();
}