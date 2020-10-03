#ifndef MYWIDGET_H
#define MYWIDGET_H

#include<QTabWidget>
#include"imagewidget.h"
#include"musicwidget.h"
#include"videowidget.h"
class MyWidget : public QTabWidget
{
    Q_OBJECT

private:

    ImageWidget *imageWidget; //图片界面
    MusicWidget *musicWidget; //音乐界面
    VideoWidget *videoWidget; //视频界面

public:
    MyWidget(QTabWidget *parent = nullptr);
    ~MyWidget();
};
#endif // MYWIDGET_H
