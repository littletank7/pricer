#include "OrderBookImpl.h"
#include <cmath>

namespace Pricer
{

  void OrderBookImpl::Add(shared_ptr<Order>& o)
  {
    size += o->GetSize();
    orders.insert(o);
    orderIdMap.insert(std::make_pair(o->GetOrderId(), o));
    if(size < target)
      return;
    processTotal(o->GetTimeStamp());
  }

  void OrderBookImpl::processTotal(unsigned int ts)
  {
    double totalExpense = getTotalExpense();
    if(totalExpense == numeric_limits<double>::min()
        && lastTotal != numeric_limits<double>::min())
      writer->Write(ts, side, totalExpense);
    
    if(totalExpense != numeric_limits<double>::min()
        && (lastTotal == numeric_limits<double>::min() 
      	    || (std::fabs(totalExpense - lastTotal) >= 0.001)))
      writer->Write(ts, side, totalExpense);
    
    lastTotal = totalExpense;
  }

  double OrderBookImpl::getTotalExpense()
  {
    if(orders.empty() || size < target)
      return numeric_limits<double>::min();

    unsigned int temp = 0;
    unsigned int nextSize = 0;
    double nextPrice = 0;
    double value = 0;
    std::set<shared_ptr<Order> >::iterator it;
  
    for(it=orders.begin(); it!= orders.end();++it)
    {
      nextSize = (*it)->GetSize();
      nextPrice = (*it)->GetPrice();
      if(temp + nextSize >= target)
        break;
      temp += nextSize;
      value += nextSize * nextPrice;
    }
    if(temp + nextSize == target)
    {
      value += nextPrice * nextSize;      
    }
    else
    {
      value += (target - temp) * nextPrice;
    }
    return value;
  }

  bool OrderBookImpl::Reduce(shared_ptr<Order>& o)
  {
    if(orderIdMap.find(o->GetOrderId()) == orderIdMap.end())
    {
      return false;
    }

    shared_ptr<Order> orig = orderIdMap[o->GetOrderId()];
    if(o->GetSize() < orig->GetSize())
    {
      orig->SetSize(orig->GetSize() - o->GetSize());
      size -= o->GetSize();
      if(size + o->GetSize() >= target)
        processTotal(o->GetTimeStamp());
    }
    else
    {
      size -= o->GetSize();
      orders.erase(orig);
      orderIdMap.erase(o->GetOrderId());
      if(size + orig->GetSize() >= target)
        processTotal(o->GetTimeStamp());
    }
    return true;
  }
  
  OrderBookImpl::~OrderBookImpl()
  {}
}