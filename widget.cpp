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

    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(btnAddClicked()));
    connect(ui->btnPlay, SIGNAL(clicked()), this, SLOT(btnPlay()));
    connect(ui->btnPause, SIGNAL(clicked()), this, SLOT(btnPause()));
//    connect(ui->btnPlay, &QToolButton::clicked, _player, &QMediaPlayer::play);
//    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){_playlist->setCurrentIndex(index.row());});

}

Widget::~Widget()
{
    delete ui;
    delete _player;
    delete _playlistModel;
}

void Widget::btnPlay()
{
    if (!_playlist[0]) return;
    _player->setSource(QUrl::fromLocalFile(_playlist[0]->item.path));
    _audioOutput->setVolume(50);
    _player->play();
    qDebug() << _player->errorString();
}

void Widget::btnPause()
{
    if (!_playlist[0]) return;
    _player->pause();
    qDebug() << _player->errorString();
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
        _playlist.push_back(QDir(filepath).absolutePath(), 30);
    }
}
