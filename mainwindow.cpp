#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QTextStream>

QString loadApiKey() {

    QFile file(".env");

    qDebug() << "Trying to open .env file at:";

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open .env file!";
        return "";
    }

    QTextStream in(&file);
    QString line = in.readLine();
    file.close();

    if (line.startsWith("API_KEY=")) {
        return line.section("=", 1, 1).trimmed();
    }

    qDebug() << "Error: API_KEY not found in .env file!";
    return "";
}



const QString API_KEY = loadApiKey();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);

    connect(ui->btnGetWeather, &QPushButton::clicked, this, &MainWindow::fetchWeather);
}

void MainWindow::fetchWeather() {
    if (API_KEY.isEmpty()) {
        ui->labelCityName->setText("Error: API Key not loaded!");
        return;
    }

    QString city = ui->lineEditCity->text().trimmed();
    if (city.isEmpty()) {
        ui->labelCityName->setText("Please enter a city name.");
        return;
    }

    QString url = "https://api.openweathermap.org/data/2.5/weather?q=" + city +
                  "&appid=" + API_KEY + "&units=metric";

    qDebug() << "Requesting URL:" << url;

    QNetworkRequest request((QUrl(url)));
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &MainWindow::handleResponse);
}

void MainWindow::handleResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "API Response:" << response;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        QString cityName = jsonObj["name"].toString();
        double temp = jsonObj["main"].toObject()["temp"].toDouble();
        double feelsLike = jsonObj["main"].toObject()["feels_like"].toDouble();
        int humidity = jsonObj["main"].toObject()["humidity"].toInt();
        double windSpeed = jsonObj["wind"].toObject()["speed"].toDouble();
        int pressure = jsonObj["main"].toObject()["pressure"].toInt();
        QString desc = jsonObj["weather"].toArray()[0].toObject()["description"].toString();
        QString iconCode = jsonObj["weather"].toArray()[0].toObject()["icon"].toString();

        QDateTime sunriseTime = QDateTime::fromSecsSinceEpoch(jsonObj["sys"].toObject()["sunrise"].toInt()).toLocalTime();
        QDateTime sunsetTime = QDateTime::fromSecsSinceEpoch(jsonObj["sys"].toObject()["sunset"].toInt()).toLocalTime();

        int timezoneOffset = jsonObj["timezone"].toInt();
        QDateTime utcNow = QDateTime::currentDateTimeUtc();
        QDateTime cityTime = utcNow.addSecs(timezoneOffset);

        QDateTime userLocalTime = QDateTime::currentDateTime();

        ui->labelCurrentTime->setText(userLocalTime.toString("hh:mm AP"));
        ui->labelCityTime->setText(cityTime.toString("hh:mm AP"));
        ui->labelCityName->setText(cityName);
        ui->labelTemp->setText(QString::number(temp) + "°C");
        ui->labelFeelsLike->setText(QString::number(feelsLike) + "°C");
        ui->labelHumidity->setText(QString::number(humidity) + "%");
        ui->labelWindSpeed->setText(QString::number(windSpeed) + " m/s");
        ui->labelPressure->setText(QString::number(pressure) + " hPa");
        ui->labelSunrise->setText(sunriseTime.toString("hh:mm AP"));
        ui->labelSunset->setText(sunsetTime.toString("hh:mm AP"));
        ui->labelDesc->setText(capitalizeWords(desc));

        loadWeatherIcon(iconCode);
    } else {
        qDebug() << "API Error:" << reply->errorString();
        ui->labelCityName->setText("Error fetching weather!");
    }

    reply->deleteLater();
}

QString MainWindow::capitalizeWords(const QString &input) {
    QStringList words = input.split(" ");
    for (int i = 0; i < words.size(); ++i) {
        if (!words[i].isEmpty()) {
            words[i][0] = words[i][0].toUpper();
        }
    }
    return words.join(" ");
}

void MainWindow::loadWeatherIcon(QString iconCode) {
    QString iconPath = QCoreApplication::applicationDirPath() + "/icons/" + iconCode + "@2x.png";
    qDebug() << "Loading Weather Icon from:" << iconPath;

    QPixmap pixmap(iconPath);
    if (pixmap.isNull()) {
        qDebug() << "Error: Failed to load icon from local directory!";
    } else {
        qDebug() << "Weather icon loaded successfully!";
        ui->labelIcon->setPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}



MainWindow::~MainWindow() {
    delete ui;
}
