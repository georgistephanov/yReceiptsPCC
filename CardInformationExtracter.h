#pragma once
#ifndef CARD_INFORMATION_EXTRACTER_H
#define CARD_INFORMATION_EXTRACTER_H

class CardInformationExtracter {
public:
	CardInformationExtracter(std::string);

	const std::string extractCardType() const;
	const std::string extractTrailingDigits() const;
	const std::string extractExpiryDate() const;

private:
	std::string cardInformation;
	std::string expiryDateRegex = "\\b\\d\\d/\\d\\d\\b";
	std::string accountNumberRegex = "[x*]{7,}(\\d{4})";

	std::string cardTypes[2] = {
		"mastercard", "visa"
	};

	inline void lowercaseString(std::string& cardInformation) {
		std::transform(cardInformation.begin(), cardInformation.end(), cardInformation.begin(), ::tolower);
	}
};

#endif