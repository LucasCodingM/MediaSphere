#ifndef LOGGER_H
#define LOGGER_H

#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QString>
#include <QTextStream>
#include <iostream>

/**
 * @class Logger
 * @brief A logging utility to handle and record log messages with timestamps and log levels.
 *
 * This class provides functionality to log messages to a file and console with different log levels.
 * It uses a custom message handler to format and output log messages.
 */
class Logger
{
public:
    /**
     * @brief Constructor for Logger.
     *
     * Initializes the logger with a specified log file name. Opens the log file in append mode
     * and installs a custom message handler.
     *
     * @param logFileName The name of the log file.
     */
    Logger(const QString &logFileName = "log.txt");
    /**
     * @brief Destructor for Logger.
     *
     * Closes the log file if it is open.
     */
    ~Logger();

private:
    /**
     * @brief Custom message handler for logging.
     *
     * This static method handles log messages, formats them with a timestamp, log level,
     * and context information, and writes them to both a log file and the console.
     *
     * @param type The type of the log message.
     * @param context The context of the log message.
     * @param message The log message.
     */
    static void messageHandler(QtMsgType type,
                               const QMessageLogContext &context,
                               const QString &message);

    QFile m_logFile;                 /**< Log file to write log messages. */
    static QTextStream m_textStream; /**< Text stream to write to the log file. */
};

#endif // LOGGER_H
