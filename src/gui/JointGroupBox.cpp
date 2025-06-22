#include "../../include/gui/JointGroupBox.h"
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <cmath>

JointGroupBox::JointGroupBox(QString title, QWidget *parent)
    : QGroupBox(title, parent)
{
    m_alphaMap = {
        {0.0,      "0"},
        {M_PI_2,   "π/2"},
        {-M_PI_2,  "-π/2"},
        {M_PI,     "π"}
    };

    setupUi();
    setupConnections();
}

void JointGroupBox::setupUi()
{
    QGridLayout* mainLayout = new QGridLayout(this);

    mainLayout->addWidget(new QLabel("theta: ", this), 0, 0);

    m_sliderTheta = new QSlider(Qt::Orientation::Horizontal, this);
    m_sliderTheta->setMinimum(-360);
    m_sliderTheta->setMaximum(360);
    mainLayout->addWidget(m_sliderTheta, 0, 1);

    m_spinBoxTheta = new QDoubleSpinBox(this);
    m_spinBoxTheta->setRange(-360, 360);
    m_spinBoxTheta->setDecimals(3);
    m_spinBoxTheta->setSingleStep(1.);
    mainLayout->addWidget(m_spinBoxTheta, 0, 2);

    mainLayout->addWidget(new QLabel("a: ", this), 1, 0);

    m_spinBoxA = new QDoubleSpinBox(this);
    m_spinBoxA->setRange(-2, 2);
    m_spinBoxA->setDecimals(3);
    m_spinBoxA->setSingleStep(0.01);
    mainLayout->addWidget(m_spinBoxA, 1, 1);

    mainLayout->addWidget(new QLabel("d: ", this), 2, 0);

    m_spinBoxD = new QDoubleSpinBox(this);
    m_spinBoxD->setRange(-1., 1.);
    m_spinBoxD->setDecimals(3);
    m_spinBoxD->setSingleStep(0.01);
    mainLayout->addWidget(m_spinBoxD, 2, 1);

    mainLayout->addWidget(new QLabel("alpha: ", this), 3, 0);

    m_comboBoxAlpha = new QComboBox(this);
    for (auto it = m_alphaMap.begin(); it != m_alphaMap.end(); ++it) {
        m_comboBoxAlpha->addItem(it.value(), it.key());
    }

    mainLayout->addWidget(m_comboBoxAlpha, 3, 1);
}

void JointGroupBox::setupConnections()
{
    connect(m_sliderTheta, &QSlider::valueChanged, this, [this] (int value){
        m_spinBoxTheta->blockSignals(true);
        m_spinBoxTheta->setValue(value);
        m_spinBoxTheta->blockSignals(false);

        emit thetaParamChanged(static_cast<double>(value));
    });
    connect(m_spinBoxTheta, &QDoubleSpinBox::valueChanged, this, [this] (double value){
        m_sliderTheta->blockSignals(true);
        m_sliderTheta->setValue(static_cast<int>(value));
        m_sliderTheta->blockSignals(false);

        emit thetaParamChanged(value);
    });

    connect(m_spinBoxA, &QDoubleSpinBox::valueChanged, this, [this] (double value){
        emit aParamChanged(value);
    });

    connect(m_spinBoxD, &QDoubleSpinBox::valueChanged, this, [this] (double value){
        emit dParamChanged(value);
    });

    connect(m_comboBoxAlpha, &QComboBox::currentIndexChanged, this, [this] (int index){
        double alphaValue = m_comboBoxAlpha->itemData(index).toDouble();
        emit alphaParamChanged(alphaValue);
    });
}

void JointGroupBox::setTheta(double thetaValue)
{
    m_spinBoxTheta->setValue(thetaValue);
}

void JointGroupBox::setA(double aValue)
{
    m_spinBoxA->setValue(aValue);
}

void JointGroupBox::setD(double dValue)
{
    m_spinBoxD->setValue(dValue);
}

void JointGroupBox::setAlpha(double alphaValue)
{
    if (m_alphaMap.find(alphaValue) != m_alphaMap.end())
        m_comboBoxAlpha->setCurrentText(m_alphaMap[alphaValue]);
}
