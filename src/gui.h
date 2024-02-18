#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QProcess>

class QPushButton;
class QTextBrowser;
class QLabel;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onButtonPressed(std::string input);
    void onButtonReleased();
    void onCaptureProcessOutput();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel* display;
    QPushButton* numButtons[10]; // digit keys 0-9
    QPushButton* opButtons[7]; // +, -, ÷, *, =, +/-, .
    QProcess pCalculate; // process will handle calculations, probably
    QPushButton* button_;
    QTextBrowser* textBrowser_;
    QProcess process_; // process the button fires off
};

#endif
