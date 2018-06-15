#ifndef SQUIRREL_OPT_H
#define SQUIRREL_OPT_H
#include<tiffio.h>
#include<string>
//#include<intypes.h>
#include<vector>
#include<math.h>
#include <bits/stdc++.h>
#include<tuple>
std::vector<int> resize(int newsize, std::vector<int> image);
std::vector<float> I_RSF(int size, float sigma);
std::tuple<float,float,float> optimisation(std::vector<uint16> imageref, std::vector<uint16> imageRS);
std::vector<uint16> Ist_gamma(std::vector<uint16> Ist, float alpha, float beta);
std::vector<uint16> convolution(std::vector<uint16> image1, std::vector<uint16> image2);
std::vector<uint16> Ist(std::vector<uint16> Is, float delta_x, float delta_y);
float delta_Ex(int i,  float sigma)
{
    return(0.5*erf((i+0.5)/1*sqrt(2)*sigma)-0.5*erf((i-0.5)/1*sqrt(2)*sigma));
}
float delta_Ey(int j, float sigma)
{

    return(0.5*erf((j+0.5)/1*sqrt(2)*sigma)-0.5*erf((j-0.5)/1*sqrt(2)*sigma));
}


std::vector<int> resize(int newsize, std::vector<int> image)
{
    int size=image.size();
    int height=sqrt(size);
    int newheight=sqrt(newsize);
    float xscale=float(height)/float(newheight), yscale=float(height)/float(newheight);
    std::vector<int> v(newsize,0);
    for (int f = 0; f<newheight; f++)
    {
        for (int g = 0; g<newheight; g++)
        {
            int xpos = float(f) * xscale;
            int ypos = float(g) * yscale;
            v[(f)*newheight+g]=image[(xpos)*height+ypos];
            //std::cout<<v[(f)*newheight+g]<<"  ";
        }
    //std::cout<<std::endl;
    }
    return(v);
}


std::vector<float> I_RSF(int size, float sigma)
{

    std::vector<float> I_RSF1(size*size);

    for(unsigned int i=0; i<size;i++)
    {
        for(unsigned int j=0; j<size; j++)
        {
            I_RSF1[i*size+j]=delta_Ex(i,sigma)*delta_Ey(j,sigma);
            std::cout<<I_RSF1[i*size+j]<<"                               ";
        }
        std::cout<<std::endl;
    }
    return(I_RSF1);

}

std::tuple<float,float,float> optimisation(std::vector<uint16> imageref, std::vector<uint16> imageRS)
{



}

std::vector<uint16> convolution(std::vector<uint16> image1, std::vector<uint16> image2)
{
    int len1=image1.size(), len2=image2.size();
    std::vector<uint16> result(len1);
    if(len1!=len2) //On convolue 2 images de la même taille: celle de nanoscopie est resizée dans optimisation
    {
        //resize()

    }
    int height=sqrt(len1);
    for(int i=0; i<len1; i++)
    {
        int m=i%height; //numero de colonne
        int n=(i-m)/height; //numéro de ligne
        result[i]=0; //pixel à la position [n][m]
        for(unsigned int j=0; i<len1; i++)
        {
            for(unsigned int k=0; i<len1; i++)
            {
                result[i]=result[i]+(image1[k*height+j]*image2[(n-k)*height+(m-j)]);
            }
        }


    }
    return(result);
}


std::vector<uint16> Ist_gamma(std::vector<uint16> Ist, float alpha, float beta)
{
    std::vector<uint16> result(Ist.size());
    for(unsigned int i=0; i<Ist.size(); i++)
    {
        result[i]=Ist[i]*alpha+beta;
    }
    return(result);
}


std::vector<uint16> Ist(std::vector<uint16> Is, float delta_x, float delta_y)
{
    std::vector<uint16> result(Is.size(),0);
    int height=sqrt(Is.size());
    for(unsigned int i=0; i<Is.size(); i++)
    {
        int m=i%height; //numero de colonne
        int n=(i-m)/height; //numéro de ligne
        if((m+delta_y<height) && (n+delta_x<height))
            result[i]=Is[(n+delta_x)*height+(m+delta_y)];

    }
    return(result);

}

#endif // SQUIRREL_OPT_H
