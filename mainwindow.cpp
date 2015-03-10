#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QApplication* app, QWidget *parent)
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

		QString Command;

		INI.setValue("Master", master);
		INI.setValue("Slave", slave);

		if (Interface->setupMaster->isChecked())
		{
			Command = "xrandr --output " + master + " --auto --primary --output " + slave + " --off";
		}
		else if (Interface->setupSlave->isChecked())
		{
			Command = "xrandr --output " + slave + " --auto --output " + master + " --off";
		}
		else if (Interface->setupBoth->isChecked())
		{
			Command = "xrandr --output " + master + " --auto --primary --output " + slave + " --auto --right-of " + master;
		}

		QProcess Process(this);

		Process.execute(Command);

		QDialog::accept();

	}
}
