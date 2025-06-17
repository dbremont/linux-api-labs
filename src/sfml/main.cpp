#include <SFML/Graphics.hpp>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Raster Image with SFML");

    // Load a raster image (e.g., PNG, JPEG)
    sf::Texture texture;
    if (!texture.loadFromFile("image.png")) {
        return -1; // Error loading image
    }

    // Create a sprite to display the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Main render loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black); // Clear the screen
        window.draw(sprite);            // Draw the image
        window.display();               // Show the result
    }

    return 0;
}
