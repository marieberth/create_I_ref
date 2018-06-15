#include <QCoreApplication>
#include<tiffio.h>
#include<string>
//#include<intypes.h>
#include<vector>
#include<math.h>
#include <bits/stdc++.h>
#include<tuple>
#include"squirrel_opt.h"
#include"AbbeTiffWriter.h"
#include"tinytiffwriter.h"



int main()
{


    const char* filename[1]={"D:/Data/Larisa/9_4/1/647/UAF.tif"};
    //{"D:/Data/Universite-Geneve_20170926/TubulineGA2pourcentAF647/Essai_1/EPI.tif", "D:/Data/Universite-Geneve_20170926/Actin-AF647-TubulinCF555/Essai1/Actin647/EPI.tif", "D:/Data/Larisa/9_4/1/647/EPI.tif"};
    TIFF* tiffrNANO = NULL;
    TIFF* tiffTotal=NULL;
    tiffrNANO=TIFFOpen(filename[0],"r");
    std::cout<<"ici"<<std::endl;
   /* int dircount=0;
    bool b=TIFFSetDirectory(tiffrNANO,0);
    while (TIFFReadDirectory(tiffrNANO))*/
    std::vector<unsigned short*> SimulatedQueue;
    int Width, Height;
    //Bit depth, in bits
    unsigned short depth;
    TIFFGetField(tiffrNANO, TIFFTAG_IMAGEWIDTH, &Width);
    TIFFGetField(tiffrNANO, TIFFTAG_IMAGELENGTH, &Height);
    TIFFGetField(tiffrNANO, TIFFTAG_BITSPERSAMPLE, &depth);
    std::vector<long long int> result(Height*Width);
    if(tiffrNANO){
        int dircount = 0;
        int i=0;
        float min=1000000000000000000000.0, max=-10.0;
        do{
            dircount++;

        unsigned short *Buffer = new unsigned short[Width*Height];
        //Copy all the scan lines
                for(int Row = 0; Row < Height; Row++){
                   TIFFReadScanline(tiffrNANO, &Buffer[Row*Width], Row, 0);

                }

                SimulatedQueue.push_back(Buffer);
                for(int j=0; j<Width*Height; j++)
                {
                   result[j]=result[j]+Buffer[j];
                   if(result[j]<min)
                   {
                       min=result[j];
                   }
                   if(result[j]>max)
                       max=result[j];
                }

                i++;




            }while(TIFFReadDirectory(tiffrNANO));
        for(int i=0; i<Width*Height;i++)
        {
            std::cout<<result[i]<<std::endl;
        }
        //Additionner tous les éléments dans simulated queue

        //std::cout<<"W*H  "<<Width*Height<<"  SimulatedQueue.size()  "<<SimulatedQueue.size()<<std::endl;
       /* for(unsigned int i=0; i<SimulatedQueue.size(); i++)
        {
            for(unsigned int j=0; j<Width*Height;j++)
            {

                result[j]=result[j]+SimulatedQueue[i][j];
                if(result[j]<min)
                {
                    min=result[j];
                }
                if(result[j]>max)
                    max=result[j];

            }



        }*/

        std::vector<uint16> data(result.size());

        for(unsigned int j=0; j<result.size();j++)
        {
           data[j]=std::pow(2,32)*(result[j]-min)/(max-min);
        }
      TIFF* Ref = NULL;
      std::string filename="D:/Data/Data_squirrel/I-ref.tif";

     /*TinyTIFFFile *tif_imNano3D = TinyTIFFWriter_open(filename.c_str(),32 ,Width, Height);
     TinyTIFFWriter_writeImage(tif_imNano3D, result.data());
     TinyTIFFWriter_close(tif_imNano3D);*/

      TinyTIFFFile *tif_imNano3D = TinyTIFFWriter_open(filename.c_str(),32 ,Width, Height);
      TinyTIFFWriter_writeImage(tif_imNano3D, result.data());
      TinyTIFFWriter_close(tif_imNano3D);


    TIFFClose(tiffrNANO);
    }

    return 1;
}


