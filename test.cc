#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "card.h"
#include <sstream>

TEST_CASE( "Basic tests", "[basic]" ) {
	Card d{Color::Heart, 12};
	std::stringstream ss;
	ss << d;
	REQUIRE(ss.str() == "Qh");
}
