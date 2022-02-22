#include "otherview-message.h"
#include <zmqpp/zmqpp.hpp>
#include "config.h"
#include "debugwriter.h"

OtherViewMessager::OtherViewMessager(const Config &c):
    conf(c)
{
    isOtherView = c.isOtherView;
    otherViewEndpoint = "tcp://127.0.0.1:9697";
    normalEndpoint = "tcp://127.0.0.1:7536";

    if (isOtherView) {
        otherview_socket_type = zmqpp::socket_type::push;
        normal_socket_type = zmqpp::socket_type::pull;
    } else {
        otherview_socket_type = zmqpp::socket_type::pull;
        normal_socket_type = zmqpp::socket_type::push;
    }

    otherview_socket = new zmqpp::socket (otherview_context, otherview_socket_type);
    normal_socket = new zmqpp::socket (normal_context, normal_socket_type);

    if (isOtherView) {
        otherview_socket->connect(otherViewEndpoint);
        normal_socket->connect(normalEndpoint);
    } else {
        otherview_socket->bind(otherViewEndpoint);
        normal_socket->bind(normalEndpoint);
    }
}

void OtherViewMessager::sendMsg(const std::string &string)
{
    zmqpp::message message;
    message << string;
    bool ret;
    if (isOtherView) {
        ret = otherview_socket->send(message, true);
    } else {
        ret = normal_socket->send(message, true);
    }
    Debug() << "Sent message: ";
    Debug() << string;
    Debug() << ret;
}

std::string OtherViewMessager::getMsg()
{
    zmqpp::message message;
    std::string response;
    bool ret;
    if (isOtherView) {
        ret = normal_socket->receive(message, true);
    } else {
        ret = otherview_socket->receive(message, true);
    }
    Debug() << "Received message: ";
    message >> response;
    Debug() << response;
    Debug() << ret;
    return response;
}

void OtherViewMessager::close() 
{
    otherview_socket->close();
    normal_socket->close();
}