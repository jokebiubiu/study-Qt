#include "mywidget.h"

MyWidget::MyWidget(QTabWidget *parent)
    : QTabWidget(parent)
{

    this->imageWidget = new ImageWidget(this);
    this->musicWidget = new MusicWidget(this);
    this->videoWidget = new VideoWidget(this);
    this->addTab(this->imageWidget,"image");
    this->addTab(this->musicWidget,"music");
    this->addTab(this->videoWidget,"video");
    this->setWindowTitle("MMS");
    this->setFixedSize(600,400); //固定窗口大小
}

MyWidget::~MyWidget()
{

}






