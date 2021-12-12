// httpserver.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>

//SERVER PART

class server
{
public:
	int port;

	void createServer()
	{
		using namespace boost::asio;

		io_context context;
		boost::system::error_code ec;
		
		
		std::uint32_t size;
		for (;;) {
		ip::tcp::socket socket(context);
		streambuf readBuffer;
		streambuf writeBuffer;

		ip::tcp::endpoint endpoint(ip::tcp::v4(), port);


		ip::tcp::acceptor acceptor(context, endpoint);

		acceptor.accept(socket, ec);
		std::cout << "Connected!";
		
		{
			socket.read_some(buffer(&size, sizeof(std::uint32_t)), ec);
			std::string readData = boost::asio::buffer_cast<const char*>(readBuffer.data());

			std::string writeDataString =
				"HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 6\n\nHello!";

			socket.write_some(buffer(writeDataString.data(), writeDataString.size()), ec);

			
			std::cout << readData << "\n";


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
