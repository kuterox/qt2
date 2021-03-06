#include <QtGui>
#include <QPainter>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    renderArea = new RenderArea();\
    setCentralWidget(renderArea);

    createActions();
    createMenus();

    setWindowTitle(tr("QuTe Viewer"));

    resize(500, 400);
}

void MainWindow::changePen()
{
    RenderArea::Shape shape = RenderArea::Shape(drawGroup->checkedAction()->data().toInt());
    renderArea->setShape(shape);
    setWindowTitle(drawGroup->checkedAction()->data().toString());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About QuTe Drawer"),
            tr("<b>QuTe Drawer</b><br/>Version: 0.1.0 20-11-2010"));
}

void MainWindow::createActions()
{
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    drawGroup = new QActionGroup(this);
    
    lineAct = new QAction(tr("&Line"), this);
    lineAct->setCheckable(true);
    lineAct->setData(RenderArea::Line);
    
    rectAct = new QAction(tr("&Rect"), this);
    rectAct->setCheckable(true);
    rectAct->setData(RenderArea::Rect);
    
    roundRectAct = new QAction(tr("Round rect"), this);
    roundRectAct->setCheckable(true);
    roundRectAct->setData(RenderArea::RoundRect);
    
    ellipseAct = new QAction(tr("&Ellipse"), this);
    ellipseAct->setCheckable(true);
    ellipseAct->setData(RenderArea::Ellipse);
    
    drawGroup->addAction(lineAct);
    drawGroup->addAction(rectAct);
    drawGroup->addAction(roundRectAct);
    drawGroup->addAction(ellipseAct);
    lineAct->setChecked(true);
    connect(drawGroup, SIGNAL(triggered(QAction*)), this, SLOT(changePen()));
    
    
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(exitAct);

    drawMenu = new QMenu(tr("&Draw"), this);
    drawMenu->addAction(lineAct);
    drawMenu->addAction(rectAct);
    drawMenu->addAction(roundRectAct);
    drawMenu->addAction(ellipseAct);
    
    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(drawMenu);
    menuBar()->addMenu(helpMenu);
}   
