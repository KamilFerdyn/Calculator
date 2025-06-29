#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>

int main() {
    // Utwórz okno
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kalkulator Kamila Ferdyna");

    sf::Font font;
    if (!font.loadFromFile("/Users/kamilferdyn/CLionProjects/Kalkulator/Arial.ttf")) {
        std::cerr << "Nie można załadować czcionki" << std::endl;
        return 1;
    }

    sf::Text text("0", font, 50);
    text.setFillColor(sf::Color::Black);
    text.setPosition(50, 50);

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> buttonLabels;

    std::string labels[4][4] = {
            {"7", "8", "9", "/"},
            {"4", "5", "6", "*"},
            {"1", "2", "3", "-"},
            {"0", ".", "+", "="}
    };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            sf::RectangleShape button(sf::Vector2f(100, 100));
            button.setFillColor(sf::Color::Blue);
            button.setPosition(50 + j * 110, 150 + i * 110);
            buttons.push_back(button);

            sf::Text label(labels[i][j], font, 50);
            label.setFillColor(sf::Color::White);
            label.setPosition(button.getPosition().x + 30, button.getPosition().y + 10);
            buttonLabels.push_back(label);
        }
    }

    std::string currentInput = "0";
    double previousValue = 0.0;
    char operation = '\0';
    bool newInput = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    for (int i = 0; i < buttons.size(); ++i) {
                        if (buttons[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            std::string label = buttonLabels[i].getString().toAnsiString();
                            std::cout << "Button " << label << " clicked" << std::endl;

                            if (isdigit(label[0]) || label == ".") {
                                if (newInput) {
                                    currentInput = label;
                                    newInput = false;
                                } else {
                                    currentInput += label;
                                }
                                text.setString(currentInput);
                            } else if (label == "C") {
                                currentInput = "0";
                                previousValue = 0.0;
                                operation = '\0';
                                text.setString(currentInput);
                            } else if (label == "=") {
                                double currentValue = std::stod(currentInput);
                                if (operation == '+') {
                                    previousValue += currentValue;
                                } else if (operation == '-') {
                                    previousValue -= currentValue;
                                } else if (operation == '*') {
                                    previousValue *= currentValue;
                                } else if (operation == '/') {
                                    if (currentValue != 0) {
                                        previousValue /= currentValue;
                                    } else {
                                        text.setString("Error");
                                        continue;
                                    }
                                }
                                currentInput = std::to_string(previousValue);
                                text.setString(currentInput);
                                operation = '\0';
                                newInput = true;
                            } else {
                                if (operation == '\0') {
                                    previousValue = std::stod(currentInput);
                                } else {
                                    double currentValue = std::stod(currentInput);
                                    if (operation == '+') {
                                        previousValue += currentValue;
                                    } else if (operation == '-') {
                                        previousValue -= currentValue;
                                    } else if (operation == '*') {
                                        previousValue *= currentValue;
                                    } else if (operation == '/') {
                                        if (currentValue != 0) {
                                            previousValue /= currentValue;
                                        } else {
                                            text.setString("Error");
                                            continue;
                                        }
                                    }
                                    text.setString(std::to_string(previousValue));
                                }
                                operation = label[0];
                                newInput = true;
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        window.draw(text);

        for (auto &button : buttons) {
            window.draw(button);
        }

        for (auto &label : buttonLabels) {
            window.draw(label);
        }

        window.display();
    }

    return 0;
}
