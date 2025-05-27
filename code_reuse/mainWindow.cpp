#include "mainWindow.h"
#include "price_calc.h"

MainWindow::MainWindow(QWidget* parent)
                    : QMainWindow(parent)
{
    setWindowTitle("price calc");
    setCentralWidget(new PriceCalc);
}