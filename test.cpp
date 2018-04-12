#include "pch.h"
#include "CardInformationExtracter.h"

const std::string masterCardSlip = "MASTERCARD Auth Code: 759830 Merchant ID: 887 Account Number: ************3456 Expiry: 08/15 NO CARDHOLDER VERIFICATION";
const std::string visaSlip = "Please debit my account Visa Debit 8768xxxxxxxx7682 Auth Code : 87ff6f";
const std::string invalidSlip = "Auth Code: 759830 Merchant ID: 887 Account Number: ************3456 Expiry: 08/15 NO CARDHOLDER VERIFICATION";

TEST(CardInformationExtracterExtracts, ReturnsAnEmptyStringWhenNoCardTypeIsPresent) {
	CardInformationExtracter *cie = new CardInformationExtracter(invalidSlip);
	ASSERT_EQ(cie->extractCardType(), "");
}

TEST(CardInformationExtracterExtracts, TheCorrectCardType) {
	CardInformationExtracter *masterCard = new CardInformationExtracter(masterCardSlip);
	ASSERT_EQ(masterCard->extractCardType(), "mastercard");

	CardInformationExtracter *visaCard = new CardInformationExtracter(visaSlip);
	ASSERT_EQ(visaCard->extractCardType(), "visa");
}

TEST(CardInformationExtracterExtracts, ReturnsTheCorrectTrailingDigits) {
	CardInformationExtracter *masterCard = new CardInformationExtracter(masterCardSlip);
	ASSERT_EQ(masterCard->extractTrailingDigits(), "3456");

	CardInformationExtracter *visaCard = new CardInformationExtracter(visaSlip);
	ASSERT_EQ(visaCard->extractTrailingDigits(), "7682");
}

TEST(CardInformationExtracterExtracts, ReturnsEmptyStringIfNoExpiryDate) {
	CardInformationExtracter *visaCard = new CardInformationExtracter(visaSlip);
	ASSERT_EQ(visaCard->extractExpiryDate(), "");
}

TEST(CardInformationExtracterExtracts, TheCorrectExpiryDate) {
	CardInformationExtracter *masterCard = new CardInformationExtracter(masterCardSlip);
	ASSERT_EQ(masterCard->extractExpiryDate(), "08/15");
}