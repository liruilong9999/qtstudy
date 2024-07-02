#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <vlc.h>

class QSlider;
class QKeyEvent ;
class QDragEnterEvent ;
class QDropEvent;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateProgressBar();
    void toggleFullScreen();
    QString getDataByKey(QString filePath, QString node, QString key);
    void setDataByKey(QString filePath, QString node, QString key, QString value);
    void playMedia(QString filePath);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_stop_clicked();

    void setPosition(int position);

private:
    Ui::MainWindow *ui;

    libvlc_instance_t     * m_vlcInstance; //连接vlc库的全局配置
    libvlc_media_t        * m_vlc_media; //文件
    libvlc_media_player_t * m_vlc_mediaPlayer;//播放控制
    QTimer                * m_timer;
    bool                    m_isProgressSliderVisible;
    QWidget               * m_videoWidget;//播放窗口
    QSlider               * m_progressSlider;//进度条
    QString m_configPath;
};
#endif // MAINWINDOW_H
