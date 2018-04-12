#include "pch.h"
#include "ClientsHttpRequest.h"

std::string getCardInformationFromUser() {
	std::cout << "\nInsert card information:" << std::endl;

	std::string cardInfo;
	std::string inputLine;

	while (std::getline(std::cin, inputLine)) {
		if (inputLine == "") break;
		cardInfo += inputLine + " ";
	}

	return cardInfo;
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	std::string cardInfo = getCardInformationFromUser();
	ClientsHttpRequest req = ClientsHttpRequest();

	try {
		std::string customers = req.getCustomers(cardInfo);
		std::cout << "\nCustomers:\n" << customers << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}