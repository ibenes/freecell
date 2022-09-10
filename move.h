#include "card-storage.h"

bool moveLegal(CardStorage *from, CardStorage *to) ;
void move(CardStorage *from, CardStorage *to) ;

using RawMove = std::pair<CardStorage *, CardStorage *>;
using Locations = std::vector<CardStorage *>;
std::vector<RawMove> availableMoves(Locations froms, Locations tos);
