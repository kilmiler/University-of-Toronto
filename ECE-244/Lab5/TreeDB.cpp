//
//  TreeDB.cpp
//  
//
//  Created by Hee Seung Hong on 11/25/19.
//

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#include "TreeDB.h"

// the default constructor, creates an empty database.
TreeDB::TreeDB(){
    root = nullptr;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.
TreeDB::~TreeDB(){
    clear();
}

// inserts the entry pointed to by newEntry into the database.
// If an entry with the same key as newEntry's exists
// in the database, it returns false. Otherwise, it returns true.
bool TreeDB::insert(DBentry* newEntry){
    if(newEntry == nullptr){
        return false;
    }else if(this->root == nullptr){
        this->root = getNewNode(newEntry);
        return true;
    }
    return insert_sup_DBentry(newEntry, this->root);
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount
DBentry* TreeDB::find(string name){
    if(this->root == nullptr){
        return nullptr;
    }
    
    probesCount = 0;
    return find_sup(root, name);
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.
bool TreeDB::remove(string name){
    if(this->root == nullptr){
        return false;
    }else{
        return removal_sup(this->root, name);
    }
}
    
// deletes all the entries in the database.
void TreeDB::clear(){
    clear_sup(this->root);
    this->root = nullptr;
}
    
// prints the number of probes stored in probesCount
void TreeDB::printProbes() const{
    cout << this->probesCount << endl;
    //iostream included
}
   
// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).
void TreeDB::countActive () const{
    int activeNum = countActive_sup(this->root);
    cout << activeNum << endl;
}

// Prints the entire tree, in ascending order of key/name
ostream& operator<< (ostream& out, const TreeDB& rhs){
    TreeNode* nodePtr = rhs.root;
        
    if(nodePtr != nullptr){
        operator<<(out, nodePtr);
    }
}

// You *may* choose to implement the function below to help print the
// tree.  You do not have to implement this function if you do not wish to.
ostream& operator<< (ostream& out, TreeNode* rhs){
    DBentry* DBentryPtr;
    DBentryPtr = rhs->getEntry();
    
    if(rhs != nullptr){
        operator<<(out, rhs->getLeft());
        operator<<(out, DBentryPtr);
        operator<<(out, rhs->getRight());
    }
}



//ADDITIONAL HELPER FUNCTIONS

TreeNode* TreeDB::getNewNode(DBentry* data){
    TreeNode* newNode = new TreeNode(data);
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}


void TreeDB::insert_sup_root(TreeNode* rootPtr, int data){
    if(rootPtr == nullptr){
        rootPtr = getNewNode(data);
    }else if(data < rootPtr->data){
        rootPtr->left = insert_sup_root(rootPtr->left, data);
    }else{
        rootPtr->right = insert_sup_root(rootPtr->right, data);
    }
    return rootPtr;
}

bool TreeDB::insert_sup_DBentry(DBentry* newEntry, TreeNode* rootPtr){
    if(newEntry->getName() = rootPtr->getEntry()->getName()){
        return false;
    }else if(newEntry->getName() < rootPtr->getEntry()->getName()){
        if(rootPtr->getLeft() == nullptr){
            insert_sup_root();
            return true;
        }else{
            return insert_sup_DBentry(newEntry, rootPtr->getLeft());
        }
    }else if(newEntry->getName() > rootPtr->getEntry()->getName()){
        if(rootPtr->getRight() == nullptr){
            insert_sup_root();
            return true;
        }else{
            return insert_sup_DBentry(newEntry, rootPtr->getRight());
        }
    }
}

Dentry* TreeDB::find_sup(TreeNode* nodePtr, string name){
    if(nodePtr == nullptr){
        return nullptr;
    }else{
        probesCount ++;
    }
    
    DBentry* found_node;
    
    if(nodePtr->getEntry()->getName() == name){
        found_node = nodePtr->getEntry();
    }else if(nodePtr->getEntry()->getName() > name){
        found_node = find_sup(nodePtr->getLeft(), name);
    }else if(nodePtr->getEntry()->getName() < name){
        found_node = find_sup(nodePtr->getRight(), name);
    }
    return found_node;
}

//search for largest key node
TreeNode* TreeDB::findLeftMax_sup(TreeNode* nodePtr, TreeNode* nodePtr_r){
    nodePtr_r = nodePtr->getRight();
    if(nodePtr_r->getRight() == nullptr){
        nodePtr->setRight(nodePtr_r->getLeft());
        nodePtr_r->setLeft(nullptr);
        return nodePtr_r;
    }else{
        findLeftMax_sup(nodePtr->getRight(), nodePtr_r);
    }
}

bool TreeDB::removal_sup(TreeNode* nodePtr, string name){
    if(nodePtr == nullptr){
        return false;
    }else if(nodePtr->getEntry()->getName() == name){
        if(nodePtr->getLeft() == nullptr && nodePtr->getRight() == nullptr){
            delete nodePtr;
            nodePtr = nullptr;
            return true;
        }else if(nodePtr->getLeft() == nullptr){
            TreeNode* tempRight = nodePtr->getRight();
            delete nodePtr;
            nodePtr = tempRight;
            return true;
        }else if(nodePtr->getRight() == nullptr){
            TreeNode* tempLeft = nodePtr->getLeft();
            delete nodePtr;
            nodePtr = tempLeft;
            return true;
        }
    }else{
        TreeNode* leftMax;
        leftMax->setLeft(nodePtr->getLeft());
        leftMax->setRight(nodePtr->getRight());
        
        if(nodePtr->getLeft()->getRight() == nullptr){
            leftMax = nodePtr->getLeft();
            leftMax->setLeft(leftMax->getLeft());
        }else{
            leftMax = findLeftMax_sup(nodePtr->getLeft(), nodePtr);
        }
        leftMax->setLeft(leftMax->getLeft());
        leftMax->setRight(leftMax->getRight());
        
        delete nodePtr;
        nodePtr = leftMax;
        return true;
    }
    
    if(name < nodePtr->getEntry()->getName()){
        nodePtr->setLeft(nodePtr->getLeft());
        return removal_sup(nodePtr->getLeft(), nodePtr, name);
    }else if(name > nodePtr->getEntry()->getName()){
        nodePtr->setRight(nodePtr->getRight());
        return removal_sup(nodePtr->getRight(), nodePtr, name);
    }
}

void TreeDB::clear_sup(TreeNode* head){
    if(head == nullptr){
        return;
    }
    
    clear_sup(head->getLeft());
    head->setLeft(nullptr);
    
    clear_sup(head->getRight());
    head->setRight(nullptr);
    
    delete head;
    head = nullptr;
}

void TreeDB::countActive_sup(TreeNode* head) const{
    int activeNum = 0;
    
    if(head == nullptr){
        return 0;
    }
    
    activeNum += countActive_sup(head->getLeft());
    activeNum += countActive_sup(head->getRight());
    if(head->getEntry()->getActive()){
        activeNum ++;
    }
    
    return activeNum;
}

