#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "LinkedList.h"
#include <QDebug>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void setDefault();
    void addDefaultTracks();

    ~Widget();

private slots:
    void btnAddClicked();
    void btnPlay();
    void btnNext();
    void btnPrev();
    void setVolume(int value);
    void audioLoop(QMediaPlayer::MediaStatus status);
    void setAudio(QModelIndex index);
    void durationEmul();

private:
    Ui::Widget          *ui;
    QStandardItemModel  *_playlistModel;
    QMediaPlayer        *_player;
    QAudioOutput        *_audioOutput;
    QTimer              *_timer;
    LinkedList          _playlist;
    uint32_t            _index;
    int                 _playState; // 1-play, 0-pause
};

#endif // WIDGET_H
