// Server.cpp
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    try
    {
        // Initialize the networking library
        boost::asio::io_service io_service;

        // Create a TCP acceptor to listen for incoming connections
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

        // Accept incoming connections and handle them one by one
        while (true)
        {
            // Wait for a new client to connect
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            // Read data from the client
            boost::asio::streambuf buffer;
            boost::asio::read_until(socket, buffer, '\n');
            std::string message = boost::asio::buffer_cast<const char*>(buffer.data());
            message.erase(message.size() - 1);

            // Print the received message to the console
            std::cout << "Received message: " << message << std::endl;

            // Echo the message back to the client
            boost::asio::write(socket, boost::asio::buffer(message + "\n"));
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
