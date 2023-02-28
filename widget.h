#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "LinkedList.h"
#include <QDebug>

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
    void btnNext();
    void btnPrev();
    void setVolume(int value);
    void audioLoop(QMediaPlayer::MediaStatus status);
    void setAudio(QModelIndex index);

private:
    Ui::Widget          *ui;
    QStandardItemModel  *_playlistModel;
    QMediaPlayer        *_player;
    QAudioOutput        *_audioOutput;
    LinkedList          _playlist;
    uint32_t            _index;
    int                 _playState; // 1-play, 0-pause
};

#endif // WIDGET_H
