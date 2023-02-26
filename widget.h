#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "LinkedList.h"
//#include <QMediaPlaylist>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void btnAddClicked();
    void btnPlay();
    void btnPause();

private:
    Ui::Widget          *ui;
    QStandardItemModel  *_playlistModel;
    QMediaPlayer        *_player;
    QAudioOutput        *_audioOutput;
    LinkedList          _playlist;

//    QMediaPlaylist      *_playlist;
};

#endif // WIDGET_H
