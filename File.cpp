#include "File.h"

File::File(const std::string& _filename) : filename(_filename) {
    file.open(filename);
    open_write_check(file);
    file.close();
};

void File::open_write_check(const std::ofstream& file) {
    try {
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file for writing!");
        }
    }
    catch (const std::exception& e) {
        sf::RenderWindow errorWindow(sf::VideoMode(400, 200), "Error");

        Label errorLabel(50, 50, e.what());
        errorLabel.setFontSize(24);
        errorLabel.setColor(sf::Color::Red);

        while (errorWindow.isOpen()) {
            sf::Event event;
            while (errorWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    errorWindow.close();
                }
            }

            errorWindow.clear(sf::Color::White);
            errorWindow.draw(errorLabel.displayText());
            errorWindow.display();
        }
        exit(errno);
    }
}

void File::write(const vector<int>& queens, const string& about) {
    file.open(filename, std::ios::app);
    file << about << endl;
    for (int i = 0; i < QUEENS_SIZE; i++) {
        for (int j = 0; j < QUEENS_SIZE; j++) {
            if (queens[i] == j) {
                file << 1 << " ";
            }
            else {
                file << 0 << " ";
            }
        }
        file << endl;
    }
    file.close();
}
