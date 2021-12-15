// httpserver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iomanip>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <format>
//SERVER PART

class server
{
public:
	int port;

	boost::system::error_code ec;
	std::string url = "http://www.example.org/index.asp";
	std::string requestString = std::format(
		"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");


	void getResponse(boost::asio::ip::tcp::socket& socket)
	{
		namespace http = boost::beast::http;
		std::cout << requestString;

		std::vector buffer(requestString.size(), requestString.data());


		std::string stringData(buffer[0]);

		std::cout << stringData;
		std::cout << "buffer says";

		read(socket, boost::asio::buffer(buffer));
	}


	void createServer()
	{
		using namespace boost::asio;

		io_context context;

		for (;;)
		{
			ip::tcp::socket socket(context);

			streambuf writeBuffer;

			ip::tcp::endpoint endpoint(ip::tcp::v4(), port);


			ip::tcp::acceptor acceptor(context, endpoint);

			acceptor.accept(socket, ec);
			std::cout << "Connected! \n";

			{
				std::cout << "Request: " << requestString << "\n";

				write(socket, buffer(requestString.data(), requestString.size()), ec);


				getResponse(socket);


				if (ec)
				{
					std::cout << "Error has occured \n" << ec.message();
					break;
				}
			}
		}
	}
};

int main()
{
	int port = 8000;

	server server;
	server.port = port;
	server.createServer();
}
