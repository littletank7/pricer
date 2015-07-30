#include "OrderBookEng.h"

namespace Pricer
{
    OrderBookEng::OrderBookEng(Parser* parser, unsigned int target, OrderWriter* writer)
    {
      unique_ptr<Parser> pp(parser);
      input = std::move(pp);
      shared_ptr<OrderWriter> pwriter(writer);
      unique_ptr<OrderBookImpl> pobib(new OrderBookImpl(Buy, target, pwriter));
      bids = std::move(pobib);
      unique_ptr<OrderBookImpl> pobis(new OrderBookImpl(Sell, target, pwriter));
      asks = std::move(pobis);
      pwriter.reset();
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
