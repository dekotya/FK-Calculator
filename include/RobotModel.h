#pragma once
#include <QObject>

struct DHJoint {

    double theta;
    double a;
    double d;
    double alpha;

    DHJoint()
    {
        theta = 0;
        a = 0;
        d = 0;
        alpha = 0;
    }

    DHJoint(double a1, double a2, double a3, double a4)
        : theta(a1), a(a2), d(a3), alpha(a4) {}
};

class RobotModel : public QObject
{
    Q_OBJECT

public:
    explicit RobotModel(int32_t jointCnt, QObject* parent = nullptr);

    int32_t jointCnt() const;

    double getTheta(int32_t jointIndex) const;
    double getA(int32_t jointIndex) const;
    double getD(int32_t jointIndex) const;
    double getAlpha(int32_t jointIndex) const;
    DHJoint getJointParams(int32_t jointIndex) const;

    void setTheta(int32_t jointIndex, double thetaDegrees);
    void setA(int32_t jointIndex, double a);
    void setD(int32_t jointIndex, double d);
    void setAlpha(int32_t jointIndex, double alphaRadians);

    void setJointParams(int32_t jointIndex, const DHJoint& params);
    void setAllJointsParams(int32_t jointCnt, const std::vector<DHJoint>& params);

private:

    void isIdxValid(int32_t jointIndex) const;

    std::vector<DHJoint> m_joints;
    int32_t m_jointCnt;
};
