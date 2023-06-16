#pragma once
#include "constants.h"
#include "Button.h"
#include "A_star.h"
#include "RBFS.h"
#include "File.h"
#include <chrono>
#include <thread>

using namespace constants;

class Interface {
    RenderWindow window;
    Button random_generation;
    Button A_star_button;
    Button RBFS_button;
    Label roots;
    Texture boardTexture;
    Image queenImage;
    Texture queenTexture;
    Texture menuTexture;
    Sprite menuSprite;
    Sprite buttonSprite;
    Sprite A_star_Sprite;
    Sprite RBFSSprite;
    Sprite boardSprite;
    Sprite Roots_Sprite;
    Texture buttonTexture;
    Texture buttonTexture2;
    Sprite queenses[8];
    // Helper method to check if an image is loaded into a texture.
    void checkloadingImage(Texture&, Image);

    // Helper method to check if an image is loaded from a file.
    void checkloadingImage(Image&, string);

    // Helper method to check if a file is loaded into a texture.
    void checkloadingFile(Texture&, string);

    // Handles exceptions by displaying appropriate error messages.
    void handleException(const exception&) const;

    // Resizes the graphical objects in the interface.
    void resizeObjects();
public:
    // Constructor for the Interface class.
    Interface();

    // Sets the initial state of the interface using a vector of integers.
    void setInitial(vector<int>&) const;

    // Executes the main program loop and handles user interactions using a File object.
    void run(File&);

    // Draws the roots (labels) on the interface.
    void drawRoots();

    // Draws the queens on the interface.
    void drawQueens();

    // Draws the interface elements based on boolean parameters and an optional flag.
    void draw(bool, bool flag2 = false);

    // Runs the RBFS (Recursive Best-First Search) algorithm using a vector of integers, a File object, and a BoardStateBase object.
    void runRBFSAlgorithm(vector<int>&, File&, BoardStateBase&);

    // Runs the A* algorithm using a vector of integers, a File object, and a BoardStateBase object.
    void runAStarAlgorithm(vector<int>&, File&, BoardStateBase&);

    // Generates a random arrangement of queens on the chessboard using a vector of integers.
    void generateRandomQueens(vector<int>&);

    // Replaces queens on the chessboard using a vector of integers, a Vector2i object, and a BoardStateBase object.
    void ReplaceQueens(vector<int>&, Vector2i, BoardStateBase&);
};