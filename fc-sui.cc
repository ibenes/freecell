#include "card.h"
#include "home-destination.h"

#include <iostream>


int main() {
	std::cout << "Hello world!\n";
	Card c{Color::Heart, 2};
	Card d{Color::Heart, 12};
	std::cout << "Hello " << c << "!\n";
	std::cout << "Hello " << d << "!\n";

    HomeDestination home_heart;
    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 3));
    std::cout << home_heart << "\n";

    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 1));
    std::cout << home_heart << "\n";
    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 2));
    std::cout << home_heart << "\n";

    home_heart.acceptCard(std::make_unique<Card>(Color::Spade, 3));
    std::cout << home_heart << "\n";
    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 4));
    std::cout << home_heart << "\n";

    home_heart.acceptCard(std::make_unique<Card>(Color::Heart, 3));
    std::cout << home_heart << "\n";
}
