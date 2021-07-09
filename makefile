zalgo: zalgo.h zalgo.cc
	$(CXX) -o zalgo zalgo.cc zalgo.h -Wall -Werror -Wextra -pedantic
	rm -f *.o

clean:
	rm -f *.o