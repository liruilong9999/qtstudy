

#include "appskeleton.h"
#include "ui_appskeleton.h"

QMutex AppSkeleton::m_mutex;

AppSkeleton & AppSkeleton::getInstance()
{
    QMutexLocker locker(&m_mutex);

    static AppSkeleton instance;
    return instance;
}

AppSkeleton::AppSkeleton(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::AppSkeleton)
{
    ui->setupUi(this);
    setWindowTitle(QStringLiteral("地图软件"));
}

AppSkeleton::~AppSkeleton()
{
    delete ui;
}

QGridLayout * AppSkeleton::getLayout()
{
    return ui->gridLayout;
}
