#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
: QDialog(parent), Interface(new Ui::MainWindow), INI(qgetenv("HOME") + "/.config/display-switcher.ini", QSettings::IniFormat)
{
    Interface->setupUi(this);

    INI.setIniCodec("UTF-8");
    INI.beginGroup("Settings");

    const QStringList devices = INI.value("Devices").toStringList();

    const QString master = INI.value("Master", "").toString();
    const QString slave = INI.value("Slave", "").toString();

    Interface->Master->addItems(devices);
    Interface->Slave->addItems(devices);

    const int master_index = Interface->Master->findText(master);
    const int slave_index = Interface->Slave->findText(slave);

    Interface->Master->setCurrentIndex(master_index);
    Interface->Slave->setCurrentIndex(slave_index);
}

MainWindow::~MainWindow()
{
    delete Interface;
}

void MainWindow::accept(void)
{
    if (Interface->Master->currentIndex() == Interface->Slave->currentIndex())
    {
	   QMessageBox::warning(this, "Błąd", "Musisz wybrać dwa różne urządzenia");
    }
    else
    {

	   const QString master = Interface->Master->currentText();
	   const QString slave = Interface->Slave->currentText();
	   const QString res = Interface->Resolution->currentText();

	   QString Command;

	   INI.setValue("Master", master);
	   INI.setValue("Slave", slave);

	   if (Interface->setupMaster->isChecked())
	   {
		  Command = QString("xrandr --output %1 --auto --primary --output %2 --off").arg(master).arg(slave);
	   }
	   else if (Interface->setupSlave->isChecked())
	   {
		  Command = QString("xrandr --output %2 --auto --output %1 --off").arg(master).arg(slave);
	   }
	   else if (Interface->setupBoth->isChecked())
	   {
		  Command = QString("xrandr --output %1 --auto --primary --output %2 --auto --right-of %1").arg(master).arg(slave).arg(res);
	   }
	   else if (Interface->setupClone->isChecked())
	   {
		   Command = QString("xrandr --output %1 --mode %3 --primary --output %2 --mode %3 --same-as %1").arg(master).arg(slave).arg(res);
	   }

	   QProcess::execute(Command);

	   QDialog::accept();

    }
}
