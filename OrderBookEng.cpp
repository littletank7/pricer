#include "OrderBookEng.h"

namespace Pricer
{
    OrderBookEng::OrderBookEng(Parser* parser, unsigned int target, OrderWriter* writer)
      : input(parser), writer(writer)
    {
      bids = new OrderBookImpl(Buy, target, writer);
      asks = new OrderBookImpl(Sell, target, writer);
    }
    
    void OrderBookEng::Run()
    {
      Order* order = nullptr;
      while(true)
      {
        order = input->Take();
        if(order == nullptr)
          break;
        if(order->GetAction() == Add)
        {
          ((order->GetSide() == Buy) ? bids : asks)->Add(order);
        }
        else
        {
          if(!bids->Reduce(order))
            asks->Reduce(order);
        }
      }
    }
}
