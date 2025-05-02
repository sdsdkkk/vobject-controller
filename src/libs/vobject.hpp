#include <GL/glut.h>
#include <objcontroller.hpp>

// Rotation angles
float angleX = 0.0f, angleY = 0.0f;

ObjController *_ocGL;
float anchorX = 0.0f, anchorY = 0.0f, anchorZ = 0.0f;

void initGL(ObjController *oc) {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    _ocGL = oc;
}

void updatePosition() {
    anchorX = (((float) _ocGL->x / 1000) - 0.5) * 2;
    anchorY = (((float) _ocGL->y / 1000) - 0.5) * 2;
    //anchorZ = ((float) _ocGL->z / 1000) - 0.5;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity(); // Reset modelview matrix
    updatePosition();

    glTranslatef(0.0f, 0.0f, -7.0f); // Move into the screen
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

    glBegin(GL_QUADS); // Start drawing cube

    // Front face (red)
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(-1.0f + anchorX, -1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX, -1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX,  1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f(-1.0f + anchorX,  1.0f + anchorY,  1.0f + anchorZ);

    // Back face (green)
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f + anchorX, -1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f(-1.0f + anchorX,  1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX,  1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX, -1.0f + anchorY, -1.0f + anchorZ);

    // Top face (blue)
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(-1.0f + anchorX,  1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f(-1.0f + anchorX,  1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX,  1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX,  1.0f + anchorY, -1.0f + anchorZ);

    // Bottom face (yellow)
    glColor3f(1.0f, 1.0f, 0.0f); 
    glVertex3f(-1.0f + anchorX, -1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX, -1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX, -1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f(-1.0f + anchorX, -1.0f + anchorY,  1.0f + anchorZ);

    // Right face (cyan)
    glColor3f(0.0f, 1.0f, 1.0f); 
    glVertex3f( 1.0f + anchorX, -1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX,  1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX,  1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f( 1.0f + anchorX, -1.0f + anchorY,  1.0f + anchorZ);

    // Left face (magenta)
    glColor3f(1.0f, 0.0f, 1.0f); 
    glVertex3f(-1.0f + anchorX, -1.0f + anchorY, -1.0f + anchorZ);
    glVertex3f(-1.0f + anchorX, -1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f(-1.0f + anchorX,  1.0f + anchorY,  1.0f + anchorZ);
    glVertex3f(-1.0f + anchorX,  1.0f + anchorY, -1.0f + anchorZ);

    glEnd(); // Done drawing cube

    glutSwapBuffers(); // Swap the buffers
}

void timer(int value) {
    angleX += 0.5f;
    angleY += 0.5f;
    glutPostRedisplay(); // Redraw
    glutTimerFunc(16, timer, 0); // Call again after ~60 FPS
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}
