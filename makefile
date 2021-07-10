zalgo: zalgo.cc zalgo.h
	$(CXX) -o zalgo zalgo.cc -Wall -Werror -Wextra -pedantic -std=c++11
	rm -f *.o

clean:
	rm -f *.o