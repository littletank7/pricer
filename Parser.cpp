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
      try
      {
        std::string line("");
        std::getline(std::cin, line);
        if(line == "") return nullptr;
        return parse(line);
      }
      catch(std::exception& ex)
      {
        std::cerr << "Exception: " << ex.what() << std::endl;
      }
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
      shared_ptr<Order> order(new Order(parseUint(tokens[timeIdx]), \
        tokens[oidIdx], parseAT(tokens[actionIdx])));
      order->SetSide(parseOT(tokens[sideIdx]));
      order->SetPrice(parseDouble(tokens[priceIdx]));
      order->SetSize(parseUint(tokens[sizeIdx]));
      return order;
    }
    else if(tokens.size() == reduceLen)
    {
      shared_ptr<Order> order(new Order(parseUint(tokens[timeIdx]), \
        tokens[oidIdx], parseAT(tokens[actionIdx])));
      order->SetSize(parseUint(tokens[reduceSizeIdx]));
      return order;
    }
    throw std::invalid_argument("invalid message");
  }

  ActionType Parser::parseAT(const string& s)
  {
    if(s != s_add && s!= s_reduce)
      throw std::invalid_argument("invalid action");
    return s == s_add ? Add : Reduce;
  }

  OrderType Parser::parseOT(const string& s)
  { 
    if(s != s_buy && s!= s_sell)
      throw std::invalid_argument("invalid side");
    return s == s_buy ? Buy : Sell;
  }

  template<typename T> bool Parser::isValidType(const std::string& s)
  {
    std::istringstream iss(s);
    T t;
    iss >> t;
    return iss.eof() && !iss.fail();
  }

  double Parser::parseDouble(const string& s)
  {
    if(!isValidType<double>(s))
      throw std::invalid_argument("invalid price");
    return std::stod(s);
  }

  unsigned int Parser::parseUint(const string& s)
  {
    if(!isValidType<unsigned int>(s))
      throw std::invalid_argument("invalid timestamp/size");
    return std::stoul(s, nullptr ,0);
  }
}