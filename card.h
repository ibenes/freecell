#ifndef CARD_H
#define CARD_H


#include <string>
#include <map>
#include <iostream>

enum class Color {Heart, Diamond, Club, Spade};
enum class RenderColor {Red, Black};

extern std::map<Color, std::string> color_map;

extern std::map<Color, RenderColor> render_color_map;

struct Card {
	const Color color;
	const int value;
};

bool operator== (const Card &a, const Card &b) ;
bool operator!= (const Card &a, const Card &b) ;

std::ostream& operator<< (std::ostream& os, const Card & card) ;

#endif
