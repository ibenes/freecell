#include "card.h"

std::map<Color, std::string> color_map{
	{Color::Heart, "h"},
	{Color::Diamond, "d"},
	{Color::Club, "c"},
	{Color::Spade, "s"},
};

std::map<Color, RenderColor> render_color_map{
	{Color::Heart, RenderColor::Red},
	{Color::Diamond, RenderColor::Red},
	{Color::Club, RenderColor::Black},
	{Color::Spade, RenderColor::Black},
};

std::vector<Color> colors_list {
	Color::Heart,
	Color::Diamond,
	Color::Club,
	Color::Spade,
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

bool operator==(const Card &a, const Card &b) {
	return a.color == b.color && a.value == b.value;
}

bool operator!=(const Card &a, const Card &b) {
	return !(a == b);
}
