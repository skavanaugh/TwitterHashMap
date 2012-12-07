csci333-final
=============

I decided to implement the tweets program as a hash table as well as a map and ran some crude timing tests on both executables.  The time to run Tweet is 0.46 seconds on average and the time to run TweetHash is 0.35 seconds on average.  Also note that I had to hack around to print tweetHash.cpp properly as the unordered_multimap does not have a reverse iterator.  I didn't think of an elegant solution to printing the unordered_multimap in descending order so I copied the entire unordered_multimap to a vector<pair<int,string> > and printed that out in descending order.  I tried the timing tests without copying to the vector with the unordered_multimap printing in ascending order and the time to run was still 0.35 seconds on average.  

I had to set a compiler flag to use the unordered_map and unordered_multimap which you will notice in the Makefile. 

I decided not to post the tweet.cpp with the timing tests because it is not really what was asked for but I am happy to post it if you would like to see it.  It's only a handful of lines of code.
 
Please note that the Tweet and TweetHash executables require a datafile as a command line argument and the NaughtyNice executable requires a datafile and a threshold integer as command line arguments.
