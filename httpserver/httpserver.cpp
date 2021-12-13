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
	std::vector<char> vBuffer;
	boost::system::error_code ec;
	std::string url = "http://www.example.org/index.asp";
	std::string requestString = std::format("HTTP / 1.1 301 Moved Permanently\n\nLocation: {}", url);
	
		

	auto getResponse(boost::asio::ip::tcp::socket& socket, std::string data, std::size_t size)
	{
		namespace http = boost::beast::http;

		http::response<http::string_body> res;


		read(socket, boost::asio::buffer(data, size));

		return res;
	}

	void makeRequest(boost::asio::ip::tcp::endpoint endpoint)
	{
		std::cout << "Request: " << requestString << "\n";

		write(socket, boost::asio::buffer(requestString.data(), requestString.size()), ec);
	}

	void createServer()
	{
		using namespace boost::asio;

		io_context context;


		std::uint32_t size;
		for (;;)
		{
			ip::tcp::socket socket(context);

			streambuf writeBuffer;

			ip::tcp::endpoint endpoint(ip::tcp::v4(), port);


			ip::tcp::acceptor acceptor(context, endpoint);

			acceptor.accept(socket, ec);
			std::cout << "Connected! \n";

			{
				makeRequest(endpoint);


				auto response = getResponse(socket, requestString.data(), requestString.size());

				std::cout << "Response body length :  " << response.body().size() << std::endl;
				std::cout << "Response headers  :  " << response.base() << std::endl;
				std::cout << "Response body : " << std::quoted(response.body()) << std::endl;

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
