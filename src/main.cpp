#include <GL/glut.h>
#include <vobject.hpp>
#include <facedetect.hpp>
#include <objcontroller.hpp>
#include <thread>

int main(int argc, char** argv) {
    ObjController *oc = new ObjController(10, 10, 10);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Cube");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    setController(oc);
    std::thread vc(videoCapture);

    initGL(oc);
    glutMainLoop();

    vc.join();

    delete oc;
    return 0;
}
