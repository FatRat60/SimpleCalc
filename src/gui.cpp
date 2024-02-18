#include <QtWidgets>
#include "gui.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // Parent Layout
    topLayout = new QGridLayout;

    displayInit();

    numberButtonsInit();

    setLayout(topLayout);
    setWindowTitle(tr("Simple Calculator"));

    // connect button
    //connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
    //connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
MainWidget::~MainWidget()
{
    for (int i = 0; i < 7; i++) {
        delete opButtons[i];
        delete numButtons[i];
    }
    for (int i = 7; i < 10; i++) {
        delete numButtons[i];
    }
    delete display;
    delete topLayout;
}

// initialize the main buttons
void MainWidget::numberButtonsInit()
{
    // Button grid
    QGridLayout *numberLayout = new QGridLayout;

    // initialize all digit buttons
    int num = 10;
    for (int i = 0; i < 3; i++){
        num -= 3;
        for (int j = 0; j < 3; j++) {
            int adjNum = num + j;
            // create button
            std::string numberString = std::to_string(adjNum);
            numButtons[adjNum] = new QPushButton(tr(numberString.c_str()));
            // add to grid
            numberLayout->addWidget(numButtons[adjNum], i, j);
            connect(numButtons[adjNum], QPushButton::pressed, this, [=]() {
                onButtonPressed(numberString);
            });
        }
    }
    // Don't forget zero
    numButtons[0] = new QPushButton(tr("0"));
    numberLayout->addWidget(numButtons[0], 3, 1);
    connect(numButtons[0], QPushButton::pressed, this, [=]() { 
        onButtonPressed("0"); 
    });

    // Run opButtonInit
    opButtonsInit(numberLayout);
    topLayout->addLayout(numberLayout, 1, 0);
}

// initialize the op Buttons
void MainWidget::opButtonsInit(QGridLayout* layout)
{
    opButtons[4] = new QPushButton(tr("+/-"));
    opButtons[5] = new QPushButton(tr("."));
    opButtons[6] = new QPushButton(tr("="));
    layout->addWidget(opButtons[4], 3, 0);
    layout->addWidget(opButtons[5], 3, 2);
    layout->addWidget(opButtons[6], 4, 1);

    opButtons[0] = new QPushButton(tr("÷"));
    opButtons[1] = new QPushButton(tr("x"));
    opButtons[2] = new QPushButton(tr("-"));
    opButtons[3] = new QPushButton(tr("+"));
    layout->addWidget(opButtons[0], 0, 3);
    layout->addWidget(opButtons[1], 1, 3);
    layout->addWidget(opButtons[2], 2, 3);
    layout->addWidget(opButtons[3], 3, 3);
}

// initialize the display
void MainWidget::displayInit()
{
    // Load custom font
    int fontid = QFontDatabase::addApplicationFont(":/fonts/resources/DS-DIGI.TTF");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontid);

    // initialize display w/ grid
    display = new QLabel();
    QFont digitalFont(fontFamilies.at(0));
    display->setFont(digitalFont);
    display->setText(tr("0"));
    display->setAlignment(Qt::AlignCenter);
    topLayout->addWidget(display, 0, 0);
}

void MainWidget::onButtonPressed(std::string input)
{
    QString currentText = display->text();
    QString zero = "0";
    if (currentText == zero)
        currentText = "";
    display->setText(currentText + QString::fromStdString(input));
}

void MainWidget::resizeEvent(QResizeEvent *event) 
{
    int newSize = width() * 0.05;

    // update size
    QFont font = display->font();
    font.setPointSize(newSize);
    display->setFont(font);

    QWidget::resizeEvent(event);
}

void MainWidget::calculateResult()
{

}