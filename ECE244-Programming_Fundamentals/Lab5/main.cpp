//
//  main.cpp
//  
//
//  Created by Hee Seung Hong on 11/25/19.
//

#include <stdio.h>
#include <iostream>
using namespace std;

#include <string>
#include <sstream>

#include "DBentry.cpp"
#include "TreeNode.cpp"
#include "TreeDB.cpp"

int main(){
    string user_input;
    TreeDB* initial_Node = new TreeDB();
    
    cout >> "> ";
    getline(cin, user_input);
    
    while(!cin.eof()){
        string command;
        stringstream lineStream(user_input);
        lineStream >> command;
        
        //INSERT
        if(command == "insert"){
            string tree_name;
            unsigned int tree_IPaddress;
            bool tree_active;
            string tree_status;
            
            lineStream >> tree_name;
            lineStream >> tree_IPaddress;
            lineStream >> tree_status;
            
            if(tree_status == "active"){
                tree_active = true;
            }else{
                tree_active = false;
            }
            
            DBentry* newEntry = new DBentry(tree_name, tree_IPaddress, tree_active);
            
            if(initial_Node->insert(newEntry)){
                cout << "Success" << endl;
            }else{
                cout << "Error: entry already exists" << endl;
                delete newEntry;
            }
            
        //FIND
        }else if(command == "find"){
            string tree_name;
            
            lineStream >> tree_name;
            
            DBentry* newEntry = initial_Node->find(tree_name);
            
            if(newEntry != nullptr){
                operator<<(cout, *newEntry);
            }else{
                cout << "Error: entry does not exist" << endl;
            }
            
        //REMOVE
        }else if(command == "remove"){
            string tree_name;
            lineStream >> tree_name;
            if(initial_Node->remove(tree_name)){
                cout << "Success" << endl;
            }else{
                cout << "Error: entry does not exist" << endl;
            }
            
        //PRINTALL
        }else if(command == "printall"){
            operator<<(cout, *initial_Node);
            
        //PRINTPROBES
        }else if(command == "printprobes"){
            string tree_name;
            
            lineStream >> tree_name;
            
            DBentry* newEntry = initial_Node->find(tree_name);
            
            if(newEntry != nullptr){
                initial_Node->printProbes();
            }else{
                cout << "Error: entry does not exist" << endl;
            }
            
        //REMOVEALL
        }else if(command == "removeall"){
            initial_Node->clear();
            cout << "Success" << endl;
            
        //COUNTACTIVE
        }else if(command == "countactive"){
            initial_Node->countactive();
            
        //UPDATESTATUS
        }else if(command == "updatestatus"){
            string tree_name;
            bool tree_active;
            string tree_status;

            lineStream >> tree_name;
            lineStream >> tree_status;
            
            DBentry* newEntry = initial_Node->find(tree_name);
            
            if(tree_status == "inactive"){
                tree_active = false;
                newEntry->setActive(tree_active);
                cout << "Success" << endl;
            }else if(tree_status == "active"){
                tree_active = true;
                newEntry->setActive(tree_active);
                cout << "Success" << endl;
            }else{
                cout << "Error: entry does not exist" << endl;
            }
        }
        
        cout << "> ";
        getline(cin, user_input);
    }
    delete initial_Node;
    return 0;
}
