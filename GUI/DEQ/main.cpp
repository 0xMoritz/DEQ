#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QTextBrowser>
#include <QWebEngineView>
#include <QUrl>
#include <QDir>

/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}*/



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout layout;

    // Read File
    QFile inFile("../../latex/eq");
    if(!inFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "error", inFile.errorString() + " inFile");
    }
    QTextStream in(&inFile);
    QString eq = "";
    while(!in.atEnd())
    {
        QString line = in.readLine();
        eq += line + "\n";
    }
    inFile.close();

    // Write File
    QString header = "<!DOCTYPE html>\n<script type='text/javascript' async src='https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.1/MathJax.js?config=TeX-AMS-MML_HTMLorMML'></script>\n<p>$$";
    QString footer = "$$</p>";
    QFile outFile(QDir::currentPath() + "/../../latex/" + "label.html");
    if (!outFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(0, "error", outFile.errorString() + " outFile");
    }
    QTextStream out(&outFile);
    out << header + eq + footer << "\n";
    outFile.close();


    QWebEngineView* web = new QWebEngineView();
    qDebug() << QDir::currentPath() + "/" + "label.html";
    web->load(QUrl::fromLocalFile(QDir::currentPath() + "/../../latex/" + "label.html"));
    layout.addWidget(web);

    window.setLayout(&layout);
    window.show();

    return app.exec();
}
