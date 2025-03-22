#include "logger.h"

// Initialize the static member
QTextStream Logger::m_textStream;

Logger::Logger(const QString &logFileName)
{
    // Open log file in append mode
    m_logFile.setFileName(logFileName);
    if (!m_logFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open log file for writing!";
        return;
    }

    m_textStream.setDevice(&m_logFile);

    // Install custom message handler
    qInstallMessageHandler(Logger::messageHandler);
}

Logger::~Logger()
{
    if (m_logFile.isOpen()) {
        m_logFile.close();
    }
}

void Logger::messageHandler(QtMsgType type,
                            const QMessageLogContext &context,
                            const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString logLevel;
    QString colorCode;

    // Determine log level
    switch (type) {
    case QtDebugMsg:
        logLevel = "DEBUG";
        colorCode = "\033[0;32m"; // Green
        break;
    case QtInfoMsg:
        logLevel = "INFO";
        colorCode = "\033[0;34m"; // Blue
        break;
    case QtWarningMsg:
        logLevel = "WARNING";
        colorCode = "\033[38;5;214m"; // Yellow
        break;
    case QtCriticalMsg:
        logLevel = "CRITICAL";
        colorCode = "\033[0;31m"; // Red
        break;
    case QtFatalMsg:
        logLevel = "FATAL";
        colorCode = "\033[1;31m"; // Bold Red
        break;
    }

    // Extract file, line, and function name from the context
    QString fileName = context.file ? QString(context.file).split('/').last() : "Unknown file";
    int lineNumber = context.line;

    // Add padding between log level and message
    QString paddedLogLevel = logLevel.leftJustified(8,
                                                    ' '); // Ensure 10 character width for the level
    // Format the log message
    QString logMessage = QString("[%1] [%2] %3:%4: %5")
                             .arg(timestamp)
                             .arg(paddedLogLevel)
                             .arg(fileName)
                             .arg(lineNumber)
                             .arg(message);

    // Apply color to the message
    QString coloredMessage = colorCode + logMessage + "\033[0m"; // Reset color after the message

    // Write to log file
    m_textStream << logMessage << Qt::endl;

    // Output to console as well
    if (type == QtFatalMsg) {
        // For fatal errors, we can do additional handling
        std::cerr << qPrintable(coloredMessage) << std::endl;
        exit(-1);
    } else {
        std::cout << qPrintable(coloredMessage) << std::endl;
    }
}
