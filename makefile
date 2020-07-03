all:baseline

baseline:baseline.cpp
	g++ $$(pkg-config --cflags --libs opencv4) -std=c++11 baseline.cpp -o baseline

clean:
	rm -f *.o baseline