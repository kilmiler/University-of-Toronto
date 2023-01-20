//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of helper functions you write here

//helper functions:
void maxShapes(stringstream &line);
void create(stringstream &line);
void move(stringstream &line);
void rotate(stringstream &line);
void draw(stringstream &line);
void delete_List(stringstream &line);

int search_Shape(string name);
bool reserved_type(string name);
bool reserved_word(string name);
bool allowed_type(string type);
bool allowed_value(int value);
bool allowed_rotation(int angle);
bool min_argument(stringstream &line);


//error functions:
void invalid_command();
void invalid_arg();
void invalid_name();
void shape_exists(string name);
void shape_notfound(string name);
void invalid_type();
void invalid_value();
void arguments_many();
void arguments_less();
void array_full();



int main() {

    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);   // Get a line from standard input
    

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream (line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        int check;
        
        bool TorF_Command = false;
        for(int i=0; i<7; i++){
            if(command == keyWordsList[i]){
                check = i;
                TorF_Command = true;
                break; //stops at i and puts it in check
            }
        }
        
        if(TorF_Command){
            switch(check){
                case 1: maxShapes(lineStream);
                    break;
                case 2: create(lineStream);
                    break;
                case 3: move(lineStream);
                    break;
                case 4: rotate(lineStream);
                    break;
                case 5: draw(lineStream);
                    break;
                case 6: delete_List(lineStream);
                    break;
                //DO I NEED DEFAULT?
            }
        }else{
            invalid_command();
        }
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
        
    }  // End input loop until EOF.
    
    return 0;
}




//helper functions:
void maxShapes(stringstream &line){
    string extra;
    
    line >> max_shapes;
    if(line.fail()){
        if(line.eof()){
            arguments_less();
            return;
        }else{
            invalid_arg();
            return;
        }
    }
    
    line >> extra;
    if(!line.fail()){
        arguments_many();
        return;
    }
    
    shapesArray = new shape*[max_shapes];
    cout << "New database: max shapes is " << max_shapes << endl;
}

void create(stringstream &line){
    string name, type;
    string extra;
    int x_location, y_location, x_size, y_size, location;
    
    //NAME
    line >> name;
    //check for arguments less
    if(line.fail()){
        arguments_less();
        return;
    }
    
    // check for reserved types
    if(reserved_type(name)){
        invalid_name();
        return;
    }
    
    // check if name is one of keywords
    if(reserved_word(name)){
        invalid_name();
        return;
    }
    
    
    // check location
    location = search_Shape(name); //would have value of -9 if empty and does not already exist
    if(location >= 0){
        shape_exists(name);
        return;
    }
    
    //TYPE
    line >> type;
    //check for arguments less
    if(line.fail()){
        arguments_less();
        return;
    }
    
    //check if type is one of the following
    if(allowed_type(type)){
        invalid_type();
        return;
    }
    
    
    //X position
    line >> x_location;
    if(allowed_value(x_location)){
        invalid_value();
        return;
    }
    
    if(line.fail()){
        invalid_arg();
        return;
    }
    
    if(min_argument(line)){
        return;
    }
    
    //Y position
    line >> y_location;
    if(allowed_value(y_location)){
        invalid_value();
        return;
    }
    
    if(line.fail()){
        invalid_arg();
        return;
    }
    
    if(min_argument(line)){
        return;
    }
    
    //X size
    line >> x_size;
    if(allowed_value(x_size)){
        invalid_value();
        return;
    }
    
    if(line.fail()){
        invalid_arg();
        return;
    }
    
    if(min_argument(line)){
        return;
    }
    
    //Y size
    line >> y_size;
    if(allowed_value(y_size)){
        invalid_value();
        return;
    }
    
    if(line.fail()){
        invalid_arg();
        return;
    }
    
    if(min_argument(line)){
        return;
    }
    
    //Check full Array
    if(shapeCount >= max_shapes){
        array_full();
        return;
    }
    
    //Check for Extra commands
    line >> extra;
    if(!line.fail()){
        arguments_many();
        return;
    }
    
    
    //Creating New Shape
    shapesArray[shapeCount] = new shape(name, type, x_location, y_location, x_size, y_size);
    cout << "Created " << name << ": " << type << " " << x_location << " " << y_location << " " << x_size << " " << y_size << endl;
    shapeCount = shapeCount + 1;
}

void move(stringstream &line){
    string name;
    string extra;
    int x_location, y_location, location;
    
    //NAME
    line >> name;
    if(line.fail()){
        invalid_arg();
        return;
    }
    
    if(line.eof()){
        arguments_less();
        return;
    }
    
    if(reserved_type(name)){
        invalid_name();
        return;
    }
    
    if(reserved_word(name)){
        invalid_name();
        return;
    }
    
    location = search_Shape(name); // SETS the location for this shape
    if(location<0){
        shape_notfound(name);
        return;
    }
    
    //X position
    line >> x_location;
    if(allowed_value(x_location)){
        invalid_value();
        return;
    }
    
    if(line.fail()){
        invalid_arg();
        return;
    }
    
    if(min_argument(line)){
        return;
    }
    
    //Y position
    line >> y_location;
    if(allowed_value(y_location)){
        invalid_value();
        return;
    }
    
    if(line.fail()){
        invalid_arg();
        return;
    }
    
    if(min_argument(line)){
        return;
    }
    
    //Check for Extra commands
    line >> extra;
    if(!line.fail()){
        arguments_many();
        return;
    }
    
    
    //Moving position of shape
    shapesArray[location]->setXlocation(x_location);
    shapesArray[location]->setYlocation(y_location);
    cout << "Moved " << name << " to " << x_location << " " << y_location << endl;
}

