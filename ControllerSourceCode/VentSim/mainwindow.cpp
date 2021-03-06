
/*************************************************************
 * Open Ventilator
 * Copyright (C) 2020 - Marcelo Varanda
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **************************************************************
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QDebug>
//#include "../ArduinoVent/vent.h"
#include "vent.h"
#include "hal.h"
#include "event.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->bt_func, SIGNAL (pressed()),this, SLOT (onBtFuncPressed()));
    connect(ui->bt_func, SIGNAL (released()),this, SLOT (onBtFuncRelease()));
    connect(ui->bt_right, SIGNAL (pressed()),this, SLOT (onBtRightPressed()));
    connect(ui->bt_right, SIGNAL (released()),this, SLOT (onBtRightRelease()));
    connect(ui->bt_left, SIGNAL (pressed()),this, SLOT (onBtLeftPressed()));
    connect(ui->bt_left, SIGNAL (released()),this, SLOT (onBtLeftRelease()));

    halInit(ui->plainTextEdit);
    init_libs();
    ventSetup();

    timerId = startTimer(1);

}

MainWindow::~MainWindow()
{
    killTimer(timerId);
    delete ui;
}

void MainWindow::onBtFuncPressed()
{
    evtPost(EVT_KEY_PRESS, KEY_SET);
}

void MainWindow::onBtFuncRelease()
{
    evtPost(EVT_KEY_RELEASE, KEY_SET);
}

void MainWindow::onBtRightPressed()
{
    evtPost(EVT_KEY_PRESS, KEY_INCREMENT);
}

void MainWindow::onBtRightRelease()
{
    evtPost(EVT_KEY_RELEASE, KEY_INCREMENT);
}

void MainWindow::onBtLeftPressed()
{
    evtPost(EVT_KEY_PRESS, KEY_DECREMENT);
}

void MainWindow::onBtLeftRelease()
{
    evtPost(EVT_KEY_RELEASE, KEY_DECREMENT);
}

void MainWindow::onBtEnterPressed()
{
    evtPost(EVT_KEY_PRESS, KEY_RESERVE);
}

void MainWindow::onBtEnterRelease()
{
    evtPost(EVT_KEY_RELEASE, KEY_RESERVE);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    ventLoop();
}

