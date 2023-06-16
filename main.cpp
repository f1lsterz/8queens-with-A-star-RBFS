#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Interface.h"

int main() {
    File my_file("result.txt");
    Interface main_interface;
    main_interface.run(my_file);
}
