#include <SFML/Graphics.hpp>

#include <chrono>
#include <iostream>

int main() {
  int length = 200;
  int width = 300;

  sf::RenderWindow window(sf::VideoMode(width, length), "SFML works!");

  sf::Vector2f max(2859.0,7261.02);
  std::vector<sf::Vertex> line = {
    sf::Vertex(sf::Vector2f(0,0)),
    sf::Vertex(max),
    sf::Vertex(sf::Vector2f(0,max.y)),
    sf::Vertex(sf::Vector2f(0,0)),
    sf::Vertex(sf::Vector2f(max.x,0.0)),
    sf::Vertex(max)
  };

  sf::View view(sf::Rect<float>(sf::Vector2f(-100.0, -100.0), sf::Vector2f(max.x + 200.0, max.y + 200.0)));

  size_t open_count = 0;

  auto start = std::chrono::high_resolution_clock::now();

  while (window.isOpen()) {

    open_count += 1;

    sf::Event event;
    while (window.pollEvent(event)) {

      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::Resized:
        case sf::Event::LostFocus:
        case sf::Event::GainedFocus:
        case sf::Event::TextEntered:
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
        case sf::Event::MouseWheelMoved:
        case sf::Event::MouseWheelScrolled:
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseMoved:
        case sf::Event::MouseEntered:
        case sf::Event::MouseLeft:
        case sf::Event::JoystickButtonPressed:
        case sf::Event::JoystickButtonReleased:
        case sf::Event::JoystickMoved:
        case sf::Event::JoystickConnected:
        case sf::Event::JoystickDisconnected:
        case sf::Event::TouchBegan:
        case sf::Event::TouchMoved:
        case sf::Event::TouchEnded:
        case sf::Event::SensorChanged:
        default:
          std::cerr << static_cast<int>(event.type) << "\n";
      }
      if (event.type == sf::Event::Closed) {
        window.close();
      } // if (event.type == sf::Event::Closed)

    } // while (window.pollEvent(event))

    window.clear();
    window.setView(view);
    window.draw(line.data(), line.size(), sf::LineStrip);
    
    window.display();
  } // while (window.isOpen())

  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> delta = stop - start;
  std::cout << "Open: " << open_count << ", Duration: " << delta.count() << ", FPS: " << open_count / delta.count() << std::endl;

  return 0;
}
