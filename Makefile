CPP = g++
CFLAGS = -Wall -Wextra -Werror 
NEWFLAG = -std=c++0x

all: Tweet NaughtyNice TweetHash

Tweet: tweet.cpp 
	$(CPP) $(CFLAGS) -o Tweet tweet.cpp

TweetHash: tweetHash.cpp
	$(CPP) $(CFLAGS) $(NEWFLAG) -o TweetHash tweetHash.cpp

NaughtyNice: NaughtyNice.cpp
	$(CPP) $(CFLAGS) -o NaughtyNice NaughtyNice.cpp

clean:
	rm -f *.o;
	rm -f Tweet; rm -f NaughtyNice; rm -f TweetHash
	rm -f cleantweets; rm -f *.log;
	rm -f *~;
