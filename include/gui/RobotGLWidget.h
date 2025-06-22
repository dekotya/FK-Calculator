#pragma once

#include <QOpenGLWidget>
#include <QVector3D>

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

private:
    std::vector<QVector3D> m_joints; // Позиции суставов
    int32_t m_jointCnt;
};
