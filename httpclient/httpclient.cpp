
#include <boost/asio.hpp>
#include <iostream>
#include <boost/system/error_code.hpp>

class client
{
public:
	int target_port;

	void connectToSocket(std::string message)
	{
		using namespace boost::asio;

		io_context context;
		boost::system::error_code ec;
		ip::tcp::endpoint endpoint(ip::make_address_v4("127.0.0.1", ec), target_port);
		ip::tcp::socket socket(context);
		streambuf readBuffer;
		socket.connect(endpoint, ec);

		if(socket.is_open())
		{
			
			{

				socket.read_some(readBuffer);
				
				socket.write_some(buffer(message), ec);

				std::string readData = boost::asio::buffer_cast<const char*>(readBuffer.data());

				std::cout << "Server responded with : \n" << readData;
				if (!ec)
				{
					std::cout << "Client connected successfully \n";
				}
				else
				{
					std::cout << "Client error" << ec.message() << "\n";
				}
			}
			
		}
		
		
		
	}
};

int main()
{
  
	client client;
	client.target_port = 8000;
	client.connectToSocket("big chungus");
}


