#pragma once
class Compressor {
public:
    char codeStr[6];
    std::map<std::string, std::string> codecMap;

    Compressor() {}
    ~Compressor() {}

    void ClearCodecMap();

    std::string BinaryImgStrToChar(std::string binaryStr);

    

    std::string CharToBinaryImgStr(std::string compStr);

    void SetData(std::string codeStr);

    void SaveBinaryFile(std::ofstream& of, std::string binaryStr);

    bool OpenBinaryFile(std::string strFile);

    void ReadBinaryFile(std::string strFile);

    void ReadTextFile();

    static inline void ltrim(std::string& s);

    static inline void rtrim(std::string& s);

    static inline std::string trim(std::string& s);
};

