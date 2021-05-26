//
// Created by dim on 23/03/2021.
//

#include "Renderer.h"

#if _WIN32

#   include <Windows.h>

#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else

#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>

#endif

void Renderer::renderMesh(const Mesh& mesh) {
    for (Face face : mesh.faces){
//        face.normal = MeshHelper::calculateNormal(face);
        glBegin(GL_TRIANGLES);
            glNormal3f(face.normal.x, face.normal.y, face.normal.z);
            glVertex3f(face.vert1->position.x, face.vert1->position.y, face.vert1->position.z);
            glVertex3f(face.vert2->position.x, face.vert2->position.y, face.vert2->position.z);
            glVertex3f(face.vert3->position.x, face.vert3->position.y, face.vert3->position.z);
        glEnd();
    }
}

void Renderer::renderParticle(const Particle* particle) {
    glPushMatrix();
    move(particle->position);
    scale(particle->scale);
    renderMesh(particle->mesh);
    glPopMatrix();
}

void Renderer::drawRect(float width, float height) {
    float heightHalf = height / 2;
    float widthHalf = width / 2;

    glBegin(GL_LINE_LOOP);
    glVertex2f(widthHalf, heightHalf);
    glVertex2f(-widthHalf, heightHalf);
    glVertex2f(-widthHalf, -heightHalf);
    glVertex2f(widthHalf, -heightHalf);
    glEnd();
}

void Renderer::drawRectSolid(float width, float height) {
    float heightHalf = height / 2;
    float widthHalf = width / 2;

    glBegin(GL_QUADS);
    glVertex2f(widthHalf, heightHalf);
    glVertex2f(-widthHalf, heightHalf);
    glVertex2f(-widthHalf, -heightHalf);
    glVertex2f(widthHalf, -heightHalf);
    glEnd();
}

void Renderer::renderText(TextOrigin origin, Vector3 offset, const std::string& text, float scale) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

        glLoadIdentity();
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        glOrtho(0, w, 0, h, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

            glLoadIdentity();

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_LIGHTING);

            switch(origin){
                case centre:
                    Renderer::move(Vector3((float)w/2, (float)h/2, 0));
                    break;
                case topLeft:
                    Renderer::move(Vector3(0, (float)h, 0));
                    break;
                case topRight:
                    Renderer::move(Vector3((float)w, (float)h, 0));
                    break;
                case bottomLeft:
                    // This is the default
                    break;
                case bottomRight:
                    Renderer::move(Vector3((float)w, 0, 0));
                    break;
            }

            // Account for different screen resolutions with offset
            float impactUnit = (float)h*(float)w / 100000;
            Renderer::move(Vector3(offset.x * impactUnit, offset.y *impactUnit, 0));
            Renderer::scale(scale * impactUnit / 40);
            glColor3f(1, 0, 0);

            for (char c : text) {
                glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
            }

            glEnable(GL_LIGHTING);
            glEnable(GL_DEPTH_TEST);

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}


void Renderer::drawCharacter(char chr) {
    glutStrokeCharacter(GLUT_STROKE_ROMAN, chr);
}

void Renderer::drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        glVertex2f(cos(i * DEG_TO_RAD) * radius, sin(i * DEG_TO_RAD) * radius);
    }
    glEnd();
}

void Renderer::setColour(Vector3 colour) {
    glColor3f(colour.x, colour.y, colour.z);
}

void Renderer::move(Vector3 move) {
    glTranslatef(move.x, move.y, move.z);
}

void Renderer::rotate(Rotation rotation) {
    glRotatef(rotation.x, 1, 0, 0);
    glRotatef(rotation.y, 0, 1, 0);
    glRotatef(rotation.z, 1, 0, 1);
}

void Renderer::push() {
    glPushMatrix();
}

void Renderer::pop() {
    glPopMatrix();
}

void Renderer::scale(Vector3 scale) {
    glScalef(scale.x, scale.y, scale.z);
}

void Renderer::scale(float scale) {
    Renderer::scale(Vector3(scale, scale, scale));
}

void Renderer::moveCamera(Vector3 position, Vector3 direction) {
    gluLookAt(position.x, position.y, position.z,
              position.x + direction.x, position.y + direction.y, position.z + direction.z,
              0.0f, 1.0f, 0.0f);
}



