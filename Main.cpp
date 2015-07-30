#include <iostream>
#include "OrderBookEng.h"

using namespace Pricer;

int main(int argc, char **argv)
{
  try
  {
    if(argc < 2)
    {
      std::cerr << "Useage: pricer targetSize" << std::endl;
      return 1;
    }
    
    unsigned int target = std::stoul(argv[1]);
    Parser* parser = new Parser();
    OrderWriter* writer = new OrderWriter();
    OrderBookEng* eng = new OrderBookEng(parser, target, writer);
    eng->Run();
    delete eng;
  }
  catch(std::exception & ex)
  {
    std::cerr << "Exception caught: " << ex.what() << std::endl;
    return 1;
  }
  return 0;
}
