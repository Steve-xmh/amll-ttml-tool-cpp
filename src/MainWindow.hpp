#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets>
#include <iostream>

#include "TTMLLyric.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    QTabWidget* editorTabWidget;
    QLabel* noFileOpenedWidget;

public slots:
    void onNewTTMLFile();
    void onOpenTTMLFile();
    void onSaveTTMLFile();
};

#endif // MAIN_WINDOW_H