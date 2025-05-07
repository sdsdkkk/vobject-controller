#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
#include <iostream>

/* A prototype code snippet to make an OpenGL Window that shows webcam stream.
Build with this command:
    g++ window.cpp -o prototype-window -Isrc/libs -I/usr/include/opencv4 -L/usr/local/lib -lGL -lGLU -lglut \
          -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_objdetect -lglfw -lopencv_imgcodecs -lGLEW
*/

GLuint loadTextureFromMat(const cv::Mat& image) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    cv::Mat imgRGB;
    cv::cvtColor(image, imgRGB, cv::COLOR_BGR2RGB); // OpenGL wants RGB
    cv::flip(imgRGB, imgRGB, 0); // Flip vertically, since OpenGL and OpenCV use some reverse coordinate positions

    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Safe for any image width

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgRGB.cols, imgRGB.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, imgRGB.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // REQUIRED
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  // REQUIRED
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Safer on all GPUs
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureID;
}

void drawTexturedQuad(GLuint textureID) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.f); glVertex2f(-1.f, -1.f);
        glTexCoord2f(1.f, 0.f); glVertex2f(1.f, -1.f);
        glTexCoord2f(1.f, 1.f); glVertex2f(1.f, 1.f);
        glTexCoord2f(0.f, 1.f); glVertex2f(-1.f, 1.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenCV + OpenGL", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    
    GLuint texture;
    cv::Mat img;
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        cap.read(img);
        texture = loadTextureFromMat(img);
        glClear(GL_COLOR_BUFFER_BIT);
        drawTexturedQuad(texture);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cap.release();
    glDeleteTextures(1, &texture);
    glfwTerminate();
    return 0;
}
