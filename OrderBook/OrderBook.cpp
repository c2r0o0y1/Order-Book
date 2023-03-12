#include "OrderBook.h"
// #include <map>

bool inline OrderBook:: is_empty() const{
    return bids.empty() && asks.empty();
}

void OrderBook::add(int price, int ammount, bool bid){
    if(bid == true){
        bids[price] += ammount;
    }

    else{
        asks[price] += ammount;
    }
}

void OrderBook::addBid(int price, int ammount){
    add(price,ammount,true);
}

void OrderBook::addAsks(int price, int ammount){
    add(price,ammount,false);
}


void OrderBook::remove(int price, int ammount, bool bid){
    if(bid == true){
        bids[price] -= ammount;
        if(!bids[price]){
            bids.erase(price);
        }
    }

    else{
        asks[price] -= ammount;
        if(!asks[price]){
            asks.erase(price);
        }
    }
}

void OrderBook::removeBid(int price, int ammount){
    if(bids.find(price) != bids.end() && bids[price] >= ammount){
        remove(price,ammount,true);
    }
}

void OrderBook::removeAsks(int price, int ammount){
    if(asks.find(price) != asks.end() && asks[price] >= ammount){
        remove(price,ammount,false);
    }
}

void OrderBook::stopLoss(int triggerPrice, int ammount, bool longPosition){
    if(longPosition){
        for(auto bid : bids){
            // Remove bids above trigger price
            if(bid.first > triggerPrice){
                removeBid(bid.price, ammount);
            }
        }
    }
    else{
        // remove asks below trigger price
        for(auto ask : asks){
            if(ask.price < triggerPrice){
                removeAsks(ask.price, ammount);
            }
        }
    }
}

OrderBook::Bidask OrderBook::getBidAsk() const{
    Bidask result;

    auto bestBid = bids.rbegin();
    if(bestBid != bids.rend()){
        result.bid = *bestBid;
    }

    auto bestAsk = asks.begin();
    if(bestAsk != asks.end()){
        result.ask = *bestAsk;
    }

    return result;
}

boost::optional<int> OrderBook::Bidask::spread() const{
    boost::optional<int> result;

    if(bid.is_initialized() && ask.is_initialized()){
        result = ask.get().first - bid.get().first;
    }
}

std::ostream& operator<<(std::ostream& os, const OrderBook& book){
    if(book.is_empty()){
        os << "THE ORDER BOOK IS EMPTY!!!";
        return os;
    }

    for(map<int,int>::reverse_iterator it = book.bids.rbegin() ; it != book.bids.rend() ; it++){
        os << it.first << "\t" << it.second << std::endl;
    }

    os << std::endl;

    for(map<int,int>::reverse_iterator it = book.asks.rbegin() ; it != book.asks.rend() ; it++){
        os << it.first << "\t" << it.second << std::endl;
    }

    return os;
}

