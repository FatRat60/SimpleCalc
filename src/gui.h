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
    void onArithOpPressed(int index);
    void calculateResult();
    void plusMinus();
    void addDecimal();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    QLabel* display;
    QPushButton* numButtons[10]; // digit keys 0-9
    QPushButton* opButtons[9]; // ÷, *, -, +, +/-, ., =, DEL, C
    QGridLayout* topLayout;
    int currentOpIndex;
    bool isTyping;
    int doCalcOnClick;
    bool EqRepeat;
    double arg1;
    double lastVal;
    bool canAddDecimal;
    void numberButtonsInit();
    void opButtonsInit(QGridLayout* layout);
    void displayInit();
};

#endif
