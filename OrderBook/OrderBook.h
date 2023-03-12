#pragma once
#include <map>
#include <iostream>
#include <optional>


class OrderBook{
    std::map<int, int> bids;
    std::map<int, int> asks;
    void add(int price, int ammount, bool bid);
    void remove(int price, int ammount, bool bid);
public:
    struct Bidask{
        typedef std::optional<std::pair<int,int>> Entry; 
        Entry bid,ask;
        boost::optional<int> spread() const;
    }
    bool inline is_empty() const; //about inline func


    void addBid(int price, int ammount);
    void addAsks(int price, int ammount);

    void removeBid(int price, int ammount);
    void removeAsk(int price, int ammount);

    void stopLoss(int triggerPrice, int ammount, bool longPosition);


    Bidask getBidAsk() const;

    friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);
};
