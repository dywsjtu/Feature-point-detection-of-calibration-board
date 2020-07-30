all:SubpixelDetector

SubpixelDetector:SubpixelDetector.cpp
	g++ $$(pkg-config --cflags --libs opencv4) -std=c++11 SubpixelDetector.cpp -o SubpixelDetector

clean:
	rm -f *.o SubpixelDetector