#ifndef __ORDERBOOK_ENG_H__
#define __ORDERBOOK_ENG_H__

#include "Parser.h"
#include "OrderWriter.h"
#include "OrderBookImpl.h"

namespace Pricer
{
  class OrderBookEng
  {
  public:
    OrderBookEng(Parser* parser, unsigned int target, OrderWriter* writer);
    void Run();
    ~OrderBookEng()
    {}

  private:
    unique_ptr<Parser> input;
    unique_ptr<OrderBookImpl> bids;
    unique_ptr<OrderBookImpl> asks;
    
    //declare away
    OrderBookEng(const OrderBookEng&);
    OrderBookEng& operator=(const OrderBookEng&);
  };
}

#endif