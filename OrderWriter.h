#ifndef __ORDER_WRITER_H__
#define __ORDER_WRITER_H__

#include "Order.h"

namespace Pricer
{
  class OrderWriter
  {
  public: 
    OrderWriter() {}
    void Write(unsigned int timestamp, OrderType side, double price);
    ~OrderWriter() {}
    
  private:
    std::string toString(double v);    
    static const std::string NullPriceString;
    
    //declare away
    OrderWriter(const OrderWriter&);
    OrderWriter& operator=(const OrderWriter&);
  };	
}
#endif

