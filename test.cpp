#include "pch.h"
#include "CardInformationExtracter.h"

const std::string masterCardSlip = "MASTERCARD Auth Code: 759830 Merchant ID: 887 Account Number: ************3456 Expiry: 08/15 NO CARDHOLDER VERIFICATION";
const std::string visaSlip = "Please debit my account Visa Debit 8768xxxxxxxx7682 Auth Code : 87ff6f";
const std::string invalidSlip = "Auth Code: 759830 Merchant ID: 887 Account Number: ************3456 Expiry: 08/15 NO CARDHOLDER VERIFICATION";

class CardInformationExtracterExtracts : public testing::Test {
public:
	CardInformationExtracter invalidCard = CardInformationExtracter(invalidSlip);
	CardInformationExtracter masterCard = CardInformationExtracter(masterCardSlip);
	CardInformationExtracter visaCard = CardInformationExtracter(visaSlip);
};


TEST_F(CardInformationExtracterExtracts, ReturnsAnEmptyStringWhenNoCardTypeIsPresent) {
	ASSERT_EQ(invalidCard.extractCardType(), "");
}

TEST_F(CardInformationExtracterExtracts, TheCorrectCardType) {
	ASSERT_EQ(masterCard.extractCardType(), "mastercard");
	ASSERT_EQ(visaCard.extractCardType(), "visa");
}

TEST_F(CardInformationExtracterExtracts, TheCorrectTrailingDigits) {
	ASSERT_EQ(masterCard.extractTrailingDigits(), "3456");
	ASSERT_EQ(visaCard.extractTrailingDigits(), "7682");
}

TEST_F(CardInformationExtracterExtracts, ReturnsEmptyStringIfNoExpiryDate) {
	ASSERT_EQ(visaCard.extractExpiryDate(), "");
}

TEST_F(CardInformationExtracterExtracts, TheCorrectExpiryDate) {
	ASSERT_EQ(masterCard.extractExpiryDate(), "08/15");
}