#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "card.h"
#include <sstream>

std::string cardRepresentation(const Card &card) {
	std::stringstream ss;
	ss << card;
	return ss.str();
}

TEST_CASE( "Card construction and printing tests", "[basic]" ) {
	REQUIRE(cardRepresentation({Color::Heart, 12}) == "Qh");
}
