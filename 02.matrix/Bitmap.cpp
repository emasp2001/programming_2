// Pablo Sauma Chacon
// August, 2020
#ifndef BITMAP 
#define BITMAP
#include <stdio.h>
class Bitmap{
	public:
		// 1-byte [height][width] array, color palette customizable with a BGR table
		template<typename T> static bool save_8bitmap(const char* filename,T** image,unsigned int width,unsigned int height,const unsigned char** colorPalette=0,unsigned int paletteSize=0){
			const unsigned char* defaultPalette[16];
			if(!colorPalette){
				for(unsigned int i=0;i<16;i++){ defaultPalette[i] = (const unsigned char*)(defaultColorPalette[i]); }
				colorPalette = (const unsigned char**)(defaultPalette);
				paletteSize = 16; 
			}
			FILE* file;
			if(file = fopen(filename,"wb")){
				unsigned int imageSize = getImageSize(width,height,1);
				writeBitmapHeader(file,40 + (paletteSize*4),imageSize);
				writeDibHeader(file,width,height,imageSize,8,0,colorPalette,paletteSize);
				writeImage2D(file,image,width,height,1);
				fclose(file);
			}
			return file;
		}
		// RGB [height][width][channel] array
		static bool save_24bitmap(const char* filename,unsigned char*** image,unsigned int width,unsigned int height){
			FILE* file;
			if(file = fopen(filename,"wb")){
				unsigned int imageSize = getImageSize(width,height,3);
				writeBitmapHeader(file,40,imageSize);
				writeDibHeader(file,width,height,imageSize,24);
				writeImage(file,image,width,height,3);
				fclose(file);
			}
			return file;
		}
		// RGBA [height][width][channel] array
		static bool save_32bitmap(const char* filename,unsigned char*** image,unsigned int width,unsigned int height){
			FILE* file;
			if(file = fopen(filename,"wb")){
				unsigned int imageSize = getImageSize(width,height,4);
				writeBitmapHeader(file,108,imageSize);
				writeDibHeader(file,width,height,imageSize,32,3);
				writeImage(file,image,width,height,4);
				fclose(file);
			}
			return file;
		}
	private:
		static unsigned int getImageSize(unsigned int width, unsigned int height,unsigned int depth){
			unsigned int rowSize = width*depth;
			rowSize += (4 - (rowSize%4))%4;
			return rowSize*height;
		}
		static void writeBitmapHeader(FILE* file,unsigned int dibHeaderSize,unsigned int imageSize){
			unsigned int offset = 14+dibHeaderSize;
			unsigned int fileSize = offset+imageSize;
			fwrite("BM",1,2,file);
			fwrite(&fileSize,4,1,file);
			fwrite("\0\0\0\0",1,4,file);
			fwrite(&offset,4,1,file);
		}
		static void writeDibHeader(FILE* file,unsigned int width,unsigned int height,unsigned int imageSize,unsigned short bits,unsigned int compression=0,const unsigned char** colorPalette=0,unsigned int paletteSize=0){
			unsigned int headerSize = (compression==3)?108:40;
			unsigned int zero = 0;
			unsigned int resolution = 2835;
			unsigned short planes = 1;
			unsigned char czero = 0;
			fwrite(&headerSize,4,1,file);
			fwrite(&width,4,1,file);
			fwrite(&height,4,1,file);
			fwrite(&planes,2,1,file);
			fwrite(&bits,2,1,file);
			fwrite(&compression,4,1,file);
			fwrite(&imageSize,4,1,file);
			fwrite(&resolution,4,1,file);
			fwrite(&resolution,4,1,file);
			fwrite(&paletteSize,4,1,file);
			fwrite(&zero,4,1,file);
			for(unsigned int c=0;c<paletteSize;c++){
				for(unsigned int channel=0;channel<3;channel++){ fwrite(&(colorPalette[c][channel]),1,1,file); }
				fwrite(&czero,1,1,file);
			}
			if(compression==3){ writeDibHeaderBitFields(file); }
		}
		static void writeDibHeaderBitFields(FILE* file){
			unsigned int fieldR = 0xFF0000, fieldG=0xFF00, fieldB=0xFF, fieldA=0xFF000000;
			unsigned int winSignature = 0x206E6957;
			unsigned int zero = 0;
			fwrite(&fieldR,4,1,file);
			fwrite(&fieldG,4,1,file);
			fwrite(&fieldB,4,1,file);
			fwrite(&fieldA,4,1,file);
			fwrite(&winSignature,4,1,file);
			for(int i=0;i<12;i++){ fwrite(&zero,4,1,file); }
		}
		static void writeImage(FILE* file,unsigned char*** image,unsigned int width,unsigned int height,unsigned int depth){
			unsigned int padding = (4 - (width%4))%4;
			for(unsigned int h=0;h<height;h++){
				for(unsigned int w=0;w<width;w++){
					for(int d=0;d<depth;d++){
						fwrite(&image[h][w][(d<3)?(2-d):d],1,1,file);
					}
				}
				for(unsigned int p=0;p<padding;p++){
					fwrite("\0",1,1,file);
				}
			}
		}
		template<typename T> static void writeImage2D(FILE* file,T** image,unsigned int width,unsigned int height,unsigned int depth){
			unsigned int padding = (4 - (width%4))%4;
			for(unsigned int h=0;h<height;h++){
				for(unsigned int w=0;w<width;w++){
					fwrite(&image[h][w],1,1,file);
				}
				for(unsigned int p=0;p<padding;p++){
					fwrite("\0",1,1,file);
				}
			}
		}
	private:
		static const unsigned char defaultColorPalette[16][3];
};
const unsigned char Bitmap::defaultColorPalette[16][3] = {
	{0x0,0x0,0x0},	{0x0,0x0,0x80}, {0x0,0x80,0x0}, {0x0,0x80,0x80},	// black, maroon, green, olive
	{0x80,0x0,0x0},	{0x80,0x0,0x80},{0x80,0x80,0x0},{0xC0,0xC0,0xC0},	// navy, purple, teal, silver
	{0x80,0x80,0x80},{0x0,0x0,0xFF},{0x0,0xFF,0x0}, {0x0,0xFF,0xFF},	// gray, red, lime, yellow
	{0xFF,0x0,0x0},	{0xFF,0x0,0xFF},{0xFF,0xFF,0x00},{0xFF,0xFF,0xFF}	// blue, fuchsia, cyan, white
};
#endif
