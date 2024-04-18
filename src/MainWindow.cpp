#include "MainWindow.h"

#include <qmessagebox.h>

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Apple Music-like lyrics TTML Tools");

    setAnimated(true);
    setMinimumSize(640, 360);

    // 菜单

    {
        auto menuBar = this->menuBar();

        auto fileMenu = new QMenu("文件");

        auto newFileAction = new QAction("新建 TTML 文件", fileMenu);
        newFileAction->setShortcut(QKeySequence::New);
        newFileAction->connect(newFileAction, &QAction::triggered, this, &MainWindow::onNewTTMLFile);
        fileMenu->addAction(newFileAction);

        auto openFileAction = new QAction("打开 TTML 文件", fileMenu);
        openFileAction->setShortcut(QKeySequence::Open);
        openFileAction->connect(openFileAction, &QAction::triggered, this, &MainWindow::onOpenTTMLFile);
        fileMenu->addAction(openFileAction);

        auto saveFileAction = new QAction("保存 TTML 文件", fileMenu);
        saveFileAction->setShortcut(QKeySequence::Save);
        saveFileAction->connect(saveFileAction, &QAction::triggered, this, &MainWindow::onSaveTTMLFile);
        fileMenu->addAction(saveFileAction);

        menuBar->addMenu(fileMenu);

        setMenuBar(menuBar);
    }

    // 布局

    auto mainWidget = new QWidget();

    auto mainHBox = new QHBoxLayout();
    mainHBox->setContentsMargins(0, 0, 0, 0);

    editorTabWidget = new QTabWidget();
    noFileOpenedWidget = new QLabel("尚未打开 TTML 文件\n请在菜单栏中选择打开或新建一个 TTML 文件");

    mainHBox->addWidget(noFileOpenedWidget, 1, Qt::AlignCenter);

    mainWidget->setLayout(mainHBox);

    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onNewTTMLFile()
{
    cout << "正在新建 TTML 文件" << endl;
}

void MainWindow::onOpenTTMLFile()
{
    cout << "正在打开 TTML 文件" << endl;
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("TTML 文件 (*.ttml)");
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.exec();
    auto selectedFiles = dialog.selectedFiles();
    if (selectedFiles.size() == 0) {
        return;
    }
    auto selectedFile = selectedFiles[0];
    cout << "选择了文件：" << selectedFile.toStdString() << endl;
    QFile file(selectedFile);
    if (!file.open(QIODevice::ReadOnly)) {
        cout << "无法打开文件：" << selectedFile.toStdString() << endl;
        return;
    }
    auto data = file.readAll();
    cout << "文件内容：" << data.toStdString() << endl;
    file.close();
    auto ttmlLyric = new TTMLLyric();
    try {
        ttmlLyric->readFromString(data.toStdString());
    } catch (exception& e) {
        cout << "读取文件失败：" << e.what() << endl;
        QMessageBox::critical(this, "读取文件失败", e.what());
        return;
    }
    cout << "读取完成" << endl;
    delete ttmlLyric;
}

void MainWindow::onSaveTTMLFile()
{
}
