#include "compressionlib.h"
#include "ImageCompression.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
#include<sstream>



Compressor::Compressor() {}
Compressor::~Compressor() {}

void Compressor::ClearCodecMap() {
    this->codecMap.clear();
}

std::string Compressor::BinaryImgStrToChar(std::string binaryStr) {
    for (const auto& codecPair : this->codecMap) {
        if (codecPair.second == binaryStr) {
            return codecPair.first;
        }
    }
}

std::string Compressor::CharToBinaryImgStr(std::string compStr) {
    for (const auto& codecPair : this->codecMap) {
        if (codecPair.first == compStr) {
            return codecPair.second;
        }
    }
}

void Compressor::SetData(std::string codeStr) {
    std::sprintf(this->codeStr, "%s", codeStr);
}

void Compressor::SaveBinaryFile(std::ofstream& of, std::string binaryStr) {
    of.write((char*)&binaryStr, sizeof(binaryStr));
}

bool Compressor::OpenBinaryFile(std::string strFile) {
    std::ofstream fs;
    fs.open(strFile, std::ios::out | std::ios::binary | std::ios::app);
    if (!fs.is_open()) {
        std::cout << "cannot open file " << strFile << std::endl;
        fs.close();
        return true;
    }
    else {
        fs.close();
        return false;
    }
}

void Compressor::ReadBinaryFile(std::string strFile) {
    std::string mimeType = strFile.substr(strFile.find(".") + 1, sizeof(strFile));
    if (mimeType == "png" || mimeType == "jpg" || mimeType == "jpeg" || mimeType == "gif") {
        ImageCompressor* imageCompressor = new ImageCompressor(&this->codecMap);
        imageCompressor->DecompressImg(strFile);
        delete(imageCompressor);
    }
    //Compression c;
    //int size = 0;

    //binaryFile.open(strFile,std::ios::in | std::ios::binary);
    //binaryFile.seekg(0,std::ios::end);
    //size = (int) binaryFile.tellg();
    //binaryFile.seekg(0,std::ios::beg);

    // while(binaryFile.tellg() < size){
    //     binaryFile.read((char *) c.codeStr, sizeof(c.codeStr));
    //     std::cout << c.codeStr << std::endl;
    //     if(mimeType == "png" || mimeType == "jpg" || mimeType == "jpeg" || mimeType == "gif"){
    //         this->DecompressImg(c.codeStr);
    //     }

    // }

    //binaryFile.close();
}

void Compressor::ReadTextFile() {

}

void Compressor::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

void Compressor::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

std::string Compressor::trim(std::string& s) {
    ltrim(s);
    rtrim(s);
    return s;
}
