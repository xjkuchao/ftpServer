#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QLoggingCategory>
#include <QRegularExpression>
#include <QSettings>
#include <QTcpServer>
#include <QTcpSocket>
#include <ftpserver.h>
#include <qtservice.h>

class FtpService : public QtService<QCoreApplication> {
  public:
    FtpService(int argc, char **argv)
        : QtService<QCoreApplication>(argc, argv, "FtpService Daemon") {
        setServiceDescription("FTP service implemented by tyler");
        setServiceFlags(QtServiceBase::Default);
    }

  protected:
    void start() {
        QCoreApplication *app = application();
        QSettings *settings = new QSettings(QDir::currentPath() + "/config.ini",
                                            QSettings::Format::IniFormat);

        const int      port = settings->value("port", 21).toInt();
        const QString &userName =
            settings->value("user_name", "admin").toString();
        const QString &password =
            settings->value("pass_word", "huimukj").toString();
        const QString &rootPath =
            settings->value("root_path", "d:\\huimu\\luxiang\\").toString();
        const bool readOnly = settings->value("read_only", true).toBool();

        FtpServer *server = new FtpServer(app, rootPath, port, userName,
                                          password, readOnly, false);
        if (server->isListening()) {
            qDebug() << QString("Listening at %1:%2")
                            .arg(FtpServer::lanIp())
                            .arg(port);
            logMessage(QString("Listening at %1:%2")
                           .arg(FtpServer::lanIp())
                           .arg(port));
        } else {
            logMessage(QString("Failed to start"), MessageType::Error);
            app->quit();
        }
    }
};

int main(int argc, char *argv[]) {
    FtpService service(argc, argv);
    return service.exec();
}
