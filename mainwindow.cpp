#include "mainwindow.h"

#include "entry.h"
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    entries = new Entry*[menu->buttonCount()];

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

    bgLayout->addWidget(meter,1,1,1,3, Qt::AlignVCenter);
    //bgLayout->addLayout(fgLayout,1,1,3,3, Qt::AlignLeft|Qt::AlignTop);
    bgLayout->addWidget(fgFrame,1,1,3,3, Qt::AlignLeft|Qt::AlignTop);
    fgFrame->setLayout(fgLayout);
    fgFrame->setFixedSize(this->size());
    fgFrame->setGraphicsEffect(opaEff);
    opaEff->setOpacity(0.98);

    fgLayout->setHorizontalSpacing(0);
    fgLayout->setContentsMargins(0,0,0,0);
    fgLayout->addWidget(menu,1,1,3,1,Qt::AlignLeft|Qt::AlignTop);
    fgLayout->addWidget(entryTemp,1,2,3,3, Qt::AlignRight|Qt::AlignTop);
    fgLayout->addWidget(entryMotor,1,2,3,3, Qt::AlignRight|Qt::AlignTop);
    fgLayout->addWidget(entryStats,1,2,3,3, Qt::AlignRight|Qt::AlignTop);
    fgLayout->addWidget(entryErrors,1,2,3,3, Qt::AlignRight|Qt::AlignTop);
    fgLayout->addWidget(entryStatus,1,2,3,3, Qt::AlignRight|Qt::AlignTop);
    fgLayout->addWidget(entrySerialLog,1,2,3,3, Qt::AlignRight|Qt::AlignTop);

    entries[0] = entryTemp;
    entries[1] = entryStatus;
    entries[2] = entryStats;
    entries[3] = entrySerialLog;
    entries[4] = entryErrors;
    entries[5] = entryMotor;

    QSizePolicy temp = menu->sizePolicy();
    temp.setRetainSizeWhenHidden(true);
    menu->setSizePolicy(temp);

    meter->show();
    //testEntry->show();
    //menu->show();

    connect(this, &MainWindow::lPressEvent1, menu, &Menu::openMenu);
    connect(this, &MainWindow::lPressEvent2, menu, &Menu::closeMenu);
    connect(this, &MainWindow::rPressEvent, menu, &Menu::toggleSelector);
    connect(this, &MainWindow::kPressEvent, this, &MainWindow::toggleEntry);
}

MainWindow::~MainWindow()
{
}

void MainWindow::mouseReleaseEvent(QMouseEvent *mouseEvent1)
{
    if(mouseEvent1->button() == Qt::LeftButton)
    {
        static bool asd = false;
        if(asd)
            this->lPressEvent2();
        else
            this->lPressEvent1();
        asd = !asd;
    }
    else
    {
        this->rPressEvent();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *mouseEvent2)
{
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    this->kPressEvent();
}
void MainWindow::toggleEntry()
{
    if(menu->isVisible())
    {
        int selPos = menu->selectorPosition();
        if(closingEntry != nullptr)
        {
            if(closingEntry->isClosing())
                return;
            else
            {
                closingEntry->toggleEntry();

                if(closingEntry == entries[selPos])
                {
                    closingEntry = nullptr;
                    return;
                }
            }
        }

        entries[selPos]->toggleEntry();
        closingEntry = entries[selPos];
    }
}

void MainWindow::toggleMotorEntry()
{}
