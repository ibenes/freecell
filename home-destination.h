#ifndef HOME_DESTINATION_H
#define HOME_DESTINATION_H

#include "card.h"

#include <string>
#include <memory>
#include <vector>


class HomeDestination {
public:
    bool acceptCard(std::unique_ptr<Card>);
    Card const * top() const;
    friend std::ostream& operator<< (std::ostream& os, const HomeDestination & hd) ;

private:
    std::vector<std::unique_ptr<Card>> storage_;
};

#endif
