#include <GL/glut.h>

// Rotation angles
float angleX = 0.0f, angleY = 0.0f;

void initGL() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
    glLoadIdentity(); // Reset modelview matrix

    glTranslatef(0.0f, 0.0f, -7.0f); // Move into the screen
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis

    glBegin(GL_QUADS); // Start drawing cube

    // Front face (red)
    glColor3f(1.0f, 0.0f, 0.0f);     
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    // Back face (green)
    glColor3f(0.0f, 1.0f, 0.0f);     
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Top face (blue)
    glColor3f(0.0f, 0.0f, 1.0f);     
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Bottom face (yellow)
    glColor3f(1.0f, 1.0f, 0.0f);     
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Right face (cyan)
    glColor3f(0.0f, 1.0f, 1.0f);     
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Left face (magenta)
    glColor3f(1.0f, 0.0f, 1.0f);     
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

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