#pragma once
#include "compressionlib.h"
class ImageCompressor : Compressor
{
public:
	std::map<std::string, std::string>* imageCodecMap;
	ImageCompressor(std::map<std::string, std::string>* codecMap);
	~ImageCompressor();
	void InitializeImgCodec();
	void DecompressImg(std::string compressedFile);
	void CompressImg(std::string decompressedFile);
};

