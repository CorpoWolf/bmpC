#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct {
	uint16_t type;
	uint32_t size;
	uint16_t reserved1, reserved2;
	uint32_t offset;
} BMPFileHeader;

typedef struct {
	uint32_t size;
	int32_t width, height;
	uint16_t planes;
	uint16_t bitCount;
	uint32_t compression;
	uint32_t sizeImage;
	int32_t xPelsPerMeter, yPelsPerMeter;
	uint32_t clrUsed, clrImportant;
} BMPInfoHeader;

#pragma pack(pop)

typedef struct {
	uint8_t blue, green, red;
} RGB;

int main() {
	int width = 80, height = 80;
	BMPFileHeader fileHeader = {0x4D42, 0, 0, 0, 54};
	BMPInfoHeader infoHeader = {
		40, width, height, 1, 24, 0, width * height * 3, 0, 0, 0, 0
	};
	fileHeader.size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + infoHeader.sizeImage;

	RGB *pixelData = (RGB *)malloc(infoHeader.sizeImage);
	if (!pixelData) {
		perror("Memory allocation failed");
		return EXIT_FAILURE;
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			if (y < height / 2) {
				if (x < width / 2) {
					pixelData[index] = (RGB){0, 0, 255}; // Red quadrant
				} else {
					pixelData[index] = (RGB){0, 255, 0}; // Green quadrant
				}
			} else {
				if (x < width / 2) {
					pixelData[index] = (RGB){255, 0, 0}; // White quadrant
				} else {
					pixelData[index] = (RGB){0, 0, 0}; // Filling the rest with black for simplicity
				}
			}
		}
	}

	FILE* file = NULL;
	errno_t err = fopen_s(&file, "example.bmp", "wb");
	if (err != 0) {
		perror("Unable to open file");
		free(pixelData);
		return EXIT_FAILURE;
	}

	fwrite(&fileHeader, sizeof(fileHeader), 1, file);
	fwrite(&infoHeader, sizeof(infoHeader), 1, file);
	fwrite(pixelData, infoHeader.sizeImage, 1, file);

	free(pixelData);
	fclose(file);
	return EXIT_SUCCESS;
}
