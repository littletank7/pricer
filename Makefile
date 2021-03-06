CXX=g++
RM=rm -f
CXXFLAGS = -O3 -Wall -DNDEBUG

SRCS=src/Order.cpp src/OrderWriter.cpp src/Parser.cpp src/OrderBookImpl.cpp src/OrderBookEng.cpp src/Main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: pricer

pricer: $(OBJS)
	$(CXX) -o pricer $(OBJS)

clean:
	$(RM) $(OBJS) pricer *.txt
smoketest:
	make pricer
	cat pricer.in | ./pricer 1 > out1.txt
	cat pricer.in | ./pricer 200 > out200.txt
	cat pricer.in | ./pricer 10000 > out10000.txt
	diff -q pricer.out.1 out1.txt
	diff -q pricer.out.200 out200.txt
	diff -q pricer.out.10000 out10000.txt