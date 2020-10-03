#include "musicwidget.h"

MusicWidget::MusicWidget(QWidget *parent) : QWidget(parent)
{
    //音乐窗口控件初始化
    this->music_List_Widget = new QListWidget(this);
    this->music_List_Widget->setFixedSize(400,300);
    this->music_List_Widget->move(0,0);
    this->music_Choose_Btn = new QPushButton("choose",this);
    this->music_Next_Btn = new QPushButton("next",this);
    this->music_Prev_Btn = new QPushButton("prev",this);
    this->music_Play_Btn = new QPushButton("play",this);
    this->music_Choose_Btn->move(500,0);
    this->music_Prev_Btn->move(500,100);
    this->music_Next_Btn->move(500,200);
    this->music_Play_Btn->move(500,300);
    this->music_Play_List = new QMediaPlaylist(this);
    this->music_Player = new QMediaPlayer(this);
    this->music_Slider = new QSlider(this);
    this->music_Slider->setOrientation(Qt::Horizontal);
    this->music_Slider->setFixedWidth(300);
    this->music_Slider->setMinimum(0);
    this->music_Slider->setMaximum(100);
    this->music_Slider->setSingleStep(1);//滑条步长为1
    this->music_Slider->move(30,320);
    this->music_Slider->setCursor(QCursor(Qt::PointingHandCursor));
    this->music_Time = new QLabel("00:00/00:00",this);
    this->music_Time->move(350,320);
    this->music_Volume_Slider = new QSlider(this);
    this->music_Volume_Label = new QLabel(tr("000"),this);
    this->music_Volume_Slider->setOrientation(Qt::Vertical);
    this->music_Volume_Slider->setFixedWidth(10);
    this->music_Volume_Slider->setMinimum(0);
    this->music_Volume_Slider->setMaximum(100);
    this->music_Volume_Slider->setSingleStep(1);
    this->music_Volume_Slider->move(450,200);
    this->music_Volume_Slider->setCursor(QCursor(Qt::PointingHandCursor));
    this->music_Volume_Label->move(430,290);

    connect(this->music_Choose_Btn,&QPushButton::clicked,this,&MusicWidget::chooseMusicFile);
    connect(this->music_Next_Btn,&QPushButton::clicked,this,&MusicWidget::nextMusic);
    connect(this->music_Prev_Btn,&QPushButton::clicked,this,&MusicWidget::prevMusic);
    connect(this->music_Play_Btn,&QPushButton::clicked,this,&MusicWidget::playOrPause);
    connect(this->music_Player,&QMediaPlayer::positionChanged,this,&MusicWidget::changePosition);
    connect(this->music_Slider,&QSlider::sliderMoved,this,&MusicWidget::changePlayerPostition);
    connect(this->music_Volume_Slider,&QSlider::sliderMoved,this,&MusicWidget::changePlayerVolume);
    connect(this->music_Player,&QMediaPlayer::volumeChanged,this,&MusicWidget::changeVolume);
    connect(this->music_List_Widget,&QListWidget::itemClicked,this,&MusicWidget::clickListWidgetItem);
    connect(this->music_Play_List,&QMediaPlaylist::currentIndexChanged,this,&MusicWidget::changeListWidgetItemColor);

}

QStringList MusicWidget::getMusicList(){
    //返回歌曲路径列表
    QStringList musics = {""};
    //选择文件夹
    QString dirurl = QFileDialog::getExistingDirectory(this,tr("Open Directory"),
                                                       "D:/",
                                                       QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(dirurl.isEmpty()){
        qDebug()<<"Not find dirurl";
    }else{
        QDir dir(dirurl);
        dirurl = dir.fromNativeSeparators(dirurl); //将‘//’转 ‘/’
        dir.setFilter(QDir::Files);
        dir.setSorting(QDir::Name);
        dir.setNameFilters(QString("*.mp3").split(";"));
        musics = dir.entryList();
        for(int i = 0;i<musics.size();i++){
            musics[i] = dirurl + "/" + musics[i];
        }
    }
    return musics;
}

void MusicWidget::chooseMusicFile(){
    //选择音乐文件夹
    this->musicList.clear();//清空列表
    this->music_Play_List->clear();
    this->music_List_Widget->clear();
    this->musicList = getMusicList();
    // this->music_List_Widget->addItems(this->musicList);
    for(int i=0;i<this->musicList.size();i++){
        this->music_Play_List->addMedia(QUrl(this->musicList.at(i)));//添加音乐播放列表项
        QStringList list = this->musicList.at(i).split("/");//获取歌曲名
        list = list.at(list.size()-1).split(".");
        this->music_List_Widget->addItem(list.at(0));//将歌曲名添加到列表窗口
    }
    this->music_Play_List->setPlaybackMode(QMediaPlaylist::Loop); //列表循环播放
    this->music_Player->setPlaylist(this->music_Play_List);
    this->music_Player->play();
    int volume = this->music_Player->volume(); //获取音量
    this->music_Volume_Label->setText(QString::number(volume));
    this->music_Volume_Slider->setValue(volume);
    this->isPlay = true;
    this->music_Play_Btn->setText(tr("pause"));
}
void MusicWidget::nextMusic(){
    //下一首歌曲
    int currentIndex = this->music_Play_List->currentIndex();
    currentIndex++;
    if(currentIndex == this->musicList.size()){
        currentIndex = 0;
    }
    this->music_Play_List->setCurrentIndex(currentIndex);

}
void MusicWidget::prevMusic(){
    //上一首
    int currentIndex = this->music_Play_List->currentIndex();
    currentIndex--;
    if(currentIndex < 0) {
        currentIndex = this->musicList.size()-1;
    }
    this->music_Play_List->setCurrentIndex(currentIndex);
}
void MusicWidget::playOrPause(){
    //暂停\播放
    if(this->isPlay){
        this->isPlay = false;
        this->music_Player->pause();
        this->music_Play_Btn->setText(tr("play"));
    }else{
        this->isPlay = true;
        this->music_Player->play();
        this->music_Play_Btn->setText(tr("pause"));
    }
}
void MusicWidget::changePosition(qint64 position){
    //播放位置改变，更改时间，滑条位置
    this->music_Slider->setMaximum(this->music_Player->duration()/1000);
    this->music_Slider->setValue(position/1000);
    QTime moveTime(0,(position/60000)%60,(position/1000)%60);
    QTime time(0,(this->music_Player->duration()/60000)%60,(this->music_Player->duration()/1000)%60);
    this->music_Time->setText(moveTime.toString("mm:ss")+"/"+time.toString("mm:ss"));
}
void MusicWidget::changePlayerPostition(int position){
    //拖动滑条更改播放位置
    position = position*1000;
    this->music_Player->setPosition(position);
}
void MusicWidget::changePlayerVolume(int volume){
    //拖动音量滑条，改变音量
    this->music_Player->setVolume(volume);
}
void MusicWidget::changeVolume(int volume){//音量变化，更新显示
    this->music_Volume_Slider->setValue(volume);
    this->music_Volume_Label->setText(QString::number(volume));
}
void MusicWidget::clickListWidgetItem(QListWidgetItem *item){
    //点击列表播放
    this->music_Play_List->setCurrentIndex(this->music_List_Widget->row(item));
}
void MusicWidget::changeListWidgetItemColor(int position){
    //切歌时更新列表正在播放颜色
    QListWidgetItem *item = this->music_List_Widget->item(position);
    item->setSelected(true);
}
