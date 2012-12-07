CPP = g++
CFLAGS = -Wall -Wextra -Werror

all: Tweet NaughtyNice

Tweet: tweet.cpp 
	$(CPP) $(CFLAGS) -o Tweet tweet.cpp

NaughtyNice: NaughtyNice.cpp
	$(CPP) $(CFLAGS) -o NaughtyNice NaughtyNice.cpp

clean:
	rm -f *.o;
	rm -f Tweet; rm -f NaughtyNice;
	rm -f cleantweets; rm -f *.log;
	rm -f *~;
