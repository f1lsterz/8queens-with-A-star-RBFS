#pragma once
#include <iostream>

using namespace std;

namespace constants {
	const int QUEENS_SIZE = 8;  // amount of queens
	const double BOARD_SIZE_HEIGHT = 480; // height of chess board
	const double BOARD_SIZE_WIDTH = 680; // 480 - width, 200 - buttons panel
	const double CELL_SIZE = BOARD_SIZE_HEIGHT / QUEENS_SIZE;  // size of one board cell
	const int MAX_RECURSION = 500; // limit of recursions for RBFS
	const double DESIRED_WIDTH = 65; // parametr width for queen`s scale
	const double DESIRED_HEIGHT = 65; // parametr height for queen`s scale
	const double button_xCoordinate = 530; // position x for all buttons
	const double RandGenerate_button_yCoordinate = 45; // position y for first button (random generation)
	const double A_star_button_yCoordinate = 245; // position y for second button (A* algorithm)
	const double RBFS_button_yCoordinate = 345; // position y for third button (RBFS algorithm)
	const double button_width = 100; // width for every button
	const double button_height = 65; // height for every button
	const double roots_xCoordinate = 525; // position x for output amount of roots in algorithms
	const double roots_yCoordinate = 150; // position y for output amount of roots in algorithms
	const double button_xScale = 0.1; // scale x for buttons
	const double button_yScale = 0.2; // scale y for buttons
	const double menu_yScale = 1.2; // scale y for button`s background
	const double menu_xScale = 1; // scale x for button`s background
	const double menu_yPosition = 0; // position y button`s background
	const double menu_xPosition = 480; // position x button`s background
	const double button_sprite_xCoordinate = 520; // position x button`s sprites
	const double RandGenerate_button_sprite_yCoordinate = 25; // position y random generation button sprite
	const double A_star_button_sprite_yCoordinate = 225; // position y A* button sprite
	const double RBFS_button_sprite_yCoordinate = 325; // position y RBFS button sprite
	const double Roots_sprite_yCoordinate = 125; // position y for amount of roots sprite
	const double Roots_xScale = 0.05; // scale x for roots sprite
	const double Roots_yScale = 0.1; // scale y for roots sprite
}