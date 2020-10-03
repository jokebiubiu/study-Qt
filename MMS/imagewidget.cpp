#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    //图片窗口控件初始化
    this->image_Label = new QLabel(this);
    this->image_Label->setFixedSize(400,370);
    this->image_Label->move(0,0);
    this->image_Choose_Btn = new QPushButton("choose",this);
    this->image_Next_Btn = new QPushButton("next",this);
    this->image_prev_Btn = new QPushButton("prev",this);
    this->image_Choose_Btn->move(500,100);
    this->image_prev_Btn->move(500,200);
    this->image_Next_Btn->move(500,300);

    connect(this->image_Choose_Btn,&QPushButton::clicked,this,&ImageWidget::chooseImageFile);
    connect(this->image_prev_Btn,&QPushButton::clicked,this,&ImageWidget::prevImage);
    connect(this->image_Next_Btn,&QPushButton::clicked,this,&ImageWidget::nextImage);
}

QStringList ImageWidget::getImageList(){
    //查询文件夹下所有图片
    QStringList images = {""};
    //选择目录
    QString dirurl = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "D:/",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(!dirurl.isEmpty())
    {
        //获取所有图片
        QDir dir(dirurl);
        dirurl = dir.fromNativeSeparators(dirurl); //将'\\'转'/'
        dir.setFilter(QDir::Files);
        dir.setSorting(QDir::Name);
        dir.setNameFilters(QString("*.jpg;*.jpeg;*.png").split(";"));
        images = dir.entryList();
        for(int i=0;i<images.size();i++){
            images[i] = dirurl+"/"+images[i];
        }
    }
    return images;
}

void ImageWidget::labelLoadImage(QString imageUrl){
    QImage img;
    if(img.load(imageUrl)){
        QSize size = this->image_Label->size();
        img = img.scaled(size,Qt::KeepAspectRatio); //图片按比例适应label尺寸
        this->image_Label->setPixmap(QPixmap::fromImage(img));
    }
}

void ImageWidget::chooseImageFile(){
    //选择图片文件夹
    this->imageList.clear();
    this->location = 0;
    this->imageList = getImageList();
    if(!this->imageList.isEmpty()){
        labelLoadImage(imageList.at(location));
    }
}
void ImageWidget::nextImage(){
    //下一张图片
    if(this->imageList.isEmpty()) return;
    this->location++;
    if(this->location >= this->imageList.size()) {
        this->location = 0;
    }
    labelLoadImage(this->imageList.at(location));
}
void ImageWidget::prevImage(){
    //上一张图片
    if(this->imageList.isEmpty()) return;
    this->location--;
    if(this->location < 0) {
        this->location = this->imageList.size() -1;
    }
    labelLoadImage(this->imageList.at(location));
}
