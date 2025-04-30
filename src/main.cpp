#include <GL/glut.h>
#include <vobject.h>
#include <facedetect.hpp>
#include <thread>

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Cube");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    std::thread vc(videoCapture);

    initGL();
    glutMainLoop();

    vc.join();

    return 0;
}
