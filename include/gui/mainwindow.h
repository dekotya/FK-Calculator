#pragma once

#include "../../include/RobotModel.h"
#include "../../include/KinematicsCalculator.h"
#include "../../include/gui/JointGroupBox.h"
#include "../../include/gui/RobotGLWidget.h"
#include <QMainWindow>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(RobotModel& robotModel, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //void onCalculateClicked();

private:
    void setupUi();
    void setupConnections();
    void updateCartesianCoord();

    std::vector<JointGroupBox*> m_jointGroupBoxes;

    QWidget *m_centralWidget;
    QLabel *m_Xpos, *m_Ypos, *m_Zpos;
    RobotGLWidget* m_robotGlWidget;

    RobotModel& m_robotModel;
    std::unique_ptr<KinematicsCalculator> m_kinematicsCalc;

    int32_t m_jointCnt;
};

