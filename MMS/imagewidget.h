#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include<QFileDialog>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

    QStringList getImageList(); //返回图片列表
    void labelLoadImage(QString imageUrl); //imageLabel显示图片
    void chooseImageFile(); //选择图片文件夹
    void nextImage();//下一张图片
    void prevImage();//上一张图片

private:
    //图片界面控件
    QPushButton *image_Choose_Btn; //选择图片文件夹按钮
    QPushButton *image_Next_Btn; //下一张图片按钮
    QPushButton *image_prev_Btn; //上一张图片按钮
    QLabel *image_Label; //显示图片label
    QStringList imageList; //图片列表
    qint64 location; //当前图片在列表位置

signals:


};

#endif // IMAGEWIDGET_H
