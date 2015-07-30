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
    {
      delete input;
      delete bids;
      delete asks;
      delete writer;
    }
  private:
    Parser* input;
    OrderBookImpl* bids;
    OrderBookImpl* asks;
    OrderWriter* writer;
    
    //declare away
    OrderBookEng(const OrderBookEng&);
    OrderBookEng& operator=(const OrderBookEng&);
  };
}

#endif