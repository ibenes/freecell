#include "catch.hpp"

#include "card.h"
#include "card-storage.h"
#include "move.h"

#include <sstream>

std::string cardRepresentation(const Card &card) {
	std::stringstream ss;
	ss << card;
	return ss.str();
}

std::string freeCellRepresentation(const FreeCell &fc) {
	std::stringstream ss;
	ss << fc;
	return ss.str();
}

std::string homeRepresentation(const HomeDestination &home) {
	std::stringstream ss;
	ss << home;
	return ss.str();
}

TEST_CASE("Card construction and printing tests") {
	REQUIRE(cardRepresentation({Color::Heart, 1}) == "1h");
	REQUIRE(cardRepresentation({Color::Heart, 2}) == "2h");
	REQUIRE(cardRepresentation({Color::Heart, 3}) == "3h");
	REQUIRE(cardRepresentation({Color::Heart, 4}) == "4h");
	REQUIRE(cardRepresentation({Color::Heart, 5}) == "5h");
	REQUIRE(cardRepresentation({Color::Heart, 6}) == "6h");
	REQUIRE(cardRepresentation({Color::Heart, 7}) == "7h");
	REQUIRE(cardRepresentation({Color::Heart, 8}) == "8h");
	REQUIRE(cardRepresentation({Color::Heart, 9}) == "9h");
	REQUIRE(cardRepresentation({Color::Heart, 10}) == "10h");
	REQUIRE(cardRepresentation({Color::Heart, 11}) == "Jh");
	REQUIRE(cardRepresentation({Color::Heart, 12}) == "Qh");
	REQUIRE(cardRepresentation({Color::Heart, 13}) == "Kh");

	REQUIRE(cardRepresentation({Color::Diamond, 7}) == "7d");
	REQUIRE(cardRepresentation({Color::Club, 7}) == "7c");
	REQUIRE(cardRepresentation({Color::Spade, 7}) == "7s");
}

TEST_CASE("FreeCell operations") {
    FreeCell free_cell;
	REQUIRE(freeCellRepresentation(free_cell) == "_");

	REQUIRE_FALSE(free_cell.topCard().has_value());
	REQUIRE_FALSE(free_cell.getCard().has_value());

	Card c{Color::Heart, 1};
	REQUIRE(free_cell.canAccept(c));
	REQUIRE(free_cell.acceptCard(c));

	REQUIRE(freeCellRepresentation(free_cell) == "1h");
	REQUIRE(cardRepresentation(*free_cell.topCard()) == "1h");
	REQUIRE(cardRepresentation(*free_cell.getCard()) == "1h");

	REQUIRE(freeCellRepresentation(free_cell) == "_");
}

TEST_CASE("Home destiation operations") {
    HomeDestination home_heart;

	REQUIRE(homeRepresentation(home_heart) == "_");

	REQUIRE_FALSE(home_heart.acceptCard({Color::Heart, 3}));
	REQUIRE(homeRepresentation(home_heart) == "_");

	REQUIRE(home_heart.acceptCard({Color::Heart, 1}));
	REQUIRE(homeRepresentation(home_heart) == "1h");

	REQUIRE(home_heart.acceptCard({Color::Heart, 2}));
	REQUIRE(homeRepresentation(home_heart) == "2h");

	REQUIRE_FALSE(home_heart.acceptCard({Color::Spade, 3}));
	REQUIRE(homeRepresentation(home_heart) == "2h");

	REQUIRE_FALSE(home_heart.acceptCard({Color::Heart, 4}));
	REQUIRE(homeRepresentation(home_heart) == "2h");

	REQUIRE(home_heart.acceptCard({Color::Heart, 3}));
	REQUIRE(homeRepresentation(home_heart) == "3h");
}

TEST_CASE("Moves to home destination") {
    HomeDestination home_heart;
    FreeCell free_cell;

	REQUIRE_FALSE(moveLegal(&free_cell, &home_heart));
	move(&free_cell, &home_heart);
	REQUIRE(homeRepresentation(home_heart) == "_");

    free_cell.acceptCard({Color::Heart, 4});

	REQUIRE_FALSE(moveLegal(&free_cell, &home_heart));
	move(&free_cell, &home_heart);
	REQUIRE(homeRepresentation(home_heart) == "_");

    free_cell.getCard();
    free_cell.acceptCard({Color::Heart, 1});
	REQUIRE(moveLegal(&free_cell, &home_heart));
	move(&free_cell, &home_heart);
	REQUIRE(homeRepresentation(home_heart) == "1h");
}
