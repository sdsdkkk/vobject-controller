all:
	mkdir -p bin
	g++ src/main.cpp -o bin/vobject -Isrc/libs -I/usr/include/opencv4 -L/usr/local/lib -lGL -lGLU -lglut \
	  -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_objdetect -lglfw -lopencv_imgcodecs -lGLEW