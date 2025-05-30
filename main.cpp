#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
//#include<imgui.h>
//#include <imgui-sfml/imgui-SFML.h>
using namespace std;

sf::Font arial("arial.ttf");
float ybelow(float bally, float waterline) {
    if (bally - waterline >= 0) {
        return bally-waterline;
    }
    return 0.0;
}
float integratecircle(float r, float h) {
    return(pow(r,2)*acos((h-r)/r)+ (r - h)*sqrt(2*h*r - pow(h, 2)));
}
float getareaofcircle (float radius, float ybelow) {
    float x1 = sqrt(pow(radius, 2)- pow(ybelow, 2));
    float x2 = -x1;
    //integrate x2, subtract that from integral of x1;
    // r^2 = y^2 + x^2
    //integrate (y = root(900-x^2)) -> i got -1/3 *(r^2 - x^2)^3/2
    return integratecircle(radius, x2) - integratecircle(radius, x1);
}
int main() {
    //Variables
    unsigned int width = 700;
    unsigned int height = 500;
    //int x = 0;
    float ballx = width/2 - 70;
    float bally = 200;
    float ballradius = 30;
    //water
    int waterline = 300;
    float waterx = 300.f;
    float watery = 0.f;
    float densitywater = 1;
    float gravity = 9.81;
    float buoyancyForce = getareaofcircle(ballradius, 0) * densitywater* gravity;
    float area;
    float ballarea = M_PI*pow(ballradius, 2);
    ///////////////////////////////////////////////////////////////
    sf::RenderWindow window(sf::VideoMode({width, height}), "Simple Buoyancy Simulator (First SFML Project)");

    sf::CircleShape ball(ballradius);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition({ballx, bally});

    sf::RectangleShape water({float(700), float(600)});
    water.setFillColor(sf::Color::Blue);
    water.setPosition({0.0, float(waterline)});
    sf::Text text(arial, to_string(getareaofcircle(ballradius, ybelow(bally, waterline))));
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    text.setPosition({10, 10});

    //////////////////////////////////////////////////////////////////
    while (window.isOpen()) {
        if (bally + ballradius < waterline) {
            text.setString("Submerged area: " + to_string(0) +
                           "\nBall Y: " + to_string(bally) +
                           "\nControls: W/S to move ball");
        } else  if (bally - ballradius > waterline) {
            text.setString("Submerged area: " + to_string(M_PI*pow(ballradius, 2)) +
                           "\nBall Y: " + to_string(bally) +
                           "\nControls: W/S to move ball");
        } else {
            text.setString("Submerged area: " + to_string(ballarea - integratecircle(ballradius, (bally + ballradius) + waterline)) +
                           "\nBall Y: " + to_string(bally) +
                           "\nControls: W/S to move ball");
        }

        if (auto event = window.pollEvent()) {
            if (event-> is<sf::Event::Closed>()) {
                window.close();
            }
            //std::cout<<x<<endl;
            //x++;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            bally += 0.3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            bally -=0.3;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            cout<<getareaofcircle(ballradius, ybelow(bally, waterline))<<endl;
        }

        window.clear();
        window.draw(water);
        ball.setPosition({ballx, bally});
        window.draw(ball);
        window.draw(text);
        window.display();


    }
}


