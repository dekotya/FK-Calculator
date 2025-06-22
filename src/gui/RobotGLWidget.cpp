#include "../../include/gui/RobotGLWidget.h"
#include <GL/glu.h>
#include <GL/glut.h>

RobotGLWidget::RobotGLWidget(int32_t jointCnt, QWidget* parent)
    : QOpenGLWidget(parent),
    m_jointCnt(jointCnt),
    m_joints(jointCnt),
    m_leftButtonPressed(false)
{
    int argc = 1;
    char* argv[] = {(char*)"RobotGLWidget"};
    glutInit(&argc, argv);

    m_shift.fill(0);
}

void RobotGLWidget::updateJoints(const std::vector<QVector3D>& jointPositions)
{
    if (jointPositions.size() != m_joints.size()) {
        std::string errorMsg = "Invalid value: " + std::to_string(jointPositions.size()) + " != " + std::to_string(m_joints.size());
        throw std::invalid_argument(errorMsg);
    }

    m_joints = jointPositions;
    update();
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

    glTranslatef(m_shift[0], m_shift[1], 0);

    gluLookAt(2, 2, 2,
              0, 0, 0,
              0, 0, 1);

    glBegin(GL_LINES);
    {
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
    }
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 0);
    for (const auto& joint : m_joints) {
        glVertex3f(joint.x(), joint.y(), joint.z());
    }
    glEnd();

    glColor3f(1, 0.5, 0);
    for (const auto& joint : m_joints) {
        glPushMatrix();
        glTranslatef(joint.x(), joint.y(), joint.z());
        glutSolidSphere(0.05, 10, 10);
        glPopMatrix();
    }
}

void RobotGLWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_leftButtonPressed = true;
        m_lastMousePos = event->position();
    }
}

void RobotGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_leftButtonPressed)
    {
        float dx = event->position().x() - m_lastMousePos.x();
        float dy = event->position().y() - m_lastMousePos.y();

        m_shift[0] += dx * 0.01f;
        m_shift[1] -= dy * 0.01f;

        m_lastMousePos = event->position();
        update();
    }
}

void RobotGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_leftButtonPressed)
    {
        m_leftButtonPressed = false;
    }
}
