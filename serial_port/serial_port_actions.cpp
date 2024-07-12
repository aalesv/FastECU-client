#include "serial_port_actions.h"

SerialPortActions::SerialPortActions(QObject *parent)
    : SerialPortActionsRemoteSimpleSource{parent}
{
    serial_direct = new SerialPortActionsDirect(this);
}

SerialPortActions::~SerialPortActions()
{
    delete serial_direct;
}

bool SerialPortActions::get_serialPortAvailable()
{
    return serial_direct->serialPortAvailable;
}

bool SerialPortActions::set_serialPortAvailable(bool value)
{
    serial_direct->serialPortAvailable = value;
    return true;
}

bool SerialPortActions::get_setRequestToSend()
{
    return serial_direct->setRequestToSend;
}

bool SerialPortActions::set_setRequestToSend(bool value)
{
    serial_direct->setRequestToSend = value;
    return true;
}

bool SerialPortActions::get_setDataTerminalReady()
{
    return serial_direct->setDataTerminalReady;
}

bool SerialPortActions::set_setDataTerminalReady(bool value)
{
    serial_direct->setDataTerminalReady = value;
    return true;
}

bool SerialPortActions::get_add_iso14230_header()
{
    return serial_direct->add_iso14230_header;
}

bool SerialPortActions::set_add_iso14230_header(bool value)
{
    serial_direct->add_iso14230_header = value;
    return true;
}

bool SerialPortActions::get_is_iso14230_connection()
{
    return serial_direct->is_iso14230_connection;
}

bool SerialPortActions::set_is_iso14230_connection(bool value)
{
    serial_direct->is_iso14230_connection = value;
    return true;
}

bool SerialPortActions::get_is_can_connection()
{
    return serial_direct->is_can_connection;
}

bool SerialPortActions::set_is_can_connection(bool value)
{
    serial_direct->is_can_connection = value;
    return true;
}

bool SerialPortActions::get_is_iso15765_connection()
{
    return serial_direct->is_iso15765_connection;
}

bool SerialPortActions::set_is_iso15765_connection(bool value)
{
    serial_direct->is_iso15765_connection = value;
    return true;
}

bool SerialPortActions::get_is_29_bit_id()
{
    return serial_direct->is_29_bit_id;
}

bool SerialPortActions::set_is_29_bit_id(bool value)
{
    serial_direct->is_29_bit_id = value;
    return true;
}

bool SerialPortActions::get_use_openport2_adapter()
{
    return serial_direct->use_openport2_adapter;
}

bool SerialPortActions::set_use_openport2_adapter(bool value)
{
    serial_direct->use_openport2_adapter = value;
    return true;
}

int SerialPortActions::get_requestToSendEnabled()
{
    return serial_direct->requestToSendEnabled;
}

bool SerialPortActions::set_requestToSendEnabled(int value)
{
    serial_direct->requestToSendEnabled = value;
    return true;
}

int SerialPortActions::get_requestToSendDisabled()
{
    return serial_direct->requestToSendDisabled;
}

bool SerialPortActions::set_requestToSendDisabled(int value)
{
    serial_direct->requestToSendDisabled = value;
    return true;
}

int SerialPortActions::get_dataTerminalEnabled()
{
    return serial_direct->dataTerminalEnabled;
}

bool SerialPortActions::set_dataTerminalEnabled(int value)
{
    serial_direct->dataTerminalEnabled = value;
    return true;
}

int SerialPortActions::get_dataTerminalDisabled()
{
    return serial_direct->dataTerminalDisabled;
}

bool SerialPortActions::set_dataTerminalDisabled(int value)
{
    serial_direct->dataTerminalDisabled = value;
    return true;
}

uint8_t SerialPortActions::get_iso14230_startbyte()
{
    return serial_direct->iso14230_startbyte;
}

bool SerialPortActions::set_iso14230_startbyte(uint8_t value)
{
    serial_direct->iso14230_startbyte = value;
    return true;
}

uint8_t SerialPortActions::get_iso14230_tester_id()
{
    return serial_direct->iso14230_tester_id;
}

bool SerialPortActions::set_iso14230_tester_id(uint8_t value)
{
    serial_direct->iso14230_tester_id = value;
    return true;
}

uint8_t SerialPortActions::get_iso14230_target_id()
{
    return serial_direct->iso14230_target_id;
}

