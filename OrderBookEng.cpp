#include "OrderBookEng.h"
#include <iostream>

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
    }
    
    void OrderBookEng::Run()
    {
      shared_ptr<Order> order = nullptr;
      while(true)
      {
        try
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
            {
              if(!asks->Reduce(order))
                std::cerr << "Exception: " << order->GetTimeStamp() <<" order " \
                << order->GetOrderId() << " is not found." << std::endl;
            }
          }
        }catch(std::exception& ex)
        {
          std::cerr << "Exception: " << ex.what() << std::endl;
        }
      }
    }
}
