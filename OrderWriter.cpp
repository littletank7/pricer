#include "OrderWriter.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <iomanip>

namespace Pricer
{
    void OrderWriter::Write(unsigned int timestamp, OrderType side, double price)
    {
      std::cout << timestamp << c_space;
      std::cout << (side == Buy ? c_sell : c_buy) << c_space;
      std::cout << (price == std::numeric_limits<double>::min() \
            ? NullPriceString : toString(price) + "\n");      
    }
    
    const std::string OrderWriter::NullPriceString = "NA\n";
  
    std::string OrderWriter::toString(double v)
    {
      std::ostringstream out;
      out << std::setprecision(2) << fixed << v;
      return out.str();
    }   
}


