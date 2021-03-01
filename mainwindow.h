#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QStringList>


struct Offset {
    int start, end;
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void expressionTextChanged();
    void contentTextChanged();
    void goBtnClicked();

private:
    Ui::MainWindow *ui;
    void testExpression();
    bool formValid() const;
    void highlightOffsets(const QVector<Offset>& offsets);
    void displayCaptureGroups(const QStringList& captures);
    void clearCaptureGroups();
    void clearTextFormatting();
};
#endif // MAINWINDOW_H
