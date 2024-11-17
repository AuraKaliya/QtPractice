#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_showArea=new QScrollArea(this);
    m_showArea->setGeometry(0,0,this->width(),this->height());
    m_showArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_showArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_showArea->setFrameShape(QFrame::NoFrame);
    m_showWidget=new QWidget(m_showArea);
    m_showWidget->setWindowFlags(Qt::FramelessWindowHint);
    m_showWidget->move(0,0);

    m_widgetGroup<<this<<m_showArea<<m_showWidget;

    initWidget();
    toThumbnail();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initWidget()
{
    initRect(QRect(0,0,400,900),QRect(0,0,80,900));
    initCardSize(QSize(90,120),QSize(70,70));

    m_Hspacing=15;
    m_Vspacing=15;
    m_duration=300;
    for(int i=0;i<5;i++)
        {
            QLabel * tmpLabel=new QLabel(this);
            tmpLabel->setFixedSize(m_cardSize);
            tmpLabel->setStyleSheet("border-image:url(:/test_CharacterCardPix"+QString::number(i+1)+".png)");

            tmpLabel->move(30+(i%3)*(tmpLabel->width()+m_Hspacing),(50+(i/3)*(tmpLabel->height()+m_Vspacing)));

            m_labelGroup<<tmpLabel;
        }

    m_showArea->setGeometry(m_showRect);
    m_showWidget->adjustSize();
    adjustSize();
    m_nowStatues=true;
}

void Widget::initRect(QRect showRect, QRect hideRect)
{
    m_showRect=showRect;
    m_hideRect=hideRect;
}

void Widget::initCardSize(QSize cardSize, QSize cardSmallSize)
{
    m_cardSize=cardSize;
    m_cardSmallSize=cardSmallSize;

}

void Widget::toThumbnail()
{
    if(!m_nowStatues) return;

    QParallelAnimationGroup * aniGroup=new QParallelAnimationGroup();

    for(int i=0;i<m_labelGroup.size();i++)
    {
        QPropertyAnimation *animation =new QPropertyAnimation(m_labelGroup[i],"pos");
        m_labelGroup[i]->setFixedSize(m_cardSmallSize);
        m_labelGroup[i]->setStyleSheet("border-image:url(:/test_CharacterCardSmallPix"+QString::number(i+1)+".png)");
        animation->setDuration(m_duration);
        QObject::connect(animation,&QPropertyAnimation::finished,[this](){

        });
        animation->setStartValue( m_labelGroup[i]->pos());
        animation->setEndValue(QPoint(15,i*(m_cardSmallSize.height()+m_Vspacing)));
        aniGroup->addAnimation(animation);
    }

    for(auto it:m_widgetGroup)
    {
        QPropertyAnimation *animation =new QPropertyAnimation(it,"size");
        animation->setDuration(m_duration);
        QObject::connect(animation,&QPropertyAnimation::finished,[this](){

        });
        animation->setStartValue(it->size());
        animation->setEndValue(m_hideRect.size());
        aniGroup->addAnimation(animation);
    }

    QObject::connect(aniGroup,&QParallelAnimationGroup::finished,[this](){

        adjustSize();
        m_nowStatues=false;
        toDetail();

    });
    QObject::connect(aniGroup,&QParallelAnimationGroup::destroyed,[this](){

        adjustSize();

    });
    aniGroup->start(QAbstractAnimation::DeleteWhenStopped);

}

void Widget::toDetail()
{

   if(m_nowStatues) return;


    QParallelAnimationGroup * aniGroup=new QParallelAnimationGroup();

    for(int i=0;i<m_labelGroup.size();i++)
    {
        QPropertyAnimation *animation =new QPropertyAnimation(m_labelGroup[i],"pos");
        m_labelGroup[i]->setFixedSize(m_cardSize);
        m_labelGroup[i]->setStyleSheet("border-image:url(:/test_CharacterCardPix"+QString::number(i+1)+".png)");
        animation->setDuration(m_duration);
        QObject::connect(animation,&QPropertyAnimation::finished,[this](){

        });
        //m_detailLayout->addWidget( m_labelGroup[i],i,0);
        animation->setStartValue( m_labelGroup[i]->pos());
        animation->setEndValue(QPoint(30+(i%3)*(m_labelGroup[i]->width()+m_Hspacing),(50+(i/3)*(m_labelGroup[i]->height()+m_Vspacing))));
        aniGroup->addAnimation(animation);
    }
    for(auto it:m_widgetGroup)
    {
        QPropertyAnimation *animation =new QPropertyAnimation(it,"size");
         animation->setDuration(m_duration);
        QObject::connect(animation,&QPropertyAnimation::finished,[this](){

        });
         animation->setStartValue(it->size());
         animation->setEndValue(m_showRect.size());
         aniGroup->addAnimation(animation);
    }

    QObject::connect(aniGroup,&QParallelAnimationGroup::finished,[this](){

        m_nowStatues=true;

        toThumbnail();
    });
    QObject::connect(aniGroup,&QParallelAnimationGroup::stateChanged,[this](){

    });
    aniGroup->start(QAbstractAnimation::DeleteWhenStopped);



}

