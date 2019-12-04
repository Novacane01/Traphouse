create:
	g++ -std=c++11 -Wall -o traphouse -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-system *.cpp UI/*.cpp