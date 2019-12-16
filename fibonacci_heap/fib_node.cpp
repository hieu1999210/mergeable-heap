#include "fib_node.h"


template<typename dataT, typename countT>
void
FibNode<dataT, countT>::init() {
    this->parent = nullptr;
    this->left = this;
    this->right = this;
    this->child = nullptr;
    this->children_num = 0;
    this->data = nullptr;
    this->mark = false;
}


template<typename dataT, typename countT>
FibNode<dataT, countT>* 
FibNode<dataT, countT>::merge_list(FibNode<dataT, countT> * list) {
    if (list == nullptr) {
        // std::cout << "here\n";
        return this;
    }
    this->right->left = list->left;
    list->left->right = this->right;
    this->right = list;
    list->left = this;
    // std::cout << "Here\n";
    return this;
}


template<typename dataT, typename countT>
FibNode<dataT, countT>* 
FibNode<dataT, countT>::merge_tree(FibNode<dataT, countT> * subtree) {
    //remove subtree from the root list
    subtree->remove_from_list();
    
    //add subtree to parent_tree
    if (this->child == nullptr) this->child = subtree;
    else this->child->merge_list(subtree);
    // std::cout << "Here\n";
    //update parent
    subtree->parent = this;

    //update child num
    ++(this->children_num);

    //clear mark of subtree
    this->mark = false;

    return this;
}


template<typename dataT, typename countT>
FibNode<dataT, countT> *
FibNode<dataT, countT>::remove_from_list() {
    if (this == this->left) return nullptr;
    FibNode<dataT, countT>* next_node = this->left;
    this->left->right = this->right;
    this->right->left = this->left;
    this->left = this->right = this;

    
    return next_node;
}


template<typename dataT, typename countT>
void 
FibNode<dataT, countT>::display_list() {
    FibNode <dataT> * head = this;
    FibNode <dataT> * current = this;
    do {
        current->display_node();
        current = current->right;
    }
    while(current != head);
}


template<typename dataT, typename countT>
void 
FibNode<dataT, countT>::display_tree() {
    display_node();
    
    if (this->child) {
        FibNode<dataT, countT> * current = this->child;
        FibNode * first_child = current;

        do {
            current->display_tree();
            current = current->right;
        } while (current != first_child);
    }
}