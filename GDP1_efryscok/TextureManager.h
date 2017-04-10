#pragma once

#include <string>
#include <map>

struct S24BitBMPPixel {
	unsigned char redPixel;
	unsigned char greenPixel;
	unsigned char bluePixel;
};

class CTextureManager {
private:
	unsigned long mFileSize;
	unsigned short mReserved1;
	unsigned short mReserved2;
	unsigned long mOffsetInBits;
	unsigned long mHeaderSize;
	unsigned long mNumberOfRows;
	unsigned long mHeight;
	unsigned long mNumberOfColumns;
	unsigned long mWidth;
	unsigned short mNumberOfPlanes;
	unsigned short mBitPerPixel;
	unsigned long mCompressionMode;
	unsigned long mImageSizeInBytes;
	unsigned long mPixelsPerMeterX;
	unsigned long mPixelsPerMeterY;
	unsigned long mNumberOfLookUpTableEntries;
	unsigned long mNumberOfImportantColours;
	unsigned long mOriginalHeight;
	unsigned long mOriginalWidth;
	unsigned long mPixelCount;

	S24BitBMPPixel* mImages;

	std::string mRootDir;

	std::map<std::string, GLuint> textures;

public:
	CTextureManager(std::string rootDir) : mRootDir(rootDir) {}
	~CTextureManager() {}

	bool loadCubeMap(std::string name, std::string posXFile, std::string negXFile, std::string posYFile, std::string negYFile, std::string posZFile, std::string negZFile);
	bool loadTexture(std::string textureFile);
	GLuint update(CModel* model);

private:
	unsigned short bitshiftAddToUShort(unsigned short uShort, char byte, int shift);
	unsigned long bitshiftAddToULong(unsigned long uLong, char byte, int shift);
	bool clearBMP();
	bool loadBMP(std::string bmpFile);
	char readNextChar(char* data, unsigned long& index);
	unsigned short readNextUShort(char* data, unsigned long& index);
	unsigned long readNextULong(char* data, unsigned long& index);
};