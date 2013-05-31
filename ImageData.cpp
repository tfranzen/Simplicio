#include "stdafx.h"
#include "ImageData.h"
#include <string>

namespace forms2{

	void ImageData::init(UInt16* b, int r, int c, int l, bool d, bool sf, DateTime datetime){
		//copies b to imageBuffer
		rows = r; cols = c; layers = l; singleFrame=sf;
		dateTime = datetime;
		dbl = d ? 2 : 1;
		length = dbl*r*c*l;
		imageBuffer = gcnew array<UInt16>(length);
		for (int i=0; i<length;i++)
			imageBuffer[i] = b[i];
		saved = false;
		seqVars = gcnew LinkedList<Variable^>();
		
	}
	UInt16 ImageData::getValue(int i){
		return imageBuffer[i];
	}
	UInt16 ImageData::getValue(int r,int c,int l,int frame){
		if (dbl==1 && frame!=0)
			return 0;
		else if (frame !=0 && frame !=1) 
			return 0;
		int i = c + (r+frame*rows)*cols + l*dbl*rows*cols;
		return getValue(i);
	}
	UInt16 ImageData::getMaxValue(int layer, int frame){
		UInt16 max = 0;
		UInt16 v;
		for(int r=0;r<rows;r++)
			for(int c=0;c<cols;c++){
				v = getValue(r,c,layer,frame); 
				if (v > max)
					max = v;
			}
		return max;
	}
	UInt16 ImageData::getMaxValue(int layer){
		int max0 = getMaxValue(layer,0);
		int max = max0;
		if (dbl==2){
			int max1 = getMaxValue(layer,1);
			if (max1>max0)
				max = max1;
		}
		return max;
	}
	String^ ImageData::getDateTimeString(){
		DateTime dt = dateTime;
		return String::Format("{0:d4}-{1:d2}-{2:d2}-{3:d2};{4:d2};{5:d2}",dt.Year,dt.Month,dt.Day,dt.Hour,dt.Minute,dt.Second);
	}

	void ImageData::saveFile(String^ filePath, String^ format)
	{
		
		if(String::Compare(format, "aia")==0){
			saveFileAIA(filePath);
		}else if (String::Compare(format, "dus")==0){
			saveFileDus(filePath);
		}else{
			//System::MessageBox::Show(String::Format("Unknown file format requested: {0}.",format),"Box",MessageBoxButtons::OK);
		}
	}

