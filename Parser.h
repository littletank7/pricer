#ifndef __PARSER_H__
#define __PARSER_H__

#include "Order.h"

namespace Pricer
{
  class Parser
  {
  public:
    Parser() {}
    Order* Take();    
    ~Parser() {}
    
  private:
    Order* parse(const std::string& line);
    ActionType parseAT(const std::string& s);
    OrderType parseOT(const std::string& s);
    
    static const int addLen = 6;
    static const int reduceLen = 4;
    static const int timeIdx = 0;
    static const int actionIdx = 1;
    static const int oidIdx = 2;
    static const int sideIdx = 3;
    static const int priceIdx = 4;
    static const int sizeIdx = 5;
    static const int reduceSizeIdx = 3;
    static const std::string s_add;
    static const std::string s_buy;
    static const std::string s_reduce;
    static const std::string s_sell;
    
    //declare away
    Parser(const Parser&);
    Parser& operator=(const Parser&);
  };
}

#endif