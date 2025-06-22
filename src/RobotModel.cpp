#include "../include/RobotModel.h"

RobotModel::RobotModel(int32_t jointCnt, QObject* parent)
    : QObject(parent),
    m_jointCnt(jointCnt),
    m_joints(jointCnt)
{

}

int32_t RobotModel::jointCnt() const
{
    return m_jointCnt;
}

void RobotModel::isIdxValid(int32_t jointIndex) const
{
    if (jointIndex >= m_jointCnt || jointIndex < 0)
    {
        std::string errorMsg = "Invalid value: " + std::to_string(jointIndex) + " >= " + std::to_string(m_jointCnt)
            + " || "  + std::to_string(jointIndex) + " < 0";
        throw std::invalid_argument(errorMsg);
    }
}

double RobotModel::getTheta(int32_t jointIndex) const
{
    isIdxValid(jointIndex);

    return m_joints[jointIndex].theta;
}

double RobotModel::getA(int32_t jointIndex) const
{
    isIdxValid(jointIndex);

    return m_joints[jointIndex].a;
}

double RobotModel::getD(int32_t jointIndex) const
{
    isIdxValid(jointIndex);

    return m_joints[jointIndex].d;
}

double RobotModel::getAlpha(int32_t jointIndex) const
{
    isIdxValid(jointIndex);

    return m_joints[jointIndex].alpha;
}

DHJoint RobotModel::getJointParams(int32_t jointIndex) const
{
    isIdxValid(jointIndex);

    return m_joints[jointIndex];
}

void RobotModel::setTheta(int32_t jointIndex, double thetaDegrees)
{
    isIdxValid(jointIndex);

    m_joints[jointIndex].theta = thetaDegrees;
}

void RobotModel::setA(int32_t jointIndex, double a)
{
    isIdxValid(jointIndex);

    m_joints[jointIndex].a = a;
}

void RobotModel::setD(int32_t jointIndex, double d)
{
    isIdxValid(jointIndex);

    m_joints[jointIndex].d = d;
}

void RobotModel::setAlpha(int32_t jointIndex, double alphaRadians)
{
    isIdxValid(jointIndex);

    m_joints[jointIndex].alpha = alphaRadians;
}

void RobotModel::setJointParams(int32_t jointIndex, const DHJoint& params)
{
    isIdxValid(jointIndex);

    m_joints[jointIndex] = params;
}

void RobotModel::setAllJointsParams(int32_t jointCnt, const std::vector<DHJoint>& params)
{
    if (jointCnt != m_jointCnt)
    {
        std::string errorMsg = std::to_string(jointCnt) + " != " + std::to_string(m_jointCnt);
        throw std::invalid_argument(errorMsg);
    }

    m_joints = params;
}
