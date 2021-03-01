#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QRegExp>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QPalette>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->goBtn->setEnabled(false);

    connect(ui->expressionText, &QLineEdit::textChanged,
            this, &MainWindow::expressionTextChanged);

    connect(ui->contentText, &QPlainTextEdit::textChanged,
            this, &MainWindow::contentTextChanged);
    connect(ui->goBtn, &QPushButton::clicked,
            this, &MainWindow::goBtnClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::expressionTextChanged()
{
    ui->goBtn->setEnabled(formValid());
}

void MainWindow::contentTextChanged()
{
    ui->goBtn->setEnabled(formValid());
}

void MainWindow::goBtnClicked()
{
    testExpression();

}

void MainWindow::testExpression()
{
    QRegExp rx(ui->expressionText->text());
    auto content = ui->contentText->toPlainText();
    auto startIndex = 0;

    if(rx.indexIn(content, startIndex) == -1) return;

    clearTextFormatting();
    clearCaptureGroups();

    QVector<Offset> offsets;

    while ((startIndex = rx.indexIn(content, startIndex)) != -1) {
        auto length = rx.matchedLength();
        Offset os;
        os.start = startIndex;
        os.end = startIndex + length;
        offsets.append(os);
        startIndex += length;
    }

    highlightOffsets(offsets);
}

bool MainWindow::formValid() const{
    return QRegExp(ui->expressionText->text()).isValid()
            &&!ui->expressionText->text().isEmpty()
            && !ui->contentText->toPlainText().isEmpty();
}

void MainWindow::highlightOffsets(const QVector<Offset> &offsets)
{

    QTextCharFormat fmt;
    auto cursor = ui->contentText->textCursor();
    fmt.setBackground(Qt::cyan);
    for(auto os : offsets) {
        cursor.setPosition(os.start, QTextCursor::MoveAnchor);
        cursor.setPosition(os.end, QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);
    }
}

void MainWindow::displayCaptureGroups(const QStringList &captures)
{
    ui->captureList->addItems(captures);
}

void MainWindow::clearCaptureGroups()
{
    ui->captureList->clear();
}

void MainWindow::clearTextFormatting()
{
    auto cursor = ui->contentText->textCursor();
    cursor.select(QTextCursor::Document);
    cursor.setCharFormat(QTextCharFormat());
    cursor.clearSelection();
}





