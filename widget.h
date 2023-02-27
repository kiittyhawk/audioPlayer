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
    void setDefault();
    ~Widget();

private slots:
    void btnAddClicked();
    void btnPlay();
//    void btnPause();
    void btnNext();
    void btnPrev();
//    void btnStop();

private:
    Ui::Widget          *ui;
    QStandardItemModel  *_playlistModel;
    QMediaPlayer        *_player;
    QAudioOutput        *_audioOutput;
    LinkedList          _playlist;
    uint32_t            _index;
//    qint64              _pos;
    int                 _playState; // 1-play, 0-pause

//    QMediaPlaylist      *_playlist;
};

#endif // WIDGET_H
