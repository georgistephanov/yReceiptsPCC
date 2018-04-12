#pragma once
#ifndef CLIENTS_HTTP_REQUEST_H
#define CLIENTS_HTTP_REQUEST_H

class ClientsHttpRequest {
public:
	std::string getCustomers(const std::string&);

private:
	std::string generateUrlFromCardInformation(const std::string&);
	bool makeRequest(const std::string&, std::string&);
};

#endif // !CLIENTS_HTTP_REQUEST_H
