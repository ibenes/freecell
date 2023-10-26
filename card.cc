#include "card.h"

#include <cassert>

#ifdef CONSOLE_COLORS
static constexpr auto ansi_reset = "\033[0m";
static constexpr auto ansi_bold = "\033[1m";
static constexpr auto ansi_red = "\033[1;31m";
#endif

const std::map<Color, std::string> color_map{
#ifdef CONSOLE_COLORS
    {Color::Heart, "\u2665"},
    {Color::Diamond, "\u2666"},
    {Color::Club, "\u2663"},
    {Color::Spade, "\u2660"},
#else
    {Color::Heart, "h"},
    {Color::Diamond, "d"},
    {Color::Club, "c"},
    {Color::Spade, "s"},
#endif
};

const std::map<Color, RenderColor> render_color_map{
	{Color::Heart, RenderColor::Red},
	{Color::Diamond, RenderColor::Red},
	{Color::Club, RenderColor::Black},
	{Color::Spade, RenderColor::Black},
};

const std::vector<Color> colors_list {
	Color::Heart,
	Color::Diamond,
	Color::Club,
	Color::Spade,
};

Card::Card(Color col, int val) : color(col), value(val) {
	assert(value >= 1 && value <= king_value);
}

std::ostream& operator<< (std::ostream& os, const Card & card) {
#ifdef CONSOLE_COLORS
    if (render_color_map.at(card.color) == RenderColor::Red) {
        os << ansi_red;
    }
    else {
        os << ansi_bold;
    }
#endif
    if (card.value < 10) {
        os << " " << card.value;
    } else if (card.value == 10) {
        os << "10";
	} else if (card.value == 11) {
        os << " J";
	} else if (card.value == 12) {
        os << " Q";
	} else if (card.value == 13) {
        os << " K";
	}
	os << color_map.at(card.color);    
#ifdef CONSOLE_COLORS
    os << " " << ansi_reset;
#endif
	return os;
}

bool operator==(const Card &a, const Card &b) {
	return a.color == b.color && a.value == b.value;
}

bool operator!=(const Card &a, const Card &b) {
	return !(a == b);
}

bool operator<(const Card &a, const Card &b) {
    return std::tie(a.color, a.value) < std::tie(b.color, b.value);
}
