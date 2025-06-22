#pragma once

#include <QOpenGLWidget>
#include <QVector3D>
#include <QMouseEvent>

class RobotGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit RobotGLWidget(int32_t jointCnt, QWidget* parent = nullptr);

    void updateJoints(const std::vector<QVector3D>& jointPositions);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    std::vector<QVector3D> m_joints;
    int32_t m_jointCnt;

    QPointF m_lastMousePos;
    std::array<float, 2> m_shift;

    bool m_leftButtonPressed;

};
