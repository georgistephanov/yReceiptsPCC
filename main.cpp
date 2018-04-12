#include "pch.h"
#include "CardInformationExtracter.h"
#include "c:\src\vcpkg\installed\x64-windows\include\curl\curl.h"

std::string getCustomers(std::string url) {
	std::cout << url << std::endl;
	return "";
}

std::string makeUrl(std::string cardInformation) {
	std::string url = "http://localhost:8080";

	CardInformationExtracter *cie = new CardInformationExtracter(cardInformation);

	// Add trailing digits
	url += "?trailing=" + cie->extractTrailingDigits();

	std::string cardType = cie->extractCardType();
	if (cardType != "") {
		url += "&card_type=" + cardType;
	}

	std::string expiryDate = cie->extractExpiryDate();
	if (expiryDate != "") {
		url += "&expiry_date=" + expiryDate;
	}

	return url;
}

void makeRequest(std::string cardInformation) {
	std::string url = makeUrl(cardInformation);
	std::string response = getCustomers(url);

	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, url);
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		std::cout << "CURL ERROR" << std::endl;
	}

	/*curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cout << "CURL ERROR" << std::endl;
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();*/
}

int main(int argc, char **argv) {
	/*testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();*/

	std::cout << "Insert card information:" << std::endl;

	std::string cardInfo;
	std::string inputLine;

	while (std::getline(std::cin, inputLine)) {
		if (inputLine == "") break;
		cardInfo += inputLine + " ";
	}

	makeRequest(cardInfo);

	std::cout << std::endl;
}