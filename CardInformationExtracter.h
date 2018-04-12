#pragma once
#ifndef CARD_INFORMATION_EXTRACTER_H
#define CARD_INFORMATION_EXTRACTER_H

#include <algorithm>
#include <regex>

class CardInformationExtracter {
public:
	CardInformationExtracter(std::string cardInfo) : cardInformation(cardInfo) {
		lowercaseString(cardInformation);
	}

	const std::string extractCardType() const {
		for (std::string cardType : cardTypes) {
			if (cardInformation.find(cardType) != std::string::npos) {
				return cardType;
			}
		}
		return "";
	}

	const std::string extractTrailingDigits() const {
		std::regex accountNumRegex(accountNumberRegex);
		std::smatch matches;

		if (std::regex_search(cardInformation, matches, accountNumRegex)) {
			return matches[1];
		}
		
		return "";
	}

	const std::string extractExpiryDate() const {
		std::regex dateRegex(expiryDateRegex);
		std::smatch matches;

		if (std::regex_search(cardInformation, matches, dateRegex)) {
			return matches[0];
		}

		return "";
	}

private:
	std::string cardInformation;
	std::string expiryDateRegex = "\\b\\d\\d/\\d\\d\\b";
	std::string accountNumberRegex = "[x*]{7,}(\\d{4})";

	std::string cardTypes[2] = {
		"mastercard", "visa"
	};

	void lowercaseString(std::string& cardInformation) {
		std::transform(cardInformation.begin(), cardInformation.end(), cardInformation.begin(), ::tolower);
	}
};

#endif