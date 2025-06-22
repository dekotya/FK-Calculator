#include "../../include/gui/mainwindow.h"

#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(RobotModel& robotModel, QWidget *parent)
    : QMainWindow(parent),
    m_robotModel(robotModel),
    m_centralWidget(new QWidget(this)),
    m_Xpos(new QLabel("X pos: ", this)),
    m_Ypos(new QLabel("Y pos: ", this)),
    m_Zpos(new QLabel("Z pos: ", this))
{
    m_jointCnt = m_robotModel.jointCnt();
    m_jointGroupBoxes.resize(m_jointCnt);
    m_kinematicsCalc = std::make_unique<KinematicsCalculator>(robotModel);

    m_robotGlWidget = new RobotGLWidget(m_jointCnt, this);

    setupUi();
    setupConnections();
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi()
{
    setWindowTitle("FK Calculator");

    QHBoxLayout* mainLayout = new QHBoxLayout(m_centralWidget);
    QVBoxLayout* vbLayout = new QVBoxLayout();

    QGridLayout* jointsLayout = new QGridLayout();

    int row, column;

    for (int32_t i = 0; i < m_jointCnt; ++i) {

        row = i / 2;
        column = i % 2;

        m_jointGroupBoxes[i] = new JointGroupBox(QString("Joint %1:").arg(i + 1), this);

        m_jointGroupBoxes[i]->setTheta(m_robotModel.getTheta(i));
        m_jointGroupBoxes[i]->setA(m_robotModel.getA(i));
        m_jointGroupBoxes[i]->setD(m_robotModel.getD(i));
        m_jointGroupBoxes[i]->setAlpha(m_robotModel.getAlpha(i));

        jointsLayout->addWidget(m_jointGroupBoxes[i], row, column);
    }
    vbLayout->addLayout(jointsLayout);

    QLabel* resultsLabel = new QLabel("Results");

    QFont boldFont = resultsLabel->font();
    boldFont.setBold(true);
    resultsLabel->setFont(boldFont);
    resultsLabel->setAlignment(Qt::AlignCenter);

    boldFont.setBold(false);
    boldFont.setPointSize(boldFont.pointSize() + 4);

    m_Xpos->setAlignment(Qt::AlignCenter);
    m_Xpos->setFont(boldFont);
    m_Ypos->setAlignment(Qt::AlignCenter);
    m_Ypos->setFont(boldFont);
    m_Zpos->setAlignment(Qt::AlignCenter);
    m_Zpos->setFont(boldFont);

    vbLayout->addWidget(resultsLabel);
    vbLayout->addWidget(m_Xpos);
    vbLayout->addWidget(m_Ypos);
    vbLayout->addWidget(m_Zpos);

    mainLayout->addLayout(vbLayout, 1);
    mainLayout->addWidget(m_robotGlWidget, 3);

    mainLayout->setStretchFactor(vbLayout, 1);
    mainLayout->setStretchFactor(m_robotGlWidget, 3);

    setCentralWidget(m_centralWidget);

    m_robotGlWidget->setMinimumWidth(width() * 0.7);

    updateCartesianCoord();
}

void MainWindow::setupConnections()
{
    for (int32_t i = 0; i < m_jointCnt; i++)
    {
        connect(m_jointGroupBoxes[i], &JointGroupBox::thetaParamChanged, this, [this, i] (double value){
            m_robotModel.setTheta(i, value);
            updateCartesianCoord();
        });

        connect(m_jointGroupBoxes[i], &JointGroupBox::aParamChanged, this, [this, i] (double value){
            m_robotModel.setA(i, value);
            updateCartesianCoord();
        });

        connect(m_jointGroupBoxes[i], &JointGroupBox::dParamChanged, this, [this, i] (double value){
            m_robotModel.setD(i, value);
            updateCartesianCoord();
        });

        connect(m_jointGroupBoxes[i], &JointGroupBox::alphaParamChanged, this, [this, i] (double value){
            m_robotModel.setAlpha(i, value);
            updateCartesianCoord();
        });
    }
}

void MainWindow::updateCartesianCoord()
{
    double x, y, z;
    std::vector<QVector3D> jointPositions;

    for (int i = 0; i < m_jointCnt; i++)
    {
        m_kinematicsCalc->calcCartesianCoord(x, y, z, i);
        jointPositions.push_back(QVector3D(x, y, z));
    }

    m_robotGlWidget->updateJoints(jointPositions);

    //m_kinematicsCalc->calcCartesianCoord(x, y, z, m_jointCnt);

    m_Xpos->setText("X pos: " + QString::number(x, 'f', 6));
    m_Ypos->setText("Y pos: " + QString::number(y, 'f', 6));
    m_Zpos->setText("Z pos: " + QString::number(z, 'f', 6));
}
