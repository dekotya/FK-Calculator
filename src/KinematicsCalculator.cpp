#include "../include/KinematicsCalculator.h"
#include <cmath>

KinematicsCalculator::KinematicsCalculator(const RobotModel& robotModel)
    : m_robotModel(robotModel)
{
}

Eigen::Matrix4f KinematicsCalculator::calcTransformMatrix(int32_t jointIdx)
{
    Eigen::Matrix4f matrixT;

    DHJoint joint = m_robotModel.getJointParams(jointIdx);

    float cosTheta = cos(joint.theta * (M_PI / 180.0));
    float sinTheta = sin(joint.theta * (M_PI / 180.0));
    float cosAlpha = cos(joint.alpha);
    float sinAlpha = sin(joint.alpha);

    matrixT << cosTheta, -sinTheta * cosAlpha,  sinTheta * sinAlpha, joint.a * cosTheta,
               sinTheta,  cosTheta * cosAlpha, -cosTheta * sinAlpha, joint.a * sinTheta,
               0,         sinAlpha,             cosAlpha,            joint.d,
               0,         0,                    0,                   1;

    return matrixT;
}

void KinematicsCalculator::calcCartesianCoord(double& x, double& y, double& z, int32_t jointIdx)
{
    Eigen::Matrix4f matrixT = calcTransformMatrix(0);

    for (int i = 1; i <= jointIdx; i++)
    {
        matrixT *= calcTransformMatrix(i);
    }

    x = matrixT(0, 3);
    y = matrixT(1, 3);
    z = matrixT(2, 3);
}
