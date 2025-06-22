#pragma once

#include <Eigen/Dense>
#include "../include/RobotModel.h"

class KinematicsCalculator
{
public:
    explicit KinematicsCalculator(const RobotModel& robotModel);

    ~KinematicsCalculator() {};

    Eigen::Matrix4f calcTransformMatrix(int32_t jointIdx);

    void calcCartesianCoord(double& x, double& y, double& z, int32_t jointIdx);


private:
    const RobotModel& m_robotModel;
};
