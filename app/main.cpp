#include "../include/gui/mainwindow.h"
#include "../include/RobotModel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int32_t jointCnt = 6;
    std::vector<DHJoint> joints = {
        { 15.0,  0.0,    0.213, M_PI_2},
        {-50.0, -0.8,    0.193, 0.0},
        {-60.0, -0.590, -0.16,  0.0},
        { 95.0,  0.0,    0.25,  M_PI_2},
        { 50.0,  0.0,    0.28, -M_PI_2},
        { 0.0,   0.0,    0.25,  0.0}
    };

    RobotModel model(jointCnt);
    model.setAllJointsParams(jointCnt, joints);

    MainWindow w(model);
    w.show();
    return a.exec();
}
