#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <string>
#include <vector>

// LSL API
#include <lsl_cpp.h>

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent, const std::string &config_file);
    ~MainWindow();
    
private slots:
    // config file dialog ops (from main menu)
    void load_config_dialog();
    void save_config_dialog();

    // start the AMTI connection
    void link_amti();

    // close event (potentially disabled)
    void closeEvent(QCloseEvent *ev);
private:
    // background data reader thread
	void read_thread(HANDLE hPort, int comPort, int samplingRate, int numDevices);

    // raw config file IO
    void load_config(const std::string &filename);
    void save_config(const std::string &filename);
	
	bool stop_;											// whether the reader thread is supposed to stop
	float calib_[2][6][6];								// device calibration matrices (one per device, 6x6)
    boost::shared_ptr<boost::thread> reader_thread_;	// our reader thread

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H