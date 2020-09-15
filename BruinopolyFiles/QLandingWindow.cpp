#include "qlandingwindow.h"
#include "mainwindow.h"
#include <QDialog>

QLandingWindow::QLandingWindow(QWidget* parent) :
    QDialog(parent),
    layout(new QGridLayout(this))
{
    open();
}

QLandingWindow::QLandingWindow(QWidget* _mainWidget, QWidget* parent) :
    QDialog(parent),
    layout(new QGridLayout(this)),
    mainWidget(_mainWidget)
{
    open();
}

QLandingOptions::QLandingOptions(
    QWidget* _mainWidget,
    const QString& _prompt,
    QWidget* parent,
    const QString& leftOpt,
    const QString& rightOpt
)
    :
    QLandingWindow(_mainWidget, parent),
    prompt(new QLabel(_prompt, this)),
    left(new QPushButton(leftOpt, this)),
    right(new QPushButton(rightOpt, this))
{
    this->setAttribute(Qt::WA_DeleteOnClose); //shortlived window don't want it keeping memory after closed

    layout->addWidget(mainWidget, 0, 0);
    layout->addWidget(prompt, 2, 0);
    layout->addWidget(left, 3, 0);
    layout->addWidget(right, 4, 0);
    this->setLayout(layout);

    sizeHint();

    open(); //open as modal dialog window

    //close window once we click a button
    connect(left, &QPushButton::clicked, this, &QWidget::close);
    connect(right, &QPushButton::clicked, this, &QWidget::close);
}


void NoOptionWindow(QWidget* parent, QString statement) {
    QDialog* content = new QDialog(parent);
    QHBoxLayout* layout = new QHBoxLayout;
    QLabel* lb = new QLabel(statement);
    content->setFixedSize(400, 200);
    layout->addWidget(lb);
    content->setLayout(layout);
    content->setWindowTitle("Notice");
    content->show();
}
