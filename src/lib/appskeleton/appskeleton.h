#ifndef APPSKELETON_H
#define APPSKELETON_H

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QMutex>

#include "appskeleton_gloabal.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AppSkeleton;
}
QT_END_NAMESPACE

class APPSKELETON_EXPORT AppSkeleton : public QMainWindow
{
    Q_OBJECT

public:
    static AppSkeleton & getInstance();
    AppSkeleton(QWidget * parent = nullptr);
    ~AppSkeleton();
    QGridLayout * getLayout();

private:
    Ui::AppSkeleton * ui;
    static QMutex     m_mutex;
};
#endif
