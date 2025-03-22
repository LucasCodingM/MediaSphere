#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <QException>
#include <QList>
#include <QString>

/**
 * @class CustomException
 * @brief Custom exception class to handle errors with detailed messages.
 *
 * This class extends QException to provide custom exception handling with detailed
 * error messages, including the file name and line number where the exception occurred.
 */
class CustomException : public QException
{
public:
    /**
     * @brief Constructor for CustomException.
     *
     * Initializes the exception with a message, file name, and line number.
     * Constructs a detailed error message including the file name and line number.
     *
     * @param message The error message.
     * @param file The file name where the exception occurred.
     * @param line The line number where the exception occurred.
     */
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

    /**
     * @brief Returns the detailed error message.
     *
     * This method returns a detailed error message including the file name and line number.
     *
     * @return The detailed error message.
     */
    const char *what() const noexcept override { return m_errorDetailMessage; }

    /**
     * @brief Raises the exception.
     *
     * This method throws the current exception object.
     */
    void raise() const override
    {
        throw *this; // Throw the exception
    }

    /**
     * @brief Clones the exception.
     *
     * This method returns a new instance of the exception with the same data.
     *
     * @return A clone of the exception.
     */
    CustomException *clone() const override
    {
        return new CustomException(*this); // Clone the exception
    }

    /**
     * @brief Returns the error message.
     *
     * This method returns the original error message provided during construction.
     *
     * @return The error message.
     */
    const QString getMessage() const
    {
        return m_errorMessage; // Return the error message
    }

private:
    QString m_errorMessage; /**< The error message. */
    const char *
        m_errorDetailMessage; /**< The detailed error message including file name and line number. */
    const char *m_fileName;   /**< The file name where the exception occurred. */
    int m_lineNumber;         /**< The line number where the exception occurred. */
};

#define THROW_CUSTOM_EXCEPTION(msg) throw CustomException(msg, __FILE__, __LINE__)

#endif // CUSTOMEXCEPTION_H
