#include "dialog.h"
#include "ui_dialog.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDesktopServices>
#include <QUrl>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    movieNameEdit = new QLineEdit(this);
    searchButton = new QPushButton("Search Netflix", this);
    resultLabel = new QLabel(this);

    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow("Movie Name:", movieNameEdit);
    formLayout->addRow("", searchButton);
    formLayout->addRow("", resultLabel);

    setLayout(formLayout);

    connect(searchButton, &QPushButton::clicked, this, &Dialog::searchNetflix);
}

void Dialog::setupUi() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(movieNameEdit);
    layout->addWidget(searchButton);
    layout->addWidget(resultLabel);
}
void Dialog::searchNetflix() {
    QString apiKey = "96727050"; // Replace with your OMDb API key
    QString movieName = movieNameEdit->text();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request(QUrl("http://www.omdbapi.com/?apikey=" + apiKey + "&t=" + movieName));
    qDebug() << "Making request to: " << request.url().toString();
    // Connect the authenticationRequired signal to a lambda function for providing credentials
    connect(manager, &QNetworkAccessManager::authenticationRequired, [this, manager, movieName](QNetworkReply *, QAuthenticator *authenticator) {
        // Provide your authentication details here
        authenticator->setUser("your_username");
        authenticator->setPassword("your_password");
    });

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [this, manager, reply, movieName]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObject = jsonResponse.object();

            QString response = jsonObject["Response"].toString();

            if (response == "True") {
                resultLabel->setText("Movie is available on Netflix!");
               // QString formattedName=movieName.replace("%20","-");
                // Construct the search URL for "swatchseries.is" using the entered movie name
                QUrl moviesJoySearchUrl("https://moviesjoy.is/search/" + movieName);

                // Open the URL in the user's default web browser
                QDesktopServices::openUrl(moviesJoySearchUrl);
            } else {
                resultLabel->setText("Movie not found on Netflix. Check other platforms.");
                // TODO: Provide an option to open the movie in other streaming platforms
            }
        } else {
            resultLabel->setText("Error: " + reply->errorString());
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}


Dialog::~Dialog()
{
    delete ui;
}
