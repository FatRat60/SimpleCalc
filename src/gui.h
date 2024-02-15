#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QProcess>

class QPushButton;
class QTextBrowser;
class QLCDNumber;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onButtonReleased();
    void onCaptureProcessOutput();

private:
    QLCDNumber* display;
    QPushButton* numButtons[10]; // digit keys 0-9
    QPushButton* opButtons[7]; // +, -, ÷, *, =, +/-, .
    QProcess pCalculate; // process will handle calculations, probably
    QPushButton* button_;
    QTextBrowser* textBrowser_;
    QProcess process_; // process the button fires off
};

#endif
