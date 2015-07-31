#include "Parser.h"
#include <sstream>
#include <iterator>
#include <vector>
#include <iostream>

namespace Pricer
{ 
  const std::string Parser::s_add = "A";
  const std::string Parser::s_buy = "B";
  const std::string Parser::s_reduce = "R";
  const std::string Parser::s_sell = "S";

  shared_ptr<Order> Parser::Take()
  {
    while(true)
    {
      std::string line("");
      std::getline(std::cin, line);
      if(line == "") return nullptr;
      return parse(line);    
    }
  }

  shared_ptr<Order> Parser::parse(const std::string& line)
  {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    copy(istream_iterator<string>(iss),
  	 istream_iterator<string>(),
         back_inserter(tokens));
    if(tokens.size() == addLen)
    {
      shared_ptr<Order> order(new Order(std::stoul(tokens[timeIdx],nullptr,0), \
        tokens[oidIdx], parseAT(tokens[actionIdx])));
      order->SetSide(parseOT(tokens[sideIdx]));
      order->SetPrice(std::stod(tokens[priceIdx]));
      order->SetSize(std::stoul(tokens[sizeIdx],nullptr,0));
      return order;
    }
    else if(tokens.size() == reduceLen)
    {
      shared_ptr<Order> order(new Order(std::stoul(tokens[timeIdx],nullptr,0), \
        tokens[oidIdx], parseAT(tokens[actionIdx])));
      order->SetSize(std::stoul(tokens[reduceSizeIdx],nullptr,0));
      return order;
    }
    std::cerr << "invalid message" << endl;
    return nullptr;
  }

  ActionType Parser::parseAT(const string& s)
  {
    if(s != s_add && s!= s_reduce)
      std::cerr << "invalid action" << endl;
    return s == s_add ? Add : Reduce;
  }

  OrderType Parser::parseOT(const string& s)
  { 
    if(s != s_buy && s!= s_sell)
      std::cerr << "invalid side" << endl;
    return s == s_buy ? Buy : Sell;
  }
}