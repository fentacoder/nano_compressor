#include "ImageCompression.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>

ImageCompressor::ImageCompressor(std::map<std::string,std::string>* codecMap) {
    this->imageCodecMap = codecMap;
}

void ImageCompressor::InitializeImgCodec() {
    std::ifstream textFile;
    textFile.open("image_compression.txt");
    std::string incomingTxt;

    while (std::getline(textFile, incomingTxt)) {
        if (incomingTxt.find(",") != std::string::npos) {
            std::string* incomingTextPtr = &incomingTxt;
            std::string compStr = incomingTxt.substr(0, incomingTxt.find("-"));
            compStr = trim(compStr);
            std::string binaryStr = incomingTxt.substr(incomingTxt.find("-") + 1, sizeof(incomingTxt) - 1);
            binaryStr = trim(binaryStr);

            std::pair<std::string, std::string> tempPair = std::make_pair(compStr, binaryStr);
            this->imageCodecMap.insert(tempPair);
            incomingTxt = "";
        }
    }

    textFile.close();
}

void ImageCompressor::DecompressImg(std::string compressedFile) {
    std::ifstream textFile;
    std::ofstream binaryFile;
    textFile.open(compressedFile);
    std::string incomingTxt;
    char binary_character;
    std::string binaryStr;
    int numberOfLines = 0;
    int tempCount = 0;
    this->InitializeImgCodec();

    std::string fileName = compressedFile.substr(0, sizeof(compressedFile) - 5);
    bool fileErrors = this->OpenBinaryFile(fileName);
    if (!fileErrors) {
        binaryFile.open(fileName, std::ios::out | std::ios::binary | std::ios::app);

        while (!textFile.eof()) {
            textFile.get(binary_character);
            incomingTxt += binary_character;
            if (incomingTxt.find("\n") != std::string::npos) {
                std::string compChar = incomingTxt.substr(0, 1);
                std::stringstream repeatNumStr(incomingTxt.substr(1, sizeof(incomingTxt)));
                int repeatNum = 0;
                repeatNumStr >> repeatNum;
                std::string convertedStr = this->CharToBinaryImgStr(compChar);
                std::string formattedStr = "";
                for (int i = 0; i < repeatNum; i++) {

                    formattedStr += convertedStr;
                }
                //write the binary comp str equiv to the text file
                this->SaveBinaryFile(binaryFile, formattedStr);
                incomingTxt = "";
            }
        }

        textFile.close();
        binaryFile.close();
    }
}

void ImageCompressor::CompressImg(std::string decompressedFile) {
    std::ifstream textFile;
    std::ofstream compressedFile;
    compressedFile.open(decompressedFile + ".nano");
    textFile.open(decompressedFile);
    std::string incomingTxt, prevStr, outputStr;
    char binary_character;
    std::string binaryStr;
    int numberOfLines = 0;
    int tempCount = 0;
    int repeatNum = 1;
    this->InitializeImgCodec();

    while (!textFile.eof()) {
        if (tempCount == 6) {
            if (incomingTxt == prevStr) {
                tempCount = 0;
                repeatNum++;
                incomingTxt = "";
            }
            else {
                /*the previous string gets written to the text file before
                being updated to the current string*/
                compressedFile << this->BinaryImgStrToChar(prevStr) + std::to_string(repeatNum) + ",\n";
                prevStr = incomingTxt;
                tempCount = 0;
                repeatNum = 1;
                incomingTxt = "";
            }
        }
        else {
            textFile.get(binary_character);
            incomingTxt += binary_character;

        }

    }

    textFile.close();
    compressedFile.close();
}

ImageCompressor::~ImageCompressor() {
    delete(this->imageCodecMap);
}