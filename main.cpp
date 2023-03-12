#include <iostream>
#include "OrderBook.h"

int main(int, char**) {
    OrderBook book;
    book.addBid(100, 5);
    book.addBid(145, 5);
    book.removeBid(145,5);
    book.addAsks(380, 45);
    book.removeAsks(380,46);
    book.stopLoss(340,2,false);
}
