// Credentials.h
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Twilio credentials, create an account and set up a sandbox
const char* account_sid = "TWILIO_ACCOUNT_ID";
const char* auth_token = "TWILIO_AUTH_TOKEN";
// %2B represnts the + in a mobile number so for a UK number you'd enter 
// something like "44798765432" in place of "TWILIO_TO_NUMBER"
const char* twilio_from = "%2B" "TWILIO_FROM_NUMBER";
const char* twilio_to = "%2B" "TWILIO_TO_NUMBER";

#endif // CREDENTIALS_H
