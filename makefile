all:baseline_opencv baseline_quadratic

baseline_opencv:baseline_opencv.cpp
	g++ $$(pkg-config --cflags --libs opencv4) -std=c++11 baseline_opencv.cpp -o baseline_opencv

baseline_quadratic:baseline_quadratic.cpp
	g++ $$(pkg-config --cflags --libs opencv4) -std=c++11 baseline_quadratic.cpp -o baseline_quadratic

clean:
	rm -f *.o baseline_opencv baseline_quadratic