#include "pch.h"
#include "CardInformationExtracter.h"
#include "c:\src\vcpkg\installed\x64-windows\include\curl\curl.h"

std::string makeUrl(std::string cardInformation) {
	CardInformationExtracter cie = CardInformationExtracter(cardInformation);
	
	std::string url = "http://localhost:8080";

	// Add trailing digits
	url += "?trailing=" + cie.extractTrailingDigits();

	std::string cardType = cie.extractCardType();
	if (cardType != "") {
		url += "&card_type=" + cardType;
	}

	std::string expiryDate = cie.extractExpiryDate();
	if (expiryDate != "") {
		url += "&expiry_date=" + expiryDate;
	}

	return url;
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*) userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool makeRequest(const std::string& url, std::string& customers) {
	CURL *curl;
	CURLcode res;

	// Initialise the CURL
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	// Set the request options
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &customers);

	// Perform the request
	res = curl_easy_perform(curl);

	// Cleanup
	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return res == CURLE_OK;
}

std::string getCustomers(const std::string& cardInformation) {
	std::string url = makeUrl(cardInformation);
	std::string customers;

	if (makeRequest(url, customers)) {
		return customers;
	}

	throw std::runtime_error("There was an error performing the request");
}

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
	/*testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();*/

	std::string cardInfo = getCardInformationFromUser();

	try {
		std::string customers = getCustomers(cardInfo);
		std::cout << "\nCustomers:\n" << customers << std::endl;
	}
	catch (std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
}