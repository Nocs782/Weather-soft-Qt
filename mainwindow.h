#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fetchWeather();
    void handleResponse();
    void loadWeatherIcon(QString iconCode);
    QString capitalizeWords(const QString &input);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
};

#endif
