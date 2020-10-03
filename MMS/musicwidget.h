#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QMediaPlayer>
#include<QSlider>
#include<QListWidget>
#include<QMediaPlaylist>
#include<QTime>
#include<QFileDialog>

class MusicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicWidget(QWidget *parent = nullptr);
    QStringList getMusicList(); //返回歌曲路径列表
    void chooseMusicFile();//选择音乐文件夹
    void nextMusic(); //下一首
    void prevMusic(); //上一首
    void playOrPause(); //播放\暂停
    void changePosition(qint64 position); //改变进度滑条和时间
    void changePlayerPostition(int position); //拖到滑条，更改播放位置
    void changePlayerVolume(int volume); //拖动音量滑条，改变音量
    void changeVolume(int volume);//音量变化，更新显示
    void clickListWidgetItem(QListWidgetItem *item); //点击列表播放
    void changeListWidgetItemColor(int position); //切歌时更新列表正在播放颜色
private:
    //音乐播放界面控件
    QPushButton *music_Choose_Btn; //选择音乐文件夹按钮
    QPushButton *music_Next_Btn; //下一首歌曲按钮
    QPushButton *music_Prev_Btn; //上一首歌曲按钮
    QPushButton *music_Play_Btn; //播放\暂停按钮
    QSlider *music_Slider; //歌曲播放进度滑条
    QSlider *music_Volume_Slider; //歌曲音量滑条
    QLabel *music_Volume_Label; //歌曲音量显示
    QLabel *music_Time; //歌曲时长显示
    QListWidget *music_List_Widget; //音乐列表窗口
    QStringList musicList; //歌曲路径列表
    bool isPlay; //播放状态
    QMediaPlayer *music_Player; //音乐播放
    QMediaPlaylist *music_Play_List; //音乐播放列表
signals:

};

#endif // MUSICWIDGET_H
