#include "createpage.h"
#include "ui_createpage.h"
#include "mediaplayer.h"
#include "piano.h"
#include "string.h"
#include "fileoperatingwidget.h"

CreatePage::CreatePage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CreatePage)
{
    ui->setupUi(this);
    player = new MediaPlayer();
    this->channelEdits[0] = this->ui->w0;
    this->channelEdits[1] = this->ui->w1;
    this->channelEdits[2] = this->ui->w2;
    this->channelEdits[3] = this->ui->w3;
    this->channelEdits[4] = this->ui->w4;
    this->channelEdits[5] = this->ui->w5;
    this->channelEdits[6] = this->ui->w6;
    this->channelEdits[7] = this->ui->w7;
    this->channelEdits[8] = this->ui->w8;

    for (int i = 0; i < 9; ++i) {
        this->channelEdits[i]->set_id(i);
        connect(this->channelEdits[i], &ChannelEdit::ChangeChannelStrength, this->player, &MediaPlayer::changeChannelStrength);
        connect(this->channelEdits[i], &ChannelEdit::ChangeMusicType, this->player, &MediaPlayer::changeMusicType);
        connect(this->channelEdits[i], &ChannelEdit::CurrentEditing, this->player, &MediaPlayer::setCurrentEditing);
        connect(this->channelEdits[i], &ChannelEdit::DeliverNote, this->player, &MediaPlayer::receiveNote);
    }
}

CreatePage::~CreatePage()
{
    delete ui;
}

void CreatePage::getmusic(Music *song){
    sang=song;
    player->SetMusic(sang);
    QString k(sang->name.c_str());
    ui->musicNameEdit->setText(k);
    for (int i = 0; i < song->channal_num; ++i) {
        this->channelEdits[i]->setStrength(song->allChannals[i]->strength);
        this->channelEdits[i]->setMusicType(song->allChannals[i]->type);
        this->channelEdits[i]->show();
    }
    for (int i = song->channal_num; i < 9; ++i) {
        this->channelEdits[i]->hide();
    }
}

void CreatePage::on_pushButton_clicked()
{
    FileOperatingWidget *t = new FileOperatingWidget(sang);
    t->show();
}

void CreatePage::on_playButton_clicked()
{
    this->player->PlayMusic();
}

void CreatePage::on_pauseButton_clicked()
{
    if (this->paused == false) {
        this->player->pause();
    }
    else {
        this->player->restart();
    }
    this->paused = !this->paused;
}

void CreatePage::on_stopButton_clicked()
{
    this->player->stop();
}

void CreatePage::on_checkBox_stateChanged(int arg1)
{
    if(arg1==0){
        player->closeMetronome();
    }
    else {
        player->openMetronome();
    }
}

