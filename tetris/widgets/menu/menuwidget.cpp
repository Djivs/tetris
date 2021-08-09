#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent)
{
    gameButton = new QPushButton("Play");
    settingsButton = new QPushButton("Settings");
    aboutButton = new QPushButton("About");

    connect(gameButton, &QPushButton::clicked, this, [this] {emit gameButtonPressed();});
    connect(settingsButton, &QPushButton::clicked, this, [this] {emit settingsButtonPressed();});
    connect(aboutButton, &QPushButton::clicked, this, [this] {emit aboutButtonPressed();});

    layout = new QVBoxLayout();
    layout->addWidget(gameButton);
    layout->addWidget(settingsButton);
    layout->addWidget(aboutButton);

    setLayout(layout);
}