	void ImageData::saveFileAIA(String^ filePath)
	{	//saves a 16-bit AIA file in little endian
		
		String^ extension =".aia";
		String^ basename = String::Format("{0}\\{1}",filePath,getDateTimeString());
		String^ filename = String::Copy(basename);
		
		//prevent overwrite by renaming
		for (int i=0; (i<1000) && File::Exists(String::Concat(filename,extension));i++){
			filename =String::Format("{0} Copy {1}",basename,i);
		}
		filename = String::Concat(filename,extension);
		//if (File::Exists(filename)) return;

		FileStream^ fs = File::Open(filename,FileMode::Create);
		BinaryWriter^ bw = gcnew BinaryWriter(fs);
		try{
			Byte b0 = 0x41;
			Byte b1 = 0x49;
			Byte b2 = 0x41;
			bw->Write(b0);
			bw->Write(b1);
			bw->Write(b2);
			UInt16 intLength = 2;
			bw->Write(intLength);
			int rows2 = (getRows())*(getDoubler());
			//int cols = getCols();
			//int layers = getLayers();
			bw->Write((UInt16)rows2);
			bw->Write((UInt16)cols);
			int templayers=layers;
			if (singleFrame)
				templayers=3;
			bw->Write((UInt16)templayers);	
			
			//write data
			//for (int i=0;i<rows2*cols*layers;i++)
			//	bw->Write(getValue(i));
			
			for (int l(0); l<layers; l++)
				if (!(singleFrame && (l==0 || l > 3)))
					for (int r(0);r<rows2;r++)
						for (int c(0);c<cols;c++)
							bw->Write(getValue(r,c,l,0));
						

			//save sequence variables:
			for each(Variable^ var in seqVars){
				bw->Write(var->VariableName->ToCharArray());
				bw->Write((Byte)0);
				bw->Write((Double)var->VariableValue);
			}
			saved=true;
		}
		finally{
			bw->Close();
			fs->Close();
		}
	}
	void ImageData::saveFileDus(String^ filePath)
	{	//saves to PAR+I16 files for Duesseldorf/Sttuttgart MATLAB scripts
		
		String^ extension =".par";
		DateTime dt = dateTime;
		String^ datetime = String::Format("{3:d2}-{4:d2}-{5:d2}",dt.Year,dt.Month,dt.Day,dt.Hour,dt.Minute,dt.Second);

		String^ basename = String::Format("{0}\\{1}",filePath,datetime);
		String^ filename = String::Copy(basename);
		
		//prevent overwrite by renaming
		int i =0;
		do{
			filename = String::Format("{0}-{1:d4}",basename,i);
		} while(File::Exists(String::Concat(filename,extension)));


		filename = String::Concat(filename,extension);

		if (File::Exists(filename)) return;

		// write .par file
		FileStream^ fs = File::Open(filename,FileMode::Create);
		StreamWriter^ tw = gcnew StreamWriter(fs);
		try{
			tw->WriteLine("[data]");
			tw->WriteLine("camera=simplicio");
			tw->WriteLine(String::Format("width={0}",getCols()));
			tw->WriteLine(String::Format("height={0}",getRows()));
			switch(layers){
			case 1:
				tw->WriteLine("mode=3"); //single picture
				break;
			case 2:
				tw->WriteLine("mode=1"); // fluorescence
				break;
			case 3:
				tw->WriteLine("mode=2"); // absorption
				break;
			}
			
			// to do: exposure time!
			int j = 0;
			for each(Variable^ var in seqVars){
				tw->WriteLine(String::Format("var{0}={1}",j++,var->VariableName->ToCharArray()));
				tw->WriteLine(String::Format("{0}={1}",var->VariableName->ToCharArray(),(Double)var->VariableValue));
			}

			tw->WriteLine("[files]");
			for (int l(0); l<layers; l++)
				tw->WriteLine(String::Format("image_{0:d2}={1}-{0:d2}.I16",l,filename));
			
			//write data
			//for (int i=0;i<rows2*cols*layers;i++)
			//	bw->Write(getValue(i));
			
			for (int l(0); l<layers; l++){
				FileStream^ bfs = File::Open(String::Format("{1}-{0:d2}.I16",l,filename),FileMode::Create);
				BinaryWriter^ bw = gcnew BinaryWriter(bfs);
				try{
				if (!(singleFrame && (l==0 || l > 3)))
					for (int r(0);r<getRows();r++)
						for (int c(0);c<getCols();c++)
							bw->Write(getValue(r,c,l,0));
				}
				finally{
					bw->Close();
					bfs->Close();
				}
			}
			
			saved=true;
		}
		finally{
			tw->Close();
			fs->Close();
		}

		/*


		FileStream^ fs = File::Open(filename,FileMode::Create);
		BinaryWriter^ bw = gcnew BinaryWriter(fs);
		try{
			Byte b0 = 0x41;
			Byte b1 = 0x49;
			Byte b2 = 0x41;
			bw->Write(b0);
			bw->Write(b1);
			bw->Write(b2);
			UInt16 intLength = 2;
			bw->Write(intLength);
			int rows2 = (getRows())*(getDoubler());
			//int cols = getCols();
			//int layers = getLayers();
			bw->Write((UInt16)rows2);
			bw->Write((UInt16)cols);
			int templayers=layers;
			if (singleFrame)
				templayers=3;
			bw->Write((UInt16)templayers);	
			
			//write data
			//for (int i=0;i<rows2*cols*layers;i++)
			//	bw->Write(getValue(i));
			
			for (int l(0); l<layers; l++)
				if (!(singleFrame && (l==0 || l > 3)))
					for (int r(0);r<rows2;r++)
						for (int c(0);c<cols;c++)
							bw->Write(getValue(r,c,l,0));
						

			//save sequence variables:
			for each(Variable^ var in seqVars){
				bw->Write(var->VariableName->ToCharArray());
				bw->Write((Byte)0);
				bw->Write((Double)var->VariableValue);
			}
			saved=true;
		}
		finally{
			bw->Close();
			fs->Close();
		}*/
	}

	void ImageData::setSeqVars(LinkedList<Variable^>^ vars){
		seqVars->Clear();
		for each(Variable^ var in vars){
			Variable^ newvar = gcnew Variable();
			newvar->VariableValue = var->VariableValue;
			newvar->VariableName = var->VariableName;
			seqVars->AddLast(newvar);
		}
	}
}