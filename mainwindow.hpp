#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDialog>
#include <QProcess>
#include <QSettings>
#include <QMessageBox>
#include <QFile>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QDialog
{

	   Q_OBJECT

    public:

	   MainWindow(QWidget *parent = nullptr);
	   ~MainWindow();

	   void accept(void);

    private:

	   Ui::MainWindow* Interface;

	   QSettings INI;

};

#endif // MAINWINDOW_HPP
