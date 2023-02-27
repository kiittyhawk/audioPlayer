#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    _playlistModel = new QStandardItemModel(this);
    ui->playlistView->setModel(_playlistModel);
    _playlistModel->setHorizontalHeaderLabels(QStringList() << tr("Audio Track") << tr("File Path"));
//    ui->playlistView->hideColumn(1);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);

    _player = new QMediaPlayer(this);
    _audioOutput = new QAudioOutput();
    _player->setAudioOutput(_audioOutput);
    _index = 0;
//    _pos = -1;
    _playState = -1;

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
    connect(ui->btnPlay, SIGNAL(clicked()), this, SLOT(btnPlay()));
//    connect(ui->btnPause, SIGNAL(clicked()), this, SLOT(btnPause()));
    connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(btnNext()));
    connect(ui->btnPrev, SIGNAL(clicked()), this, SLOT(btnPrev()));
//    connect(ui->btnStop, SIGNAL(clicked()), this, SLOT(btnStop()));
//    connect(ui->playlistView, SIGNAL(doubleClicked()), this, SLOT(btn));

    if (_player->position() == _player->duration() && _player->duration() > 0 &&
            _playlistModel->rowCount() > 0 && _playState == 1)
    {
//        if (!_playlist[_index + 1]) return;
//        _index++;
//        _pos = -1;
//        _player->setSource(QUrl::fromLocalFile(_playlist[_index]->item.path));
//    //    _player->duration() = _playlist[_index]->item.duration;
//        _audioOutput->setVolume(50);
//        _player->play();
        if (!_playlist[_index + 1])
        {
            _index = 0;
            setDefault();
            btnPlay();
        }
        else
            btnNext();
    }
}

Widget::~Widget()
{
    delete ui;
    delete _player;
    delete _playlistModel;
    delete _audioOutput;
}

void Widget::setDefault()
{
    ui->btnPlay->setText("Pause");
    _playState = -1;
}

void Widget::btnPlay()
{
    if (!_playlist[_index]) return;

    if (_playState == -1)
    {
        _player->setSource(QUrl::fromLocalFile(_playlist[_index]->item.path));
        _playState = 0;
    }
    switch (_playState)
    {
        case 0:
        //    _player->duration() = _playlist[_index]->item.duration;
            _audioOutput->setVolume(50);
            ui->btnPlay->setText("Pause");
            _playState = 1;
            _player->play();
            qDebug() << _player->duration() << _player->position();
            break;

        case 1:
        //    std::cout << _player->position() << _pos << std::endl;
            _player->pause();
            _playState = 0;
            ui->btnPlay->setText("Play");
            break;

        default:
            qWarning("Это не должно так работать");
            break;
    }
}

void Widget::btnNext()
{
    if (!_playlist[_index + 1]) return;
    _index++;
//    _pos = -1;
//    _player->setSource(QUrl::fromLocalFile(_playlist[_index]->item.path));
//    _player->duration() = _playlist[_index]->item.duration;
//    _audioOutput->setVolume(50);
//    _player->play();
    setDefault();
    btnPlay();
//    qDebug() << _player->errorString() << _playlistModel->rowCount();
}

void Widget::btnPrev()
{
    if (!_playlist[_index - 1]) return;
    _index--;
//    _pos = -1;
//    _player->setSource(QUrl::fromLocalFile(_playlist[_index]->item.path));
//    _player->duration() = _playlist[_index]->item.duration;
//    _audioOutput->setVolume(50);
//    _player->play();
    setDefault();
    btnPlay();
//    qDebug() << _player->errorString() << _playlistModel->rowCount();
}

//void Widget::btnStop()
//{
//    if (!_playlist[_index]) return;
////    _index--;
////    _pos = -1;
////    _player->setSource(QUrl::fromLocalFile(_playlist[_index]->item.path));
////    _player->duration() = _playlist[_index]->item.duration;
////    _audioOutput->setVolume(50);
////    _player->play();
////    setDefault();
////    btnPlay();
//    ui->btnPlay->setText("Play");
//    _index = 0;
//    _playState = -1;
//    _player->stop();
////    qDebug() << _player->errorString() << _playlistModel->rowCount();
//}

//void Widget::btnPause()
//{
//    if (!_playlist[_index]) return;
//    _pos = _player->position();
////    std::cout << _player->position() << _pos << std::endl;
//    _player->pause();
//    qDebug() << _player->errorString();
//}

void Widget::btnAddClicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"), QString(), tr("Audio Files (*.mp3)"));
    foreach (QString filepath, files)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filepath).dirName()));
        items.append(new QStandardItem(filepath));
        _playlistModel->appendRow(items);
        _playlist.push_back(QDir(filepath).absolutePath(), 30);
    }
}