bool SerialPortActions::set_iso14230_target_id(uint8_t value)
{
    serial_direct->iso14230_target_id = value;
    return true;
}

QByteArray SerialPortActions::get_ssm_receive_header_start()
{
    return serial_direct->ssm_receive_header_start;
}

bool SerialPortActions::set_ssm_receive_header_start(QByteArray value)
{
    serial_direct->ssm_receive_header_start = value;
    return true;
}

QStringList SerialPortActions::get_serial_port_list()
{
    return serial_direct->serial_port_list;
}

bool SerialPortActions::set_serial_port_list(QStringList value)
{
    serial_direct->serial_port_list = value;
    return true;
}

QString SerialPortActions::get_openedSerialPort()
{
    return serial_direct->openedSerialPort;
}

bool SerialPortActions::set_openedSerialPort(QString value)
{
    serial_direct->openedSerialPort = value;
    return true;
}

QString SerialPortActions::get_subaru_02_16bit_bootloader_baudrate()
{
    return serial_direct->subaru_02_16bit_bootloader_baudrate;
}

bool SerialPortActions::set_subaru_02_16bit_bootloader_baudrate(QString value)
{
    serial_direct->subaru_02_16bit_bootloader_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_04_16bit_bootloader_baudrate()
{
    return serial_direct->subaru_04_16bit_bootloader_baudrate;
}

bool SerialPortActions::set_subaru_04_16bit_bootloader_baudrate(QString value)
{
    serial_direct->subaru_04_16bit_bootloader_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_02_32bit_bootloader_baudrate()
{
    return serial_direct->subaru_02_32bit_bootloader_baudrate;
}

bool SerialPortActions::set_subaru_02_32bit_bootloader_baudrate(QString value)
{
    serial_direct->subaru_02_32bit_bootloader_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_04_32bit_bootloader_baudrate()
{
    return serial_direct->subaru_04_32bit_bootloader_baudrate;
}

bool SerialPortActions::set_subaru_04_32bit_bootloader_baudrate(QString value)
{
    serial_direct->subaru_04_32bit_bootloader_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_05_32bit_bootloader_baudrate()
{
    return serial_direct->subaru_05_32bit_bootloader_baudrate;
}

bool SerialPortActions::set_subaru_05_32bit_bootloader_baudrate(QString value)
{
    serial_direct->subaru_05_32bit_bootloader_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_02_16bit_kernel_baudrate()
{
    return serial_direct->subaru_02_16bit_kernel_baudrate;
}

bool SerialPortActions::set_subaru_02_16bit_kernel_baudrate(QString value)
{
    serial_direct->subaru_02_16bit_kernel_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_04_16bit_kernel_baudrate()
{
    return serial_direct->subaru_04_16bit_kernel_baudrate;
}

bool SerialPortActions::set_subaru_04_16bit_kernel_baudrate(QString value)
{
    serial_direct->subaru_04_16bit_kernel_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_02_32bit_kernel_baudrate()
{
    return serial_direct->subaru_02_32bit_kernel_baudrate;
}

bool SerialPortActions::set_subaru_02_32bit_kernel_baudrate(QString value)
{
    serial_direct->subaru_02_32bit_kernel_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_04_32bit_kernel_baudrate()
{
    return serial_direct->subaru_04_32bit_kernel_baudrate;
}

bool SerialPortActions::set_subaru_04_32bit_kernel_baudrate(QString value)
{
    serial_direct->subaru_04_32bit_kernel_baudrate = value;
    return true;
}

QString SerialPortActions::get_subaru_05_32bit_kernel_baudrate()
{
    return serial_direct->subaru_05_32bit_kernel_baudrate;
}

bool SerialPortActions::set_subaru_05_32bit_kernel_baudrate(QString value)
{
    serial_direct->subaru_05_32bit_kernel_baudrate = value;
    return true;
}

QString SerialPortActions::get_can_speed()
{
    return serial_direct->can_speed;
}

bool SerialPortActions::set_can_speed(QString value)
{
    serial_direct->can_speed = value;
    return true;
}

QString SerialPortActions::get_serial_port_baudrate()
{
    return serial_direct->serial_port_baudrate;
}

bool SerialPortActions::set_serial_port_baudrate(QString value)
{
    serial_direct->serial_port_baudrate = value;
    return true;
}

QString SerialPortActions::get_serial_port_linux()
{
    return serial_direct->serial_port_linux;
}

bool SerialPortActions::set_serial_port_linux(QString value)
{
    serial_direct->serial_port_linux = value;
    return true;
}

QString SerialPortActions::get_serial_port_windows()
{
    return serial_direct->serial_port_windows;
}

bool SerialPortActions::set_serial_port_windows(QString value)
{
    serial_direct->serial_port_windows = value;
    return true;
}

QString SerialPortActions::get_serial_port()
{
    return serial_direct->serial_port;
}

bool SerialPortActions::set_serial_port(QString value)
{
    serial_direct->serial_port = value;
    return true;
}

QString SerialPortActions::get_serial_port_prefix()
{
    return serial_direct->serial_port_prefix;
}

bool SerialPortActions::set_serial_port_prefix(QString value)
{
    serial_direct->serial_port_prefix = value;
    return true;
}

QString SerialPortActions::get_serial_port_prefix_linux()
{
    return serial_direct->serial_port_prefix_linux;
}

bool SerialPortActions::set_serial_port_prefix_linux(QString value)
{
    serial_direct->serial_port_prefix_linux = value;
    return true;
}

QString SerialPortActions::get_serial_port_prefix_win()
{
    return serial_direct->serial_port_prefix_win;
}

bool SerialPortActions::set_serial_port_prefix_win(QString value)
{
    serial_direct->serial_port_prefix_win = value;
    return true;
}

uint32_t SerialPortActions::get_can_source_address()
{
    return serial_direct->can_source_address;
}

bool SerialPortActions::set_can_source_address(uint32_t value)
{
    serial_direct->can_source_address = value;
    return true;
}

uint32_t SerialPortActions::get_can_destination_address()
{
    return serial_direct->can_destination_address;
}

bool SerialPortActions::set_can_destination_address(uint32_t value)
{
    serial_direct->can_destination_address = value;
    return true;
}

uint32_t SerialPortActions::get_iso15765_source_address()
{
    return serial_direct->iso15765_source_address;
}

bool SerialPortActions::set_iso15765_source_address(uint32_t value)
{
    serial_direct->iso15765_source_address = value;
    return true;
}

uint32_t SerialPortActions::get_iso15765_destination_address()
{
    return serial_direct->iso15765_destination_address;
}

bool SerialPortActions::set_iso15765_destination_address(uint32_t value)
{
    serial_direct->iso15765_destination_address = value;
    return true;
}


bool SerialPortActions::is_serial_port_open()
{
    return serial_direct->is_serial_port_open();
}

int SerialPortActions::change_port_speed(QString portSpeed)
{
    return serial_direct->change_port_speed(portSpeed);
}

int SerialPortActions::fast_init(QByteArray output)
{
    return serial_direct->fast_init(output);
}

int SerialPortActions::set_lec_lines(int lec1, int lec2)
{
    return serial_direct->set_lec_lines(lec1, lec2);
}

int SerialPortActions::pulse_lec_1_line(int timeout)
{
    return serial_direct->pulse_lec_1_line(timeout);
}

int SerialPortActions::pulse_lec_2_line(int timeout)
{
    return serial_direct->pulse_lec_2_line(timeout);
}

bool SerialPortActions::reset_connection()
{
    serial_direct->reset_connection();
    return true;
}

QByteArray SerialPortActions::read_serial_data(uint32_t datalen, unsigned long timeout)
{
    return serial_direct->read_serial_data(datalen, timeout);
}

QByteArray SerialPortActions::write_serial_data(QByteArray output)
{
    return serial_direct->write_serial_data(output);
}

QByteArray SerialPortActions::write_serial_data_echo_check(QByteArray output)
{
    return serial_direct->write_serial_data_echo_check(output);
}

int SerialPortActions::clear_rx_buffer()
{
    return serial_direct->clear_rx_buffer();
}

int SerialPortActions::clear_tx_buffer()
{
    return serial_direct->clear_tx_buffer();
}

int SerialPortActions::send_periodic_j2534_data(QByteArray output, int timeout)
{
    return serial_direct->send_periodic_j2534_data(output, timeout);
}

int SerialPortActions::stop_periodic_j2534_data()
{
    return serial_direct->stop_periodic_j2534_data();
}

QStringList SerialPortActions::check_serial_ports()
{
    return serial_direct->check_serial_ports();
}

QString SerialPortActions::open_serial_port()
{
    return serial_direct->open_serial_port();
}
