zalgo: zalgo.h zalgo.cc
	$(CXX) -o zalgo zalgo.cc zalgo.h -Wall -Werror -Wextra -pedantic -std=c++11
	rm -f *.o

clean:
	rm -f *.o