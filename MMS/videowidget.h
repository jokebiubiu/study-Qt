#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QMediaPlayer>
#include<QSlider>
#include<QLabel>
#include<QFileDialog>
#include<QTime>
#include<QVideoWidget>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);
     QString getVideoUrl();//返回视频路径
     void chooseVideo();//选择mp4文件
     void playOrPause();//播放\暂停
     void changePosition(qint64 position);//改变进度滑条位置，时间显示
     void changePlayerPosition(int position);//拖动进度滑条，改变播放位置
     void changeVolume(int volume); //改变音量显示
     void changePlayerVolume(int volume); //拖动音量滑条，更改音量
     void changeState(QMediaPlayer::State state); //检测播放状态，结束则重新播放
private:
    //MP4播放界面控件
    QPushButton *video_Choose_Btn; //视频选择按钮
    QPushButton *video_Play_Btn; //视频播放\暂停按钮
    QLabel *video_Time; //视频时长显示
    QVideoWidget *video_Play_Widget; //视频窗口
    QSlider *video_Slider; //视频进度滑条
    QMediaPlayer *video_Player; //视频播放
    bool video_play; //视频播放状态
    QSlider *video_Volume_Slider; //视频音量滑条
    QLabel *video_Volume_Label; //视频音量显示
signals:

};

#endif // VIDEOWIDGET_H
