#ifndef CARD_H
#define CARD_H


#include <string>
#include <map>
#include <vector>
#include <iostream>

enum class Color {Heart, Diamond, Club, Spade};
enum class RenderColor {Red, Black};

extern const std::vector<Color> colors_list;

extern const std::map<Color, std::string> color_map;

extern const std::map<Color, RenderColor> render_color_map;

inline constexpr int king_value = 13;

struct Card {
	Card(Color col, int val);

	const Color color;
	const int value;
};

bool operator==(const Card &a, const Card &b) ;
bool operator!=(const Card &a, const Card &b) ;
bool operator<(const Card &a, const Card &b) ;

std::ostream& operator<< (std::ostream& os, const Card & card) ;

#endif
