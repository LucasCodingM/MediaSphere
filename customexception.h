#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <QException>
#include <QList>
#include <QString>

class CustomException : public QException
{
public:
    CustomException(const QString &message, const char *file, int line)
        : m_errorMessage(message)
        , m_fileName(file)
        , m_lineNumber(line)
    {
        QString fileNameSplitted = QString(m_fileName).split('/').last();
        m_errorDetailMessage = QString("Exception at %1:%2:  %3")
                                   .arg(fileNameSplitted)
                                   .arg(m_lineNumber)
                                   .arg(m_errorMessage)
                                   .toUtf8()
                                   .constData();
    }

    const char *what() const noexcept override { return m_errorDetailMessage; }

    void raise() const override
    {
        throw *this; // Throw the exception
    }
    CustomException *clone() const override
    {
        return new CustomException(*this); // Clone the exception
    }

    const QString getMessage() const
    {
        return m_errorMessage; // Return the error message
    }

private:
    QString m_errorMessage;       // The message to store in the exception
    const char *m_errorDetailMessage; // The detail message to store in the exception
    const char *m_fileName;
    int m_lineNumber;
};

#define THROW_CUSTOM_EXCEPTION(msg) throw CustomException(msg, __FILE__, __LINE__)

#endif // CUSTOMEXCEPTION_H
