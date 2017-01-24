//
//  main.cpp
//
//  Created by Matthew Lei on 12/20/16.
//

// Exercise: sort deck of cards (string) by suit and value

#include <iostream>
#include <unordered_map>
#include <list>
#include <exception>

using namespace std;

static const unordered_map<string, int> card_value = {
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"10", 10},
    {"J", 11},
    {"Q", 12},
    {"K", 13},
    {"A", 14},
};

enum EnumSuit {
    SUIT_D,
    SUIT_S,
    SUIT_C,
    SUIT_H,
};

static const unordered_map<string, EnumSuit> card_suit = {
    {"d", SUIT_D},
    {"s", SUIT_S},
    {"c", SUIT_C},
    {"h", SUIT_H},
};

void read_card(string s, int &value, EnumSuit &suit) {
    if (s.empty()) {
        throw(string("{Empty String}"));
    }
    
    string tmp_val = string(s.begin(), s.end() - 1);
    string tmp_suit = string(s.end() - 1, s.end());
    
    if (card_value.find(tmp_val) == card_value.end()
        || card_suit.find(tmp_suit) == card_suit.end()) {
        throw(s);
    } else {
        value = card_value.at(tmp_val);
        suit = card_suit.at(tmp_suit);
    }
}

bool compare_cards(string a, string b) {
    int a_val, b_val;
    EnumSuit a_suit, b_suit;
    
    try {
        read_card(a, a_val, a_suit);
        read_card(b, b_val, b_suit);
    } catch (string e) {
        cout << "Found Unknown Card: " << e << endl;
        cout << "Program closing...\n";
        exit(0);
    } catch (...) {
        cout << "Error while parsing cards" << endl;
        exit(-1);
    }
    
    if (a_suit <= b_suit) {
        if (a_suit == b_suit) {
            return a_val < b_val;
        } else {
            return true;
        }
    } else {
        return false;
    }
    
}

void print_cards(list<string> deck) {
    for (auto card : deck) {
        cout << card << " ";
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    list<string> deck =  { "3c", "Js", "2d", "10h", "Kd", "7s", "Qh", "8s", "5d", "6h", "9c", "Ac", "4h" };
    print_cards(deck);
    deck.sort(compare_cards);
    print_cards(deck);
    return 0;
}
