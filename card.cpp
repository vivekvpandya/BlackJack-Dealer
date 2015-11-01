#include "card.h"
#include <iostream>
#include <sstream>

using namespace std;
Card::Card()
{}
    Card::Card(Rank r, Suit s, bool isFace)
    { rank = r;
      suit = s;
      isFaceUp = isFace;
    }

    int Card::getValue() const
    {
        //if a cards is face down, its value is 0
        int value = 0;
        if (isFaceUp)
        {
            if(rank > 10)
                value = 10;
            else
                value = rank;

    }
        return value;
    }

    void Card::flip()
    {
            isFaceUp = !isFaceUp;
    }

    string Card::convert()
    {
        std::ostringstream oss;
        string str;
            const string RANKS[] = {"0", "1", "2", "3", "4", "5", "6", "7",
                "8", "9","10", "11", "12", "13"};
            const string SUITS[] = {"1", "2", "3", "4"};

            if (isFaceUp)
                oss << ":images/" << SUITS[suit] << RANKS[rank] << ".png";
            else
                oss << ":images/" << "back" << ".png";

            str = oss.str();
            return str;
    }



