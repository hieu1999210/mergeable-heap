#include <iostream>
#include "fibon_heap.h"
#include "fib_node.h"
#include <math.h>
#include <stdio.h>

template<typename dataT, typename countT>
FibHeap<dataT, countT>::FibHeap(bool (*cmp)(const dataT &, const dataT &)) {
    top_node = nullptr;
    root_list = nullptr;
    tree_num = 0;
    node_num = 0;
    this->cmp = cmp;
}


template<typename dataT, typename countT>
FibNode<dataT, countT> *
FibHeap<dataT, countT>::push(dataT & data) {
    FibNode<dataT, countT> * node = new FibNode<dataT, countT>(data);
    node->merge_list(this->root_list);
    if (this->empty()) {
        this->top_node = node;
        this->root_list = node;
    }
    else if (!cmp(data, *(this->top_node->data))) top_node = node;

    ++(this->node_num);
    ++(this->tree_num);

    return node;
}


template<typename dataT, typename countT>
FibNode<dataT, countT> *
FibHeap<dataT, countT>::push(dataT && data) {
    FibNode<dataT, countT> * node = new FibNode<dataT, countT>(data);
    node->merge_list(this->root_list);
    if (this->empty()) {
        this->top_node = node;
        this->root_list = node;
    }
    else if (!cmp(data, *(this->top_node->data))) top_node = node;

    ++(this->node_num);
    ++(this->tree_num);
    return node;
}


template<typename dataT, typename countT>
void
FibHeap<dataT, countT>::display() {
    if (this->empty()) {
        puts(" Empty heap.");
        return;
    }
    countT tree_count = 1;
    countT tree_num = this->tree_num;
    FibNode<dataT, countT> * current_tree = this->root_list;
    while (tree_count <= tree_num) {
        printf("tree %u: ", tree_count);
        current_tree->display_tree();
        current_tree = current_tree->right;
        puts(" ");
        ++tree_count;
    }
}


template<typename dataT, typename countT>
FibHeap<dataT, countT> &
FibHeap<dataT, countT>::merge(FibHeap<dataT, countT> & heap) {
    this->node_num += heap.node_num;
    this->tree_num += heap.tree_num;
    
    if(cmp(this->top(), heap.top())) {
        this->top_node = heap.top_node;
    }

    this->root_list->merge_list(heap.root_list);
    return *this;
}


template<typename dataT, typename countT>
void
FibHeap<dataT, countT>::pop() {
    if (this->empty()) return;
    
    FibNode<dataT, countT> * top_node = this->top_node;
    FibNode<dataT, countT> * child = top_node->child;
    countT child_num = top_node->children_num;
    // std::cout << child_num << "here---\n";
    while (child_num > 0) {
        --child_num;

        //update parent
        child->parent = nullptr;
        child = child->right;
    }
    // child->display_list();
    // std::cout << "\nbeforehere\n" << this->tree_num << std::endl;
    //merge child_list to root_list
    if (this->top_node->children_num > 0) child->merge_list(this->root_list);
    // update tree_num
    this->tree_num += top_node->children_num;

    // this->root_list->display_list();
    // std::cout << "\nbeforehere\n" << this->tree_num << std::endl;
    //remove top_node from the root_list
    //update root_list (in case root_list point to top_node)
    this->root_list = top_node->remove_from_list();

    // this->root_list->display_list();
    // std::cout << "\nbeforehere\n" << this->tree_num << std::endl;
    // std::cout << "here---";
    delete top_node;
    --this->tree_num;
    if (this->tree_num == 0) {
        this->top_node = nullptr;
    } else {
        this->consolidate();
    }
    // std::cout << "here---";
    //consolidate
    
    // std::cout << "here---";
    //update node_num    
    --this->node_num;
}


