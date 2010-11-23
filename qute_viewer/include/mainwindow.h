#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPrinter>

class QLabel;
class QScrollArea;
class QScrollBar;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();

    void greyScale();
    void negative();
    void gradient();
    void hMirror();
    void vMirror();

    void about();

private:
    void mirror(bool hori);
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QImage image;
    Ui::MainWindow *ui;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    double scaleFactor;
};

#endif

