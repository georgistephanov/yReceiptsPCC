#include "pch.h"
#include "c:\src\vcpkg\installed\x64-windows\include\curl\curl.h"
#include "ClientsHttpRequest.h"
#include "CardInformationExtracter.h"

std::string ClientsHttpRequest::generateUrlFromCardInformation(const std::string& cardInformation) {
	CardInformationExtracter cie = CardInformationExtracter(cardInformation);

	std::string url = "http://localhost:8080";

	// Add the trailing digits
	url += "?trailing=" + cie.extractTrailingDigits();

	// Add the card type if it exists
	std::string cardType = cie.extractCardType();
	if (cardType != "") {
		url += "&card_type=" + cardType;
	}

	// Add the expiry date if it exists
	std::string expiryDate = cie.extractExpiryDate();
	if (expiryDate != "") {
		url += "&expiry_date=" + expiryDate;
	}

	return url;
}

std::string ClientsHttpRequest::getCustomers(const std::string& cardInformation) {
	std::string url = generateUrlFromCardInformation(cardInformation);
	std::string customers;

	if (makeRequest(url, customers)) {
		return customers;
	}

	throw std::runtime_error("There was an error performing the request");
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*) userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

bool ClientsHttpRequest::makeRequest(const std::string& url, std::string& customers) {
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