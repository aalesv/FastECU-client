#ifndef REMOTE_UTILITY_H
#define REMOTE_UTILITY_H
#include <QObject>
#include <QProgressBar>
#include <QPlainTextEdit>
#include "rep_remote_utility_source.h"

class RemoteUtility : public RemoteUtilitySimpleSource
{
    Q_OBJECT
public:
    explicit RemoteUtility(QObject *parent=nullptr);
    ~RemoteUtility();

    bool send_log_window_message(QString message) override;
    bool set_progressbar_value(int value) override;
    QString ping(QString message) override;

signals:
    void signal_send_log_window_message(QString message);
    void signal_set_progressbar_value(int value);

private:
};

#endif
