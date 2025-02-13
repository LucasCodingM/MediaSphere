#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QString>
#include <QTextStream>
#include <iostream>

class Logger
{
public:
    Logger(const QString &logFileName = "log.txt");
    // Constructor that sets up logging using qInstallMessageHandler
    // Destructor to clean up
    ~Logger();

private:
    // Actual logging method
    static void messageHandler(QtMsgType type,
                               const QMessageLogContext &context,
                               const QString &message);

    // File to log messages
    QFile m_logFile;
    static QTextStream m_textStream;
};

#endif // LOGGER_H
