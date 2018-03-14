/*
 * RSA_Cryption.h
 *
 *  Created on: Feb 1, 2018
 *      Author: Yusheng Xu
 */
#ifndef RSA_CRYPTION_H_
#define RSA_CRYPTION_H_

#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include <time.h>
#include <vector>

// Crypto++
#include <cryptopp/randpool.h>
#include <cryptopp/rsa.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/base64.h>
#include <cryptopp/osrng.h>

using namespace std;

void
splitString(const std::string& s, std::vector<std::string>& v, const std::string& c);

string
decryptInformation(string cipher_pathname, string private_pathanme);

bool
verifyLicense(string cipher_pathname, string private_pathanme);

#endif /* RSA_CRYPTION_H_ */
