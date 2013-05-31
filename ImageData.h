#pragma once
//ImageData.h
//ImageData represents a layered image
//ImageData stores the bytes of the image, 16 bits per pixel
namespace forms2{
	using namespace System;
	using namespace System::IO;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace DataStructures;
	
	public ref class ImageData
	{
	public:
		ImageData(UInt16* b,int r, int c, int l, bool d,bool sf, DateTime dt){
			init(b,r,c,l,d,sf,dt);
		}
		~ImageData(){
		}

		UInt16 getValue(int i);
		UInt16 getValue(int r,int c,int l,int frame);
		int getRows(){return rows;}
		int getCols(){return cols;}
		int getLayers(){return layers;}
		int getLength(){return length;}
		int getDoubler(){return dbl;}
		DateTime getDateTime(){return dateTime;}
		bool isDouble(){return (dbl==2);}
		bool getSaved(){return saved;}

		String^ getDateTimeString();
		UInt16 getMaxValue(int layer, int frame);
		UInt16 getMaxValue(int layer);
		void saveFile(String^ path, String^ format);
		void setSeqVars(LinkedList<Variable^>^ vars);
		LinkedList<Variable^>^ getSeqVars(){return seqVars;}

	private:
		array<UInt16>^ imageBuffer;
		LinkedList<Variable^>^ seqVars;
		int rows;
		int cols;
		int layers;
		int length;
		int dbl;
		bool saved;
		bool singleFrame;
		DateTime dateTime;//time and date when this ImageData object was created

		void init(UInt16* b, int r, int c, int l, bool d, bool sf, DateTime dt);
		void saveFileAIA(String^ path);
		void saveFileDus(String^ path);
	};
}