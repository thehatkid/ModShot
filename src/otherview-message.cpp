#include "otherview-message.h"
#include <zmqpp/zmqpp.hpp>
#include "config.h"
#include "debugwriter.h"

OtherViewMessager::OtherViewMessager(const Config &c):
    conf(c)
{
    isOtherView = c.isOtherView;
    otherViewEndpoint = "tcp://localhost:9697";
    normalEndpoint = "tcp://localhost:7536";

    if (isOtherView) {
        otherview_socket_type = zmqpp::socket_type::push;
        normal_socket_type = zmqpp::socket_type::pull;
    } else {
        otherview_socket_type = zmqpp::socket_type::pull;
        normal_socket_type = zmqpp::socket_type::push;
    }

    otherview_socket = new zmqpp::socket (otherview_context, otherview_socket_type);
    normal_socket = new zmqpp::socket (normal_context, normal_socket_type);

    Debug() << "Connecting to " + otherViewEndpoint;
    otherview_socket->connect(otherViewEndpoint);
    Debug() << "Connecting to " + normalEndpoint;
    normal_socket->connect(normalEndpoint);
}

void OtherViewMessager::sendMsg(const std::string &message)
{
    if (isOtherView) {
        otherview_socket->send(message);
    } else {
        normal_socket->send(message);
    }
    Debug() << "Sent message: " << message;
}

std::string OtherViewMessager::getMsg()
{
    std::string message;
    if (!isOtherView) {
        otherview_socket->receive(message);
    } else {
        normal_socket->receive(message);
    }
    Debug() << "Received message: " << message;
    return message;
}