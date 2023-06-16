#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "constants.h"

using namespace constants;
using namespace std;

class File {
    string filename; // Stores the name of the file
    ofstream file; // ofstream object for file operations

    // Private helper method to check if the ofstream object is open for writing
    void open_write_check(const ofstream&);

public:
    // Constructor that initializes the File object with the provided filename
    File(const string&);

    // Method to write the contents of the vector to the file with the specified text
    void write(const vector<int>&, const string&);
};