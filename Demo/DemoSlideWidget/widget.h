#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSize>
#include <QRect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QGridLayout>
#include <QVector>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initWidget();
    void initRect(QRect showRect,QRect hideRect);
    void initCardSize(QSize cardSize,QSize cardSmallSize);

protected:
    void keyPressEvent(QKeyEvent*e)override;
public slots:
    void toThumbnail();
    void toDetail();

private:
    QScrollArea *m_showArea;
    QWidget * m_showWidget;
    QVector<QLabel*> m_labelGroup;
    QVector<QLabel*> m_detailLabelGroup;
    QVector<QWidget*>m_widgetGroup;
    bool m_nowStatues;
    QGridLayout * m_detailLayout;
    QGridLayout * m_thumbnailLayout;

    QRect m_showRect;
    QRect m_hideRect;
    QSize m_cardSize;
    QSize m_cardSmallSize;

    int m_Hspacing;
    int m_Vspacing;
    int m_duration;

};
#endif // WIDGET_H
