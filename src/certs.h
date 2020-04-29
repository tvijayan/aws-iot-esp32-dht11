#ifndef certs_h
#define certs_h

// Amazon's root CA. This should be the same for everyone.
const char* AWS_CERT_CA = "-----BEGIN CERTIFICATE-----\n" \
"----------------------------------------------------------------\n" \
"----------------------------------------------------------------\n" \
"----------------------------------------------------------------\n" \
"-----END CERTIFICATE-----";

// The private key for the device
const char* AWS_CERT_PRIVATE = "-----BEGIN RSA PRIVATE KEY-----\n" \
"----------------------------------------------------------------\n" \
"----------------------------------------------------------------\n" \
"----------------------------------------------------------------\n" \
"-----END RSA PRIVATE KEY-----";

// The certificate for the device
const char* AWS_CERT_CRT = "-----BEGIN CERTIFICATE-----\n" \
"----------------------------------------------------------------\n" \
"----------------------------------------------------------------\n" \
"----------------------------------------------------------------\n" \
"-----END CERTIFICATE-----";

#endif
