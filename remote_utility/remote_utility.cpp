// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "remote_utility.h"

RemoteUtility::RemoteUtility(QObject *parent)
    : RemoteUtilitySimpleSource(parent)
{}

RemoteUtility::~RemoteUtility()
{}

bool RemoteUtility::send_log_window_message(QString message)
{
    qDebug() << Q_FUNC_INFO << message;
    emit signal_send_log_window_message(message);
    return true;
}

bool RemoteUtility::set_progressbar_value(int value)
{
    qDebug() << Q_FUNC_INFO << value;
    emit signal_set_progressbar_value(value);
    return true;
}
