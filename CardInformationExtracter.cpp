#include "pch.h"
#include "CardInformationExtracter.h"
#include <algorithm>
#include <regex>

CardInformationExtracter::CardInformationExtracter(std::string cardInfo) 
	: cardInformation(cardInfo) {

	lowercaseString(cardInformation);
}

const std::string CardInformationExtracter::extractTrailingDigits() const {
	std::regex accountNumRegex(accountNumberRegex);
	std::smatch matches;

	if (std::regex_search(cardInformation, matches, accountNumRegex)) {
		// The first element of matches is the part of the card number with the stars
		// The second element is just the trailing digits and that's why it is being returned
		return matches[1];
	}

	return "";
}

const std::string CardInformationExtracter::extractCardType() const {
	for (std::string cardType : cardTypes) {
		if (cardInformation.find(cardType) != std::string::npos) {
			return cardType;
		}
	}

	return "";
}

const std::string CardInformationExtracter::extractExpiryDate() const {
	std::regex dateRegex(expiryDateRegex);
	std::smatch matches;

	if (std::regex_search(cardInformation, matches, dateRegex)) {
		return matches[0];
	}

	return "";
}