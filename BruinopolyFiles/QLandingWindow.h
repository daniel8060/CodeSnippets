#ifndef QLANDINGWINDOW_H
#define QLANDINGWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QPainter>
#include <QLabel>
#include <QLayout>
#include <string>

class MainWindow;

//generates a QDialog showing the no-option statement, delete on closed
void NoOptionWindow(QWidget* parent, QString statement);


/*
Base class for my custom popup windows.
Stores a gridlayout and a QWidget.
Displays QWidget in 0,0 of GridLayout.
*/
class QLandingWindow : public QDialog {
    Q_OBJECT
public:
    QLandingWindow(QWidget* parent = nullptr);
    QLandingWindow(QWidget* _mainWidget, QWidget* parent);
    virtual ~QLandingWindow() = default;
protected:
    QGridLayout* layout;
    QWidget* mainWidget;
};



/*
   A window class for use in displaying a message that allows the player two options.
    For example, buying a property or not buying a property.
      displays its elements in a column.
*/
class QLandingOptions : public QLandingWindow {
    Q_OBJECT

public:
    QLandingOptions(QWidget* _mainWidget,
        const QString& _prompt,
        QWidget* parent,
        const QString& leftOpt = "Yes",
        const QString& rightOpt = "No"
    );

    QLabel* getPrompt()    const { return prompt; }
    QPushButton* getLeft() const { return left; }
    QPushButton* getRight()const { return right; }

    ~QLandingOptions() override = default;
private:
    QLabel* prompt;
    QPushButton* left;
    QPushButton* right;
};


#endif // QLANDINGWINDOW_H
