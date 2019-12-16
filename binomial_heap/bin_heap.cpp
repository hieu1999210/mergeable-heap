#include "bin_heap.h"

template<typename dataT, typename countT>
BinHeap<dataT, countT>::BinHeap(bool (*cmp)(const dataT &, const dataT &)) {
    trees_list = nullptr;
    top_node = nullptr;
    // tree_num = 0;
    node_num = 0;

    this->cmp = cmp;
}


template<typename dataT, typename countT>
void
BinHeap<dataT, countT>::display() {
    if (this->empty()) {
        puts(" Empty heap.");
        return;
    }
    countT tree_count = 1;
    BinNode<dataT, countT> * current_tree = this->trees_list;
    while (current_tree != nullptr) {
        printf("tree %u: ", tree_count);
        current_tree->display_node();
        if (current_tree->child != nullptr) {
            std::cout << "[";
            current_tree->child->display_tree();
            std::cout << "]";
        }
        current_tree = current_tree->sibling;
        puts(" ");
        ++tree_count;
    }
}


template<typename dataT, typename countT>
BinNode<dataT, countT> *
BinHeap<dataT, countT>::push(dataT & data) {
    BinNode<dataT, countT> * node = new BinNode<dataT, countT>(data);
    node->sibling = this->trees_list;
    this->trees_list = this->consolidate(node);

    ++this->node_num;
    if (this->top_node == nullptr || cmp_node(this->top_node, node)) top_node = node;

    return node;
}


template<typename dataT, typename countT>
BinNode<dataT, countT> *
BinHeap<dataT, countT>::push(dataT && data) {
    BinNode<dataT, countT> * node = new BinNode<dataT, countT>(data);
    node->sibling = this->trees_list;
    this->trees_list = this->consolidate(node);

    ++this->node_num;
    if (this->top_node == nullptr || cmp_node(this->top_node, node)) top_node = node;
    // std::cout << "here";
    return node;
}


template<typename dataT, typename countT>
BinNode<dataT, countT> *
BinHeap<dataT, countT>::consolidate(BinNode<dataT, countT> * head) {
    BinNode<dataT, countT> * current = head;
    BinNode<dataT, countT> * next = current->sibling;
    BinNode<dataT, countT> * prev = nullptr;
    while (next != nullptr) {
        if ((current->children_num != next->children_num) ||
            (next->sibling != nullptr && 
             current->children_num == next->sibling->children_num)) {
            prev = current;
            current = next;
        } else if (cmp_node(next, current)) {
            current->sibling = next->sibling;
            current->merge_tree(next);
        } else {
            if (prev == nullptr) head = next;
            else prev->sibling = next;
            next->merge_tree(current);
            current = next;
        }
        next = current->sibling;
    }
    // std::cout << "here";
    return head;
}


template<typename dataT, typename countT>
void
BinHeap<dataT, countT>::merge(BinHeap<dataT, countT> & heap) {
    if (heap.empty()) return;
    BinNode<dataT, countT> * current = heap.trees_list->merge_trees_list(this->trees_list);
    current = consolidate(current);
    this->trees_list = current;
    this->node_num += heap.node_num;
    if (this->cmp_node(this->top_node, heap.top_node)) 
        this->top_node = heap.top_node;
}


template<typename dataT, typename countT>
void
BinHeap<dataT, countT>::pop() {
    if (this->empty()) return;

    BinNode<dataT, countT> * current = this->trees_list;

    // remove top_node from trees_list
    if (current == this->top_node) {
        this->trees_list = this->top_node->sibling;
    } else {
        //find prev of top_node
        while (current->sibling != this->top_node) current = current->sibling;

        // remove top_node from trees_list
        current->sibling = this->top_node->sibling;
    }

    // merge children of top_node to trees_list
    if (top_node->children_num > 0) {
        // reverse children_list of top_node
        BinNode<dataT, countT> * child = this->top_node->child;
        BinNode<dataT, countT> * temp;
        current = nullptr;
        while (child != nullptr) {
            child->parent = nullptr;
            temp = child->sibling;
            child->sibling = current;
            current = child;
            child = temp;
        }

        // merge children of top_node to trees_list
        current = current->merge_trees_list(this->trees_list);
        current = consolidate(current);
        this->trees_list = current;
    }

    --this->node_num;
    delete this->top_node;

    // update top node;
    this->top_node = this->trees_list;
    current = this->trees_list;
    while (current != nullptr) {
        if (cmp_node(this->top_node, current)) this->top_node = current;
        current = current->sibling;
    }
}


template<typename dataT, typename countT>
void
BinHeap<dataT, countT>::change_value(BinNode<dataT, countT> * node, dataT & new_data) {
    node->data = &new_data;
    BinNode<dataT, countT> * parent = node->parent;
    while (parent != nullptr && cmp_node(parent, node)) {
        // swap data
        dataT * temp = node->data;
        node->data = parent->data;
        parent->data = temp;

        node = parent;
        parent = node->parent;
    }
}


template<typename dataT, typename countT>
void
BinHeap<dataT, countT>::change_value(BinNode<dataT, countT> * node, dataT && new_data) {
    node->data = &new_data;
    BinNode<dataT, countT> * parent = node->parent;
    while (parent != nullptr && cmp_node(parent, node)) {
        // swap data
        dataT * temp = node->data;
        node->data = parent->data;
        parent->data = temp;
        // std::cout << "here"; 
        node = parent;
        parent = node->parent;
    }
}