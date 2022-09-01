#include "card.h"

std::map<Color, std::string> color_map{
	{Color::Heart, "h"},
	{Color::Diamond, "d"},
	{Color::Club, "c"},
	{Color::Spade, "s"},
};


std::ostream& operator<< (std::ostream& os, const Card & card) {
	if (card.value <= 10) {
		os << card.value;
	} else if (card.value == 11) {
		os << "J";
	} else if (card.value == 12) {
		os << "Q";
	} else if (card.value == 13) {
		os << "K";
	}
	os << color_map[card.color];
	return os;
}

