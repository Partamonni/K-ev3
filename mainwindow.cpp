#include "mainwindow.h"

#include "entry.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    entries = new Entry*[menu->buttonCount()];
    entries[0] = testEntry;

    this->setFixedSize(SCR_WIDTH,SCR_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setCentralWidget(center);
    #if !RPI
    this->grabMouse();
    this->grabKeyboard();
    #endif

    center->setLayout(bgLayout);
    bgLayout->addWidget(bgLabel,1,1,3,3);
    bgLayout->setContentsMargins(0,0,0,0);
    bgImg->load(":/mainbg");
    bgLabel->setPixmap(bgImg->scaled(SCR_WIDTH,
                                     SCR_HEIGHT,
                                     Qt::KeepAspectRatioByExpanding));

    bgLayout->addLayout(fgLayout,1,1,3,3, Qt::AlignLeft|Qt::AlignTop);
    bgLayout->addWidget(meter,1,1,1,3, Qt::AlignVCenter);

    fgLayout->setHorizontalSpacing(0);
    fgLayout->setContentsMargins(0,0,0,0);
    fgLayout->setGeometry(bgLayout->geometry());
    fgLayout->addWidget(menu,1,1,3,1,Qt::AlignLeft|Qt::AlignTop);

    fgLayout->addWidget(testEntry,1,2,3,3, Qt::AlignRight|Qt::AlignTop);
    meter->show();
    testEntry->show();
    //menu->show();

    connect(this, &MainWindow::lPressEvent, menu, &Menu::openMenu);
    connect(this, &MainWindow::lReleaseEvent, menu, &Menu::closeMenu);
    connect(this, &MainWindow::rPressEvent, this, &MainWindow::toggleEntry);
}

MainWindow::~MainWindow()
{
}

void MainWindow::mouseReleaseEvent(QMouseEvent *mouseEvent1)
{
    static bool asd = false;
    if(asd)
        this->lReleaseEvent();
    else
        this->lPressEvent();
    asd = !asd;
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent2)
{
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    this->rPressEvent();
}
void MainWindow::toggleEntry()
{
    if(menu->isVisible())
    {
        if(closingEntry != nullptr &&)
    }
    //entries[menu->selectorPosition()]->toggleEntry();
}

void MainWindow::toggleMotorEntry()
{}
