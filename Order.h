#ifndef __ORDER_H__
#define __ORDER_H__

#include <string>
#include <memory>
#include <assert.h>

using namespace std;

namespace Pricer
{

  enum OrderType { Buy, Sell};
  enum ActionType { Add, Reduce};
  
  const char c_add('A');
  const char c_reduce('R');
  const char c_buy('B');
  const char c_sell('S');
  const char c_space(' '); 

  class Order
  {
  public: 
    Order(unsigned int ts, string oid, ActionType at) : timeStamp(ts), orderId(oid), actionType(at)
    {}
    
    Order(const Order& another)
    {
      timeStamp = another.timeStamp;
      actionType = another.actionType;
      size = another.size;
      price = another.price;
      side = another.side;
      orderId = another.orderId;
    }

    const OrderType GetSide() const
    {
      return side;
    }

    void SetSide(OrderType s)
    { 
      side = s;
    }

    const unsigned int GetSize() const
    { 
      return size;
    }

    void SetSize(unsigned int s)
    { 
      size = s;
    }

    const double GetPrice() const
    { 
      return price;
    }
  
    void SetPrice(double p)
    { 
      price = p;
    }

    const string GetOrderId() const
    {
      return orderId;
    }

    const unsigned int GetTimeStamp() const
    {
      return timeStamp;
    }

    const ActionType GetAction() const
    {
      return actionType;
    }
  
    ~Order() {}

  private:
    //declare away
    Order();    
    Order& operator=(const Order&);

    unsigned int timeStamp;
    string orderId;
    ActionType actionType;
    unsigned int size;
    double price;
    OrderType side;    
  };
  
  struct order_compare 
  {
    bool operator() (const shared_ptr<Order>& lhs, const shared_ptr<Order>& rhs) const
    {      
      if(lhs == nullptr || rhs == nullptr)
      	      return false;
      assert(lhs->GetSide() == rhs->GetSide());
      if(lhs->GetPrice() == rhs->GetPrice())
        return lhs->GetOrderId() < rhs->GetOrderId();
      else
      	return lhs->GetSide() == Buy \
          ? lhs->GetPrice() > rhs->GetPrice() : lhs->GetPrice() < rhs->GetPrice(); 
    }
  };
}

#endif
