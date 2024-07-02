#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QSlider>
#include <QSettings>
#include <QVariant>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_vlcInstance(nullptr)
    , m_vlc_media(nullptr)
    , m_vlc_mediaPlayer(nullptr)
    , m_isProgressSliderVisible(false)
    , m_videoWidget(nullptr)
    , m_progressSlider(nullptr)
{
    ui->setupUi(this);

    //创建并初始化libvlc实例
    m_vlcInstance = libvlc_new(0, nullptr);
    this->setWindowTitle("xxxx");

    QVBoxLayout *layout = ui->verticalLayout;
    m_videoWidget = new QWidget(this);
    layout->addWidget(m_videoWidget);

    m_progressSlider = new QSlider(Qt::Horizontal, this);
    layout->addWidget(m_progressSlider);

    // 在 MainWindow 构造函数中添加计时器来更新进度条
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainWindow::updateProgressBar);
    m_timer->start(1000); // 每秒更新一次

    // 连接进度条的拖动事件
    connect(m_progressSlider, &QSlider::sliderMoved, this, &MainWindow::setPosition);

    m_configPath = QDir::currentPath() + "/config/setting.ini";
    setAcceptDrops(true); // 允许窗口接受拖拽


}

MainWindow::~MainWindow()
{
    libvlc_media_player_release(m_vlc_mediaPlayer);
    libvlc_release(m_vlcInstance);
    delete ui;
}

void MainWindow::updateProgressBar()
{
    if (m_vlc_mediaPlayer && libvlc_media_player_is_playing(m_vlc_mediaPlayer))
    {
        float position = libvlc_media_player_get_position(m_vlc_mediaPlayer);
        m_progressSlider->setValue(position * 1000);
    }
}

void MainWindow::toggleFullScreen()
{
    if (isFullScreen())
    {
        showNormal();
        ui->menubar->show();
    }
    else
    {
        showFullScreen();
        ui->menubar->hide();
    }
}

QString MainWindow::getDataByKey(QString filePath, QString node, QString key)
{
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup(node);
    QString rVal = settings.value(key,"invalid").toString();
    settings.endGroup();
    return rVal;
}

void MainWindow::setDataByKey(QString filePath, QString node, QString key, QString value)
{
    QSettings settings(filePath, QSettings::IniFormat);
    settings.beginGroup(node);
    settings.setValue(key,value);
    settings.endGroup();
}

void MainWindow::playMedia(QString filename)
{
    std::replace(filename.begin(), filename.end(), QChar('/'), QChar('\\'));
    qDebug()<<"播放的媒体:"<<filename;

    /*为特定文件路径创建媒体*/
    if(m_vlc_media)
        libvlc_media_release(m_vlc_media);
    if(!m_vlcInstance)
        return;
    m_vlc_media = libvlc_media_new_path(m_vlcInstance, filename.toUtf8().data());
    if(m_vlc_media == nullptr)
    {
        qDebug()<<"libvlc_media_new_path 执行错误.";
        return;
    }

    /*根据给定的媒体对象创建一个播放器对象*/
    if(m_vlc_mediaPlayer)
        libvlc_media_player_release(m_vlc_mediaPlayer);

    m_vlc_mediaPlayer = libvlc_media_player_new_from_media(m_vlc_media);

    if(!m_vlc_mediaPlayer)
        return;
    /*设置给予媒体播放器媒体输出的win32/win64窗口句柄*/
    libvlc_media_player_set_hwnd(m_vlc_mediaPlayer, (void *)m_videoWidget->winId());

    /*播放媒体文件*/
    if(m_vlc_mediaPlayer)
        libvlc_media_player_play(m_vlc_mediaPlayer);
    setDataByKey(m_configPath,"currentPath","currentPath",filename);
}

void MainWindow::MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen())
    {
        showNormal();
        ui->menubar->show();
    }
    else if (event->key() == Qt::Key_F11)
    {
        toggleFullScreen();
    }
    QMainWindow::keyPressEvent(event);

}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }

}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty())
        {
            QString filePath = urlList.first().toLocalFile();
            if (filePath.endsWith(".mp4", Qt::CaseInsensitive))
            {
                playMedia(filePath);
            }
        }
    }
}

void MainWindow::on_pushButton_open_clicked()
{
    /*选择文件*/
    QString filePath = QDir::currentPath();
    QString filename = QFileDialog::getOpenFileName(this,"选择打开的文件",filePath,tr("*.*"));

    playMedia(filename);
}

void MainWindow::on_pushButton_pause_clicked()
{
    if(m_vlc_mediaPlayer)
        libvlc_media_player_pause(m_vlc_mediaPlayer);
}

void MainWindow::on_pushButton_stop_clicked()
{
    if(m_vlc_mediaPlayer)
        libvlc_media_player_stop(m_vlc_mediaPlayer);
}

void MainWindow::setPosition(int position)
{
    if (m_vlc_mediaPlayer)
    {
        libvlc_media_player_set_position(m_vlc_mediaPlayer, (float)position / 1000.0f);
    }
}
