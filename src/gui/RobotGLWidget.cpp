#include "../../include/gui/RobotGLWidget.h"
#include <GL/glu.h>
#include <GL/glut.h>

RobotGLWidget::RobotGLWidget(int32_t jointCnt, QWidget* parent)
    : QOpenGLWidget(parent),
    m_jointCnt(jointCnt),
    m_joints(jointCnt)
{
    // Инициализация GLUT (фиктивные аргументы)
    int argc = 1;
    char* argv[] = {(char*)"RobotGLWidget"};
    glutInit(&argc, argv);
}

void RobotGLWidget::updateJoints(const std::vector<QVector3D>& jointPositions)
{
    if (jointPositions.size() != m_joints.size()) {
        std::string errorMsg = "Invalid value: " + std::to_string(jointPositions.size()) + " != " + std::to_string(m_joints.size());
        throw std::invalid_argument(errorMsg);
    }

    m_joints = jointPositions;
    update(); //
}

void RobotGLWidget::initializeGL()
{
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

void RobotGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void RobotGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // наблюдение
    gluLookAt(2, 2, 2,  // Позиция камеры
              0, 0, 0,  // Точка наблюдения
              0, 0, 1); // Вектор "вверх"

    // Оси
    glBegin(GL_LINES);
    {
        // X
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);

        // Y
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);

        // Z
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
    }
    glEnd();

    // робот
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 0);
    for (const auto& joint : m_joints) {
        glVertex3f(joint.x(), joint.y(), joint.z());
    }
    glEnd();

    // суставы
    glColor3f(1, 0.5, 0);
    for (const auto& joint : m_joints) {
        glPushMatrix();
        glTranslatef(joint.x(), joint.y(), joint.z());
        glutSolidSphere(0.05, 10, 10); // сфера в каждой точке
        glPopMatrix();
    }
}
