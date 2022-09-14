#include "catch.hpp"

#include "card.h"
#include "card-storage.h"
#include "move.h"
#include "game.h"

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

std::string workStackRepresentation(const WorkStack &stack) {
	std::stringstream ss;
	ss << stack;
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

	REQUIRE(render_color_map[Card{Color::Spade, 7}.color] == render_color_map[Card{Color::Club, 7}.color]);
	REQUIRE(render_color_map[Card{Color::Spade, 7}.color] != render_color_map[Card{Color::Heart, 7}.color]);
	REQUIRE(render_color_map[Card{Color::Diamond, 7}.color] == render_color_map[Card{Color::Heart, 7}.color]);
}

TEST_CASE("Card equality tests") {
	REQUIRE(Card{Color::Heart, 1} == Card{Color::Heart, 1});
	REQUIRE(Card{Color::Spade, 1} != Card{Color::Heart, 1});
	REQUIRE(Card{Color::Heart, 2} != Card{Color::Heart, 1});
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

TEST_CASE("Work stack operations") {
    WorkStack stack;

	REQUIRE(workStackRepresentation(stack) == "_");
	REQUIRE_FALSE(stack.topCard().has_value());
	REQUIRE_FALSE(stack.getCard().has_value());
	REQUIRE(workStackRepresentation(stack) == "_");

	REQUIRE(stack.acceptCard({Color::Heart, 3}));
	REQUIRE(workStackRepresentation(stack) == "3h");
	REQUIRE(cardRepresentation(*stack.topCard()) == "3h");

	REQUIRE_FALSE(stack.acceptCard({Color::Heart, 3}));
	REQUIRE_FALSE(stack.acceptCard({Color::Heart, 2}));
	REQUIRE_FALSE(stack.acceptCard({Color::Spade, 3}));
	REQUIRE_FALSE(stack.acceptCard({Color::Spade, 4}));

	REQUIRE(stack.acceptCard({Color::Spade, 2}));
	REQUIRE(workStackRepresentation(stack) == "3h 2s");

	REQUIRE_FALSE(stack.acceptCard({Color::Heart, 3}));
	REQUIRE_FALSE(stack.acceptCard({Color::Heart, 2}));
	REQUIRE_FALSE(stack.acceptCard({Color::Club, 1}));

	REQUIRE(stack.acceptCard({Color::Diamond, 1}));
	REQUIRE(workStackRepresentation(stack) == "3h 2s 1d");
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

TEST_CASE("Moves from work stack") {
    WorkStack stack;
    HomeDestination home_heart;
    FreeCell free_cell;

	REQUIRE_FALSE(moveLegal(&stack, &home_heart));
	move(&stack, &home_heart);
	REQUIRE(homeRepresentation(home_heart) == "_");

	REQUIRE_FALSE(moveLegal(&stack, &free_cell));
	move(&stack, &free_cell);
	REQUIRE(freeCellRepresentation(free_cell) == "_");

    stack.acceptCard({Color::Spade, 5});
	REQUIRE(moveLegal(&stack, &free_cell));
	move(&stack, &free_cell);
	REQUIRE(freeCellRepresentation(free_cell) == "5s");
	REQUIRE(workStackRepresentation(stack) == "_");

    stack.acceptCard({Color::Heart, 5});
    stack.acceptCard({Color::Spade, 4});
    stack.acceptCard({Color::Heart, 3});
    stack.acceptCard({Color::Club, 2});
    stack.acceptCard({Color::Heart, 1});
	REQUIRE(workStackRepresentation(stack) == "5h 4s 3h 2c 1h");

	REQUIRE(moveLegal(&stack, &home_heart));
	move(&stack, &home_heart);
	REQUIRE(workStackRepresentation(stack) == "5h 4s 3h 2c");
	REQUIRE(homeRepresentation(home_heart) == "1h");

	REQUIRE_FALSE(moveLegal(&stack, &home_heart));
	move(&stack, &home_heart);
	REQUIRE(workStackRepresentation(stack) == "5h 4s 3h 2c");
	REQUIRE(homeRepresentation(home_heart) == "1h");

    free_cell.getCard();
	REQUIRE(moveLegal(&stack, &free_cell));
	move(&stack, &free_cell);
	REQUIRE(workStackRepresentation(stack) == "5h 4s 3h");
	REQUIRE(freeCellRepresentation(free_cell) == "2c");

    home_heart.acceptCard({Color::Heart, 2});
	REQUIRE(moveLegal(&stack, &home_heart));
	move(&stack, &home_heart);
	REQUIRE(workStackRepresentation(stack) == "5h 4s");
	REQUIRE(homeRepresentation(home_heart) == "3h");
}

TEST_CASE("Moves to work stack") {
    WorkStack stack;
    FreeCell fc_1, fc_2;

	REQUIRE_FALSE(moveLegal(&fc_1, &stack));
	move(&fc_1, &stack);
	REQUIRE(workStackRepresentation(stack) == "_");
	REQUIRE(freeCellRepresentation(fc_1) == "_");

    fc_1.acceptCard({Color::Club, 10});
    fc_2.acceptCard({Color::Diamond, 9});
	REQUIRE(moveLegal(&fc_1, &stack));
	move(&fc_1, &stack);
	REQUIRE(moveLegal(&fc_2, &stack));
	move(&fc_2, &stack);
	REQUIRE(workStackRepresentation(stack) == "10c 9d");
	REQUIRE(freeCellRepresentation(fc_1) == "_");
	REQUIRE(freeCellRepresentation(fc_2) == "_");

    fc_1.acceptCard({Color::Club, 9});
    fc_2.acceptCard({Color::Diamond, 8});
	REQUIRE_FALSE(moveLegal(&fc_1, &stack));
	move(&fc_1, &stack);
	REQUIRE_FALSE(moveLegal(&fc_2, &stack));
	move(&fc_2, &stack);
	REQUIRE(workStackRepresentation(stack) == "10c 9d");
	REQUIRE(freeCellRepresentation(fc_1) == "9c");
	REQUIRE(freeCellRepresentation(fc_2) == "8d");
}

TEST_CASE("Move discovery") {
    WorkStack stack;
    FreeCell fc_1, fc_2;

    stack.acceptCard({Color::Heart, 7});
    REQUIRE(availableMoves({&stack}, {&fc_1}) == std::vector<RawMove>{{&stack, &fc_1}});
    REQUIRE(availableMoves({&stack}, {&fc_2}) == std::vector<RawMove>{{&stack, &fc_2}});

    REQUIRE(availableMoves({&fc_1}, {&fc_2}) == std::vector<RawMove>{});
    REQUIRE(availableMoves({}, {&fc_1}) == std::vector<RawMove>{});
    REQUIRE(availableMoves({&stack}, {}) == std::vector<RawMove>{});

    fc_2.acceptCard({Color::Spade, 6});
    REQUIRE(
        availableMoves({&stack, &fc_2}, {&fc_1}) ==
        std::vector<RawMove>{
            {&stack, &fc_1},
            {&fc_2, &fc_1},
        });
    REQUIRE(
        availableMoves({&stack, &fc_2}, {&fc_1, &stack}) ==
        std::vector<RawMove>{
            {&stack, &fc_1},
            {&fc_2, &fc_1},
            {&fc_2, &stack},
        });
}

TEST_CASE("Top cards discovery") {
    GameState gs;

    gs.stacks[0].acceptCard({Color::Heart, 7});
    gs.stacks[0].acceptCard({Color::Spade, 6});
    gs.stacks[1].acceptCard({Color::Heart, 6});
    gs.stacks[2].acceptCard({Color::Club, 6});

    gs.free_cells[3].acceptCard({Color::Diamond, 1});

    gs.homes[0].acceptCard({Color::Heart, 1});
    gs.homes[0].acceptCard({Color::Heart, 2});
    gs.homes[2].acceptCard({Color::Club, 1});

    REQUIRE(topCards(gs) == std::vector<Card>{
        {Color::Diamond, 1},
        {Color::Spade, 6},
        {Color::Heart, 6},
        {Color::Club, 6},
    });
}

TEST_CASE("Finding home for card") {
    GameState gs;

    gs.homes[0].acceptCard({Color::Heart, 1});
    gs.homes[0].acceptCard({Color::Heart, 2});
    gs.homes[2].acceptCard({Color::Club, 1});

    REQUIRE(findHomeFor(gs, {Color::Club, 2}) == gs.homes.begin()+2);
    REQUIRE(findHomeFor(gs, {Color::Diamond, 2}) == gs.homes.end());
    REQUIRE(findHomeFor(gs, {Color::Diamond, 1}) == gs.homes.begin()+1);
    REQUIRE(findHomeFor(gs, {Color::Diamond, 1}) == gs.homes.begin()+1);
    REQUIRE(findHomeFor(gs, {Color::Spade, 1}) == gs.homes.begin()+1);
    REQUIRE(findHomeFor(gs, {Color::Heart, 3}) == gs.homes.begin()+0);
}


TEST_CASE("Safe moving of aces") {
    GameState gs;

    gs.stacks[0].acceptCard({Color::Spade, 1});
    gs.stacks[1].acceptCard({Color::Spade, 6});
    gs.stacks[1].acceptCard({Color::Heart, 3});

    gs.free_cells[0].acceptCard({Color::Club, 3});
    gs.free_cells[1].acceptCard({Color::Club, 1});

    gs.homes[0].acceptCard({Color::Heart, 1});
    gs.homes[1].acceptCard({Color::Diamond, 1});

    REQUIRE(safeHomeMoves(gs) == std::vector<RawMove>{
        {&gs.free_cells[1], &gs.homes[2]},
        {&gs.stacks[0], &gs.homes[2]},
    });
}
