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
    ui->playlistView->hideColumn(1);
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistView->setContextMenuPolicy(Qt::CustomContextMenu);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setWindowTitle("Audio Player");
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);
    ui->verticalSlider->setMinimum(0);
    ui->verticalSlider->setMaximum(100);
    ui->verticalSlider->setValue(30);
    ui->playingTrack->setTickInterval(1);


    _player = new QMediaPlayer(this);
    _audioOutput = new QAudioOutput();

    _player->setAudioOutput(_audioOutput);
    _audioOutput->setVolume(0.3f);
    _index = 0;
    _playState = -1;
    addDefaultTracks();

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(durationEmul()));
    _timer->start(1000);

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
    connect(ui->btnPlay, SIGNAL(clicked()), this, SLOT(btnPlay()));
    connect(ui->btnNext, SIGNAL(clicked()), this, SLOT(btnNext()));
    connect(ui->btnPrev, SIGNAL(clicked()), this, SLOT(btnPrev()));
    connect(ui->verticalSlider, SIGNAL(sliderMoved(int)), this, SLOT(setVolume(int)));
    connect(_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(audioLoop(QMediaPlayer::MediaStatus)));
    connect(ui->playlistView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(setAudio(QModelIndex)));

}

Widget::~Widget()
{
    delete ui;
    delete _player;
    delete _playlistModel;
    delete _audioOutput;
    delete _timer;
}

QString convertTime(qint64 seconds)
{
    QString min = QString::number(seconds / 60);
    QString sec = QString::number(seconds % 60);
    if ((seconds / 60) >= 0 && (seconds / 60) < 10)
        min = "0" + min;
    if ((seconds % 60) >= 0 && (seconds % 60) < 10)
        sec = "0" + sec;
    return (min + ":" + sec);
}

void Widget::durationEmul()
{
    if (!_playlist[_index] || _index == (uint32_t)-1) return;

    ui->playingTrack->setMaximum(_player->duration()/1000);
    ui->playingTrack->setValue((int)_player->position()/1000);
    ui->currentTime->setText(convertTime(_player->position()/1000));
    ui->endTime->setText(convertTime(_player->duration()/1000));
}

void Widget::setVolume(int value)
{
    if (_audioOutput->volume() == (float)value) return;
    _audioOutput->setVolume((float)value / 100);
}

void Widget::audioLoop(QMediaPlayer::MediaStatus status)
{

    if (status == QMediaPlayer::EndOfMedia)
    {
        if (!_playlist[_index + 1])
        {
            ui->btnPlay->setText("Play");
            _playState = -1;
        }
        btnNext();
    }
}

void Widget::setAudio(QModelIndex index)
{
    if (index.isValid())
    {
        _index = index.row();
        setDefault();
        btnPlay();
    }
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
        ui->playlistView->selectRow(_index);

    }
    switch (_playState)
    {
        case 0:

            ui->btnPlay->setText("Pause");
            _playState = 1;
            _player->play();

            break;

        case 1:
            _player->pause();
            _playState = 0;
            ui->btnPlay->setText("Play");

            break;

        default:
            qWarning("?????? ???? ???????????? ?????? ????????????????");
            break;
    }
}

void Widget::btnNext()
{
    if (!_playlist[_index + 1])
        return;
    _index++;
    setDefault();
    btnPlay();
}

void Widget::btnPrev()
{
    if (!_playlist[_index - 1]) return;
    _index--;
    setDefault();
    btnPlay();
}

void Widget::addDefaultTracks()
{
    QDir dir("./tracks");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.count(); i++) {
        QFileInfo fileInfo = list.at(i);
        QList<QStandardItem *> items;
        items.append(new QStandardItem(fileInfo.fileName()));
        items.append(new QStandardItem(fileInfo.absoluteFilePath()));
        _playlistModel->appendRow(items);
        _playlist.push_back(fileInfo.absoluteFilePath());
    }
}

void Widget::btnAddClicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open File"), QString(), tr("Audio Files (*.mp3)"));
    foreach (QString filepath, files)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filepath).dirName()));
        items.append(new QStandardItem(filepath));
        _playlistModel->appendRow(items);
        _playlist.push_back(QDir(filepath).absolutePath());
    }
}