template<typename dataT, typename countT>
void
FibHeap<dataT, countT>::consolidate() {
    // bound of child num: log2(node_num)
    countT max_child_num = (countT) log2((double) this->node_num) + 2;
    // std::cout << "max child num: " << max_child_num << std::endl;
    // std::cout << "here---";
    /*
    tree_array: to keep tract of tree with their child_nums,
    store tree pointers indexed by their child_num
    
    */
    FibNode<dataT, countT> ** tree_array =  new FibNode<dataT, countT>*[max_child_num];
    for (countT i = 0; i < max_child_num; ++i) {
        tree_array[i] = nullptr;
    }
    // top_node might be deleted by the time consolidate is called
    this->top_node = this->root_list;
    FibNode<dataT, countT> * current_tree = this->root_list;
    FibNode<dataT, countT> * next_tree = nullptr;
    FibNode<dataT, countT> * visited_tree;
    countT tree_count = this->tree_num;
    // std::cout << "tree num" << tree_count << std::endl;
    countT child_num;
    // loop iterate through all tree
    // this loop will merge trees which have the same child_num,
    //at the same time update heap->min_node;
    while (tree_count > 0) {
        --tree_count;
        next_tree = current_tree->right;
        child_num = current_tree->children_num;
        // current_tree->display_node();
        // std::cout << "\n";
        while(visited_tree = tree_array[child_num]) {
            // merge current tree and visited tree
            // std::cout << "\dataT inner loop: ";
            // visited_tree->display_node();
            // std::cout << "\n";
            if(cmp_node(visited_tree, current_tree)) {
                // std::cout << "before merge Here\n";
                // visited_tree->display_node();
                current_tree->merge_tree(visited_tree);
                
            } else
                current_tree = visited_tree->merge_tree(current_tree);
            
            //update tree_num after merging trees
            --(this->tree_num);
            tree_array[child_num] = nullptr;
            ++child_num;
        }
        // std::cout << "here---";
        tree_array[child_num] = current_tree;

        //update heap min
        if (cmp_node(this->top_node, current_tree))
            this->top_node = current_tree;
        // std::cout << "here---";
        //update current tree for the next iteration
        current_tree = next_tree;
    }
    // std::cout << "here---";
    // std::cout << "final child num" << this->tree_num;
    this->root_list = this->top_node;
    // std::cout << "here---";
    delete [] tree_array;
    // std::cout << "here---";
}


template<typename dataT, typename countT>
void
FibHeap<dataT, countT>::change_value(FibNode<dataT, countT> * node, dataT & new_data) {
    node->data = &new_data;
    FibNode<dataT, countT> * parent = node->parent;
    if (parent != nullptr && cmp(*(parent->data), new_data)) {
        this->cut(node);
        this->cascading_cut(parent);
    }

    if (cmp(this->top(), new_data)) this->top_node = node;
}


template<typename dataT, typename countT>
void
FibHeap<dataT, countT>::change_value(FibNode<dataT, countT> * node, dataT && new_data) {
    node->data = &new_data;
    FibNode<dataT, countT> * parent = node->parent;
    if (parent != nullptr && cmp(*(parent->data), new_data)) {
        this->cut(node);
        this->cascading_cut(parent);
    }

    if (cmp(this->top(), new_data)) this->top_node = node;
}


template<typename dataT, typename countT>
void
FibHeap<dataT, countT>::cut(FibNode<dataT, countT> * node) {
    FibNode<dataT, countT> * parent = node->parent;

    //remove node from child_list of its parent
    parent->child = node->remove_from_list();
    --parent->children_num;

    // insert child to tree list
    this->root_list->merge_list(node);
    ++this->tree_num;

    node->parent = nullptr;
    node->mark = false;
}


template<typename dataT, typename countT>
void
FibHeap<dataT, countT>::cascading_cut(FibNode<dataT, countT> * node) {
    FibNode<dataT, countT> * parent = node->parent;

    if (parent != nullptr) {
        if (!node->mark) // if node->mark == false

            /* the cascading_cut follows cut procedure 
            of the child of current node
            node->mark = false means that before cut mark = false
            so only one child of this node is cut*/
            node->mark = true;
        else { // mean 2 children of current node have been removed
            cut(node);
            cascading_cut(parent);
        }
    }
}

