#include <QtWidgets>
#include "gui.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // Parent Layout
    QGridLayout *topLayout = new QGridLayout;
    // Button grid
    QGridLayout *numberLayout = new QGridLayout;

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

    // initialize all buttons
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
    opButtons[4] = new QPushButton(tr("+/-"));
    numButtons[0] = new QPushButton(tr("0"));
    opButtons[5] = new QPushButton(tr("."));
    opButtons[6] = new QPushButton(tr("="));
    numberLayout->addWidget(opButtons[4], 3, 0);
    numberLayout->addWidget(numButtons[0], 3, 1);
    numberLayout->addWidget(opButtons[5], 3, 2);
    numberLayout->addWidget(opButtons[6], 4, 1);
    connect(numButtons[0], QPushButton::pressed, this, [=]() { 
        onButtonPressed("0"); 
    });

    opButtons[0] = new QPushButton(tr("÷"));
    opButtons[1] = new QPushButton(tr("x"));
    opButtons[2] = new QPushButton(tr("-"));
    opButtons[3] = new QPushButton(tr("+"));
    numberLayout->addWidget(opButtons[0], 0, 3);
    numberLayout->addWidget(opButtons[1], 1, 3);
    numberLayout->addWidget(opButtons[2], 2, 3);
    numberLayout->addWidget(opButtons[3], 3, 3);

    topLayout->addLayout(numberLayout, 1, 0);

    button_ = new QPushButton(tr("Push Me!"));
    textBrowser_ = new QTextBrowser();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(button_, 0, 0);
    mainLayout->addWidget(textBrowser_, 1, 0);
    setLayout(topLayout);
    setWindowTitle(tr("Simple Calculator"));

    // connect button
    connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
    connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
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
    delete button_;
    delete textBrowser_;
}

// Handle for click]
void MainWidget::onButtonReleased()
{
    // clear text in textbrowser
    textBrowser_->clear();
    textBrowser_->append(tr("Running command:"));

    // set up process to write to stdout
    process_.setCurrentWriteChannel(QProcess::StandardOutput);
    process_.start("echo garsh");
}

void MainWidget::onCaptureProcessOutput()
{
    // DEtermine 
    QProcess* process = qobject_cast<QProcess*>(sender());
    if (process)
        textBrowser_->append(process->readAllStandardOutput());
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