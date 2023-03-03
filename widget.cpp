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
//    std::time_t tt = static_cast<time_t>(_player->duration()/1000);
    if (!_playlist[_index] || _index == (uint32_t)-1) return;
//    std::cout << static_cast<time_t>(_player->position()/1000) << std::endl;
    ui->playingTrack->setMaximum(_player->duration()/1000);
    ui->playingTrack->setValue((int)_player->position()/1000);
    ui->currentTime->setText(convertTime(_player->position()/1000));
    ui->endTime->setText(convertTime(_player->duration()/1000));
//    std::cout << _player->duration() << std::endl;
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
        //    _player->duration() = _playlist[_index]->item.duration;

            ui->btnPlay->setText("Pause");
            _playState = 1;
            _player->play();
//            std::cout << _player->duration() << std::endl;
//            QDebug() << QString::number(_player->duration() / 1000);
//            ui->playingTrack->setMaximum((int)(_player->duration()/1000));
//            qDebug() << (_player->duration());

            break;

        case 1:
        //    std::cout << _player->position() << _pos << std::endl;
            _player->pause();
            _playState = 0;
            ui->btnPlay->setText("Play");
//            std::cout << _player->duration() << std::endl;
            break;

        default:
            qWarning("Это не должно так работать");
            break;
    }
}

void Widget::btnNext()
{
    if (!_playlist[_index + 1])
    {
//        _playState = -1;
//        ui->btnPlay->setText("Play");
        return;
    }
    _index++;
    setDefault();
    btnPlay();
//    qDebug() << _player->errorString() << _playlistModel->rowCount();
}

void Widget::btnPrev()
{
    if (!_playlist[_index - 1]) return;
    _index--;
    setDefault();
    btnPlay();
//    qDebug() << _player->errorString() << _playlistModel->rowCount();
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
//        qDebug() << QString("%1 %2").arg(fileInfo.fileName()).arg(fileInfo.absoluteFilePath());
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