void rotate(stringstream &line){
    string name;
    string extra;
    int angle, location;
    
    //NAME
    line >> name;
    if(line.fail()){
        arguments_less();
        return;
    }
       
    if(reserved_type(name)){
        invalid_name();
        return;
    }
    
    if(reserved_word(name)){
        invalid_name();
        return;
    }
       
    location = search_Shape(name); // SETS the location for this shape
    if(location<0){
        shape_notfound(name);
        return;
    }
    
    //ANGLE
    line >> angle;
    if(min_argument(line)){
        return;
    }
    
    if(allowed_rotation(angle)){
        return;
    }
    
    //Check for Extra commands
    line >> extra;
    if(!line.fail()){
        arguments_many();
        return;
    }
    
    shapesArray[location]->setRotate(angle);
    cout << "Rotated " << name << " by " << angle << " degrees" << endl;
}

void draw(stringstream &line){
    string command;
    string extra;
    int location;
    
    line >> command;
    if(line.fail()){
        arguments_less();
        return;
    }
    
    line >> extra;
    if(!line.fail()){
        arguments_many();
        return;
    }
    
    //if "all"
    if(command == keyWordsList[0]){
        cout << "Drew all shapes" << endl;
        for(int j=0; j<shapeCount; j++){
            if(shapesArray[j] != NULL){
                shapesArray[j]->draw();
            }
        }
    }else{
        location = search_Shape(command);
        if(location < 0){
            shape_notfound(command);
            return;
        }
        
        cout << "Drew " << shapesArray[location]->getName() << endl;
        shapesArray[location]->draw();
    }
}
//delete my1
void delete_List(stringstream &line){
    string name;
    string extra;
    int location;
    
    line >> name;
    if(line.fail()){
        arguments_less();
        return;
    }
    
    line >> extra;
    if(!line.fail()){
        arguments_many();
        return;
    }
    
    
    //if "all"
    if(name == keyWordsList[0]){
        for(int j=0; j<shapeCount; j++){
            if(shapesArray[j] != NULL){
                delete shapesArray[j]; //delete a block of memory
                shapesArray[j] = NULL; //emtpy the memory
            }
        }
        cout << "Deleted: all shapes" << endl;
        return;
    }else{
        location = search_Shape(name);
        if(location < 0){
            shape_notfound(name);
            return;
        }
        else{
            cout << "Deleted shape " << shapesArray[location]->getName() << endl;
            delete shapesArray[location];
            shapesArray[location] = NULL;
            return;
        } return;
    }
}


//error message functions:
void invalid_command(){
    cout << "Error: invalid command" << endl;
}

void invalid_arg(){
    cout << "Error: invalid argument" << endl;
}

void invalid_name(){
    cout << "Error: invalid shape name" << endl;
}

void shape_exists(string name){
    cout << "Error: shape " << name << " exists" << endl;
}

void shape_notfound(string name){
    cout << "Error: shape " << name << " not found" << endl;
}

void invalid_type(){
    cout << "Error: invalid shape type" << endl;
}

void invalid_value(){
    cout << "Error: invalid value" << endl;
}

void arguments_many(){
    cout << "Error: too many arguments" << endl;
}

void arguments_less(){
    cout << "Error: too few arguments" << endl;
}

void array_full(){
    cout << "Error: shape array is full" << endl;
}


//helper functions for checking errors

int search_Shape(string name){
    int i=0;
    for(i=0; i<shapeCount; i++){
        if(shapesArray[i] != NULL){
            if(name == shapesArray[i]->getName()) {
                return i; // if NULL, but name already exists, returns i value (i>=0)
            }
        }
    } return -9; // if NULL, but name does not already exist, returns a - value
}

bool reserved_type(string name){
    for (int i=0; i<3; i++){
        if (name == shapeTypesList[i]){
            return true;
        }
    } return false;
}

bool reserved_word(string name){
    for (int i=0; i<7; i++){
        if (name == keyWordsList[i]){
            return true;
        }
    } return false;
}

bool allowed_type(string type){
    if(type != shapeTypesList[0]){
        if(type != shapeTypesList[1]){
            if(type != shapeTypesList[2]){
                return true;
            }
        }
    }
    return false;
}
    
bool allowed_value(int value){
    if(value <= 0){
        return true;
    }
    return false;
}

bool allowed_rotation(int angle){
    if((angle > 360) || (angle < 0)){
        invalid_value();
        return true;
    } return false;
}

bool min_argument(stringstream &line){
    if(line.fail()){
        if(line.eof()){
            arguments_less();
            return true;
        }else{
            invalid_arg();
            return true;
        }
    } return false;
}


