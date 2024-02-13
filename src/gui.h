#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QProcess>

class QPushButton;
class QTextBrowser;

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
    QPushButton* button_;
    QTextBrowser* textBrowser_;
    QProcess process_; // process the button fires off
};

#endif
