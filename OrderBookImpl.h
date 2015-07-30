#ifndef __ORDERBOOK_IMPL_H__
#define __ORDERBOOK_IMPL_H__

#include "Order.h"
#include "OrderWriter.h"
#include <unordered_map>
#include <set>
#include <memory>

namespace Pricer
{
  class OrderBookImpl
  {
  public:
    OrderBookImpl(OrderType side, unsigned int target, shared_ptr<OrderWriter>& pwriter)
      : side(side), target(target), writer(pwriter), size(0), lastTotal(std::numeric_limits<double>::min())
    {}
    void Add(Order* o);
    bool Reduce(Order* o);
    ~OrderBookImpl();
  private:
    void processTotal(unsigned int p);
    double getTotalExpense();
    
    const OrderType side;
    const unsigned int target;
    shared_ptr<OrderWriter> writer;
    std::set<Order*, order_compare> orders;
    std::unordered_map<string, Order*> orderIdMap;
    unsigned int size;
    double lastTotal;
    
    //declare away
    OrderBookImpl();
    OrderBookImpl(const OrderBookImpl&);
    OrderBookImpl& operator=(const OrderBookImpl&);
  };
}

#endif