/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *horizontalLayoutWidget;
    QGridLayout *gridLayout;
    QToolButton *btnPlay;
    QToolButton *btnPrev;
    QToolButton *btnNext;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableView *playlistView;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QToolButton *btnAdd;
    QSlider *verticalSlider;
    QLabel *label;
    QWidget *gridLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *currentTime;
    QSlider *playingTrack;
    QLabel *endTime;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(601, 480);
        horizontalLayoutWidget = new QWidget(Widget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(80, 350, 441, 61));
        gridLayout = new QGridLayout(horizontalLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btnPlay = new QToolButton(horizontalLayoutWidget);
        btnPlay->setObjectName("btnPlay");
        btnPlay->setMinimumSize(QSize(100, 50));

        gridLayout->addWidget(btnPlay, 0, 1, 1, 1);

        btnPrev = new QToolButton(horizontalLayoutWidget);
        btnPrev->setObjectName("btnPrev");
        btnPrev->setMinimumSize(QSize(100, 50));

        gridLayout->addWidget(btnPrev, 0, 0, 1, 1);

        btnNext = new QToolButton(horizontalLayoutWidget);
        btnNext->setObjectName("btnNext");
        btnNext->setMinimumSize(QSize(100, 50));

        gridLayout->addWidget(btnNext, 0, 2, 1, 1);

        verticalLayoutWidget = new QWidget(Widget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 10, 581, 271));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        playlistView = new QTableView(verticalLayoutWidget);
        playlistView->setObjectName("playlistView");

        verticalLayout->addWidget(playlistView);

        verticalLayoutWidget_2 = new QWidget(Widget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(80, 410, 441, 52));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnAdd = new QToolButton(verticalLayoutWidget_2);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setMinimumSize(QSize(375, 50));

        verticalLayout_2->addWidget(btnAdd, 0, Qt::AlignHCenter);

        verticalSlider = new QSlider(Widget);
        verticalSlider->setObjectName("verticalSlider");
        verticalSlider->setGeometry(QRect(560, 290, 18, 160));
        verticalSlider->setOrientation(Qt::Vertical);
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(540, 450, 50, 20));
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(80, 300, 441, 30));
        horizontalLayout = new QHBoxLayout(gridLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        currentTime = new QLabel(gridLayoutWidget);
        currentTime->setObjectName("currentTime");

        horizontalLayout->addWidget(currentTime);

        playingTrack = new QSlider(gridLayoutWidget);
        playingTrack->setObjectName("playingTrack");
        playingTrack->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(playingTrack);

        endTime = new QLabel(gridLayoutWidget);
        endTime->setObjectName("endTime");

        horizontalLayout->addWidget(endTime);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        btnPlay->setText(QCoreApplication::translate("Widget", "play", nullptr));
        btnPrev->setText(QCoreApplication::translate("Widget", "prev", nullptr));
        btnNext->setText(QCoreApplication::translate("Widget", "next", nullptr));
        btnAdd->setText(QCoreApplication::translate("Widget", "add", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Volume", nullptr));
        currentTime->setText(QCoreApplication::translate("Widget", "00:00", nullptr));
        endTime->setText(QCoreApplication::translate("Widget", "00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
