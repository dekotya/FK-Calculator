#pragma once
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QComboBox>

class JointGroupBox : public QGroupBox
{
    Q_OBJECT
public:

    JointGroupBox(QString title = "", QWidget *parent = nullptr);

    void setTheta(double thetaValue);
    void setA(double aValue);
    void setD(double dValue);
    void setAlpha(double alphaValue);

signals:
    void thetaParamChanged(double thetaValue);
    void aParamChanged(double thetaValue);
    void dParamChanged(double thetaValue);
    void alphaParamChanged(double thetaValue);

private:

    void setupUi();
    void setupConnections();

    QSlider* m_sliderTheta;
    QDoubleSpinBox* m_spinBoxTheta;

    QDoubleSpinBox* m_spinBoxA;

    QDoubleSpinBox* m_spinBoxD;

    QComboBox* m_comboBoxAlpha;
    QMap<double, QString> m_alphaMap; // Хранит соответствия
};
