CXX=g++
RM=rm -f
CXXFLAGS = -O3 -Wall -DNDEBUG

SRCS=Order.cpp OrderWriter.cpp Parser.cpp OrderBookImpl.cpp OrderBookEng.cpp Main.cpp
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