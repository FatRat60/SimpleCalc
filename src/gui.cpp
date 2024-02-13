#include <QtWidgets>
#include "gui.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    button_ = new QPushButton(tr("Push Me!"));
    textBrowser_ = new QTextBrowser();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(button_, 0, 0);
    mainLayout->addWidget(textBrowser_, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Connecting buttons to processes"));

    // connect button
    connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
    connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
MainWidget::~MainWidget()
{
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
