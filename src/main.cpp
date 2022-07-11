#include <SFML/Graphics.hpp>
#include <iostream>

#include "main.h"

// Global Definitions-
int numberArray[1000] = {};
int numberArrayIndexSize = *(&numberArray + 1) - numberArray; // Retrieve the size of numberArray
int randomNumberRange = 1000;

// SFML Definitions
int windowSizeX = 1000;
int windowSizeY = 1000;
sf::RenderWindow window(sf::VideoMode(windowSizeX, windowSizeY), "Bubble Sort Algorithm Visualization");
// Create view and invert windowSizeY so the visualizer starts from the bottom left.
sf::View view(sf::FloatRect(0.0f, windowSizeY, windowSizeX, -windowSizeY));
float sleeperDelay = 0.0f; // 1000.0f = 1 second, 0.0f is disabled.

int main()
{
    // Program will initialize(), then sort() -> render() -> sf::sleep() -> back to sorting.
    // 
    // sort() :
    // Sort the array in 1 step at a time using bubble sorting algorithm.
    // 
    // render() :
    // Render all the values of the array through SFML.
    // 
    // sf::sleep() :
    // Pause before sorting again or else you can't see it doing cool sorting logic.

    // Setup stuff such as randomizing the array.
    initialize();

    // SFML Window
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}

void initialize()
{
    std::cout << std::endl << "Initialize... \n";

    // Randomise numbers to fill numberArray[]
    srand(time(NULL)); // Generate random seed for rand() based on time
    std::cout << "unsorted array : \n";
    for (int i = 0; i < numberArrayIndexSize; i++)
    {
        // Random number between 0 and 99
        numberArray[i] = rand() % randomNumberRange;

        std::cout << numberArray[i] << "\t";
    }

    window.setView(view);

    std::cout << std::endl << "Setup done. \n";
    sort();
}

void sort()
{
    std::cout << std::endl << "Sorting... \n";

    // Definitions
    int temp;
    int i, j;
    bool final = false;

    // Sort the array numberArray[]
    for (i = 0; i < numberArrayIndexSize; i++)
    {
        for (j = i + 1; j < numberArrayIndexSize; j++)
        {
            if (numberArray[j] < numberArray[i])
            {
                temp = numberArray[i];
                numberArray[i] = numberArray[j];
                numberArray[j] = temp;
            }
        }
        render(final);

        std::cout << std::endl << "Pausing... \n";
        // Set the program to sleep
        sf::sleep(sf::milliseconds(sleeperDelay));
    }
    final = true;
    render(final);
}

void render(bool final)
{
    int width = windowSizeX / numberArrayIndexSize;
    int height = windowSizeY / randomNumberRange;

    window.clear();

    for (int i = 0; i < numberArrayIndexSize; i++)
    {
        int barheight = height * numberArray[i];

        // Create rectangle Bar with dimensions 10x25
        sf::RectangleShape bar(sf::Vector2f(width, barheight));
        bar.setFillColor(sf::Color::White);
        if (final)
        {
            bar.setFillColor(sf::Color::Green);
        }
        // Setting offset
        bar.setPosition(i * width, 0);
        // Drawing the current bar
        window.draw(bar);
    }

    std::cout << std::endl << "Rendering... \n";
    window.display();
}