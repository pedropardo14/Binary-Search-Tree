// mymap.h
//
// AUTHOR: Pedro Pardo
// IDE: VSCode on MacOS
// 
// This Program will take a spin on a classic Binary Search Tree and impliment a Singly Threaded Binary Tree.
// Everthing writen in this code is helpful for using many different features of a Threaded BST and will allow you to acess different data of the tree.

#pragma once

#include <iostream>
#include <sstream>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {
            if(curr == nullptr){ //checks if curr equals null to return null
                return iterator(nullptr);
            }
            if(curr->isThreaded == true){ //when the node is threaded
                curr = (curr->isThreaded) ? nullptr: curr->right; //go right
                return iterator(curr); //return node
            }
            else{ //when thread isnt true
                curr = curr->right; //go right
                if(curr == nullptr){ //check for null
                    return iterator(nullptr);
                }
                while(curr->left != nullptr){ //go left most
                    curr = curr->left;
                }
                return iterator(curr); //return node
            }
        }
    };

    void _toString(NODE* node, ostream& output){ //makes a string based on the bst
        if (node == nullptr) { //return if tree is empty
            return;
        } 
        else{ //if tree is populated
            _toString(node->left, output); //traverses left
            output << "key: " << node->key << " value: "  << node->value << "\n";
            if(node->isThreaded){
                node = nullptr;
                _toString(node, output);
            }
            else{
                _toString(node->right, output); //traverses right 
            }
        }
    }

    void _clear(NODE* node) { //helper function to clear a bst
        if (node == nullptr) { //when tree is empty return
            return;
        } 
        else {
            _clear(node->left); //traverse left
            if(node->isThreaded){
                node = nullptr;
                _clear(node); 

            }
            else{
                _clear(node->right); //traverse right
            }
            delete node; //deletes the node
        }
    }

    NODE* _copy(NODE* original, NODE* parent){ //helper function for copy constructor
        if (original == nullptr) { //return when BST is empty
            return nullptr;
        }
        else{ //if bst isnt empty
            NODE* n = new NODE; //creates a new node for copy
            n->key = original->key; //copy over key
            n->value = original->value; //copy over value
            n->isThreaded = original->isThreaded; //copy over thread
            n->left = nullptr;
            n->right = original->right; //copy linked threaded node
            n->nL = 0;
            n->nR = 0;
            this->size++;
            n->left = _copy(original->left, n); //traverses through the left 
            n->right = _copy(original->right, n); //travserses through the right
            return n; //returns the copied nodes
        }
    }

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() {
        root = nullptr;
        size = 0;
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) {
        NODE *original = other.root; //set temp node to the other root
        NODE *newCopy = nullptr;
        size = 0;
        newCopy = _copy(original, newCopy); //creates a copt of the tree based on this new node and the other tree
        this->root = newCopy; //makes the main root into the new bst

    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) {
        clear();   //clear tree
        NODE *original = other.root; //set temp node to the other root
        NODE *newCopy = nullptr;
        newCopy = _copy(original, newCopy); //creates a copt of the tree based on this new node and the other tree
        this->root = newCopy; //makes the main root into the new bst
        return *this; //returns the copied tree
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() {
        NODE *node = root;
        _clear(node);
        size = 0;
        root = nullptr;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() {
        clear();
    }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) {
        NODE* prev = nullptr;
        NODE* cur = root;
        NODE* succ = nullptr;

        while(cur != nullptr){ // when the node doesnt hit null
            if(key == cur->key){ //when the key is a duplicate
                cur->value = value; //set new value
                return;
            }
            else if(key < cur->key){ //when key needs to go left
                succ = cur; //documents a parent node
                prev = cur;
                cur = cur->left; //go left
            }
            else{
                prev = cur;
                cur = (cur->isThreaded) ? nullptr: cur->right; //checks for thread 
            }
        }

        NODE* n = new NODE; //creates anther temp node for use
        n->key = key;
        n->value = value;
        n->isThreaded = false;
        n->left = nullptr;
        n->right = nullptr;
        n->nL = 0;
        n->nR = 0;

        if(prev == nullptr){ //if there isnt any nodes 
            root = n; //set root equal to this temp node
        }
        else if(key < prev->key){ //if value is less then the previous
            prev->left = n; //set the value to the left
        }
        else if(key > prev->key){ //if value is more then the other
            prev->right = n; //set it to the right
        }
        else if(succ != nullptr){ //links to thread
            n->right = succ;
            n->isThreaded = true;
        }
        size++; //increase size 
    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) {
        NODE* temp = root; 

        while(temp != nullptr){ //checks tree until null
            if(temp->key == key){ //if key is found
                return true;
            }
            else if(key < temp->key){ //if not go left
                temp = temp->left;
            }
            else{ //go right
                temp = (temp->isThreaded) ? nullptr: temp->right;
            }
        }
        return false; //if not true return false
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) {
        NODE* temp = root;

        while(temp != nullptr){ //checks until null
            if(temp->key == key){ //checks if key is founf
                return temp->value;
            }
            else if(key < temp->key){ //goes left
                temp = temp->left;
            }
            else{ //goes right
                temp = (temp->isThreaded) ? nullptr: temp->right; 
            }
        }

        return valueType(); //if not found return 
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) {
        NODE* temp = root;

        while(temp != nullptr){ //goes up until null
            if(temp->key == key){ //checks if key is found
                return temp->value;
            }
            else if(key < temp->key){ //checks left
                temp = temp->left;
            }
            else{ //checks right
                temp = (temp->isThreaded) ? nullptr: temp->right;
            }
        }

        put(key, valueType()); //if not found its inserted
        return valueType(); //returns the value
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;  //returns size
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() {
        NODE *cur = root;
        if(cur == nullptr){ //checks if root is null
            return iterator(nullptr);
        }
        while(cur->left){ //goes all the way left
            cur = cur->left;
        }
        return iterator(cur); //returns left-most node
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // 
    // Time Complexity: O(1)
    //
    iterator end() {
        return iterator(nullptr);
    }

    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() {
        if (this->size == 0) { //when tree is empty
            return ""; //return empty string
        } 
        else{ //when tree is populated
            stringstream ss; 
            _toString(this->root, ss); //call the helper with root and the stringstream
            string str = ss.str();
            return str;
        }
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<pair<keyType, valueType> > toVector() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() {


        // TODO: write this function.


        return {};  // TODO: Update this return.
    }
};
