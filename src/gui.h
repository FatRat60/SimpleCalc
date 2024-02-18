#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QProcess>

class QPushButton;
class QLabel;
class QGridLayout;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void onButtonPressed(std::string input);
    void calculateResult();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QLabel* display;
    QPushButton* numButtons[10]; // digit keys 0-9
    QPushButton* opButtons[7]; // +, -, ÷, *, =, +/-, .
    QGridLayout* topLayout;
    void numberButtonsInit();
    void opButtonsInit(QGridLayout* layout);
    void displayInit();
};

#endif
