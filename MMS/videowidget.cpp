#include "videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
    //视频窗口控件初始化
    this->video_Choose_Btn = new QPushButton(tr("choose"),this);
    this->video_Play_Btn = new QPushButton(tr("play"),this);
    this->video_Time = new QLabel(tr("00:00/00:00"),this);
    this->video_Slider = new QSlider(this);
    this->video_Play_Widget = new QVideoWidget(this);
    this->video_Play_Widget->setFixedSize(400,300);
    this->video_Slider->setFixedWidth(300);
    this->video_Play_Widget->move(50,0);
    this->video_Choose_Btn->move(100,330);
    this->video_Play_Btn->move(200,330);
    this->video_Slider->move(50,310);
    this->video_Time->move(370,310);
    this->video_Slider->setOrientation(Qt::Horizontal);
    this->video_Slider->setMinimum(0);
    this->video_Slider->setMaximum(100);
    this->video_Slider->setSingleStep(1);
    this->video_Slider->setCursor(QCursor(Qt::PointingHandCursor));
    this->video_Player = new QMediaPlayer(this);
    this->video_Player->setVideoOutput(this->video_Play_Widget);
    this->video_Volume_Label = new QLabel("000",this);
    this->video_Volume_Label->move(480,290);
    this->video_Volume_Slider = new QSlider(this);
    this->video_Volume_Slider->setOrientation(Qt::Vertical);
    this->video_Volume_Slider->setFixedWidth(10);
    this->video_Volume_Slider->setMinimum(0);
    this->video_Volume_Slider->setMaximum(100);
    this->video_Volume_Slider->setSingleStep(1);
    this->video_Volume_Slider->setCursor(QCursor(Qt::PointingHandCursor));
    this->video_Volume_Slider->move(500,200);

    connect(this->video_Choose_Btn,&QPushButton::clicked,this,&VideoWidget::chooseVideo);
    connect(this->video_Play_Btn,&QPushButton::clicked,this,&VideoWidget::playOrPause);
    connect(this->video_Player,&QMediaPlayer::positionChanged,this,&VideoWidget::changePosition);
    connect(this->video_Slider,&QSlider::sliderMoved,this,&VideoWidget::changePlayerPosition);
    connect(this->video_Player,&QMediaPlayer::volumeChanged,this,&VideoWidget::changeVolume);
    connect(this->video_Volume_Slider,&QSlider::sliderMoved,this,&VideoWidget::changePlayerVolume);
    connect(this->video_Player,&QMediaPlayer::stateChanged,this,&VideoWidget::changeState);
}

QString VideoWidget::getVideoUrl(){
    //返回视频路径
    QString videoUrl = "";
    //选择文件
    videoUrl = QFileDialog::getOpenFileName(this,tr("open video file"),
                                            "D:/",
                                            tr("videos (*.mp4)"));
    return videoUrl;
}

void VideoWidget::chooseVideo(){
    //选择mp4文件
    QString videoUrl = getVideoUrl();
    this->video_Player->setMedia(QUrl::fromLocalFile(videoUrl));
    this->video_Player->play();
    this->video_play = true;
    this->video_Play_Btn->setText(tr("pause"));
    this->video_Volume_Slider->setValue(this->video_Player->volume());
    this->video_Volume_Label->setText(QString::number(this->video_Player->volume()));
}
void VideoWidget::playOrPause(){
    //播放\暂停
    if(this->video_play) {
        this->video_play = false;
        this->video_Player->pause();
        this->video_Play_Btn->setText(tr("play"));
    }else{
        this->video_play = true;
        this->video_Player->play();
        this->video_Play_Btn->setText(tr("pause"));
    }
}

void VideoWidget::changePosition(qint64 position){
    //改变进度滑条位置，时间显示
    this->video_Slider->setMaximum(this->video_Player->duration()/1000);
    this->video_Slider->setValue(position/1000);
    QTime moveTime(0,(position/60000)%60,(position/1000)%60);
    QTime time(0,(this->video_Player->duration()/60000)%60,(this->video_Player->duration()/1000)%60);
    this->video_Time->setText(moveTime.toString("mm:ss")+"/"+time.toString("mm:ss"));
}
void VideoWidget::changePlayerPosition(int position){
    //拖动进度滑条，改变播放位置
    position = position*1000;
    this->video_Player->setPosition(position);
}
void VideoWidget::changeVolume(int volume){
    //改变音量显示
    this->video_Volume_Label->setText(QString::number(volume));
    this->video_Volume_Slider->setValue(volume);
}
void VideoWidget::changePlayerVolume(int volume){
    //拖动音量滑条，更改音量
    this->video_Player->setVolume(volume);
}
void VideoWidget::changeState(QMediaPlayer::State state){
    //检测播放状态，结束则重新播放
    if(state == QMediaPlayer::StoppedState) {
        this->video_Player->play();
    }
}
