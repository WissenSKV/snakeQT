#include "mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QMessageBox>

Snake::Snake(QWidget *parent) : QWidget(parent) {


    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    load();
    Game();
}

void Snake::load() {

    dot.load("C:\\Qt projects\\s\\body.png");
    head.load("C:\\Qt projects\\s\\head.png");
    apple.load("C:\\Qt projects\\s\\apple.png");
}

void Snake::Game() {

    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }

    Apple();

    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *event) {

    Q_UNUSED(event);

    Draw();
}

void Snake::Draw() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }


    }
}



void Snake::Applee() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
        Apple();
    }
}

void Snake::action() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}

void Snake::check() {

    for (int z = dots; z > 0; z--) {

        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

void Snake::Apple() {

    QTime time = QTime::currentTime();
    srand((uint) time.msec());

    int r = rand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = rand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *event) {

    Q_UNUSED(event);

    if (inGame) {

        Applee();
        check();
        action();
    }

    repaint();
}

void Snake::keyPressEvent(QKeyEvent *event) {

    int key = event->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    QWidget::keyPressEvent(event);
}
