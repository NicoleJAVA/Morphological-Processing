
#include "stdio.h"
#include "iostream.h"
#include "stdlib.h"
#include "math.h"

#define PI 3.14159265
#define Size 512
#define ThreshUp 30
#define ThreshLow 20
using namespace std;

int main( int argc, char *argv[])
{
	FILE *file;
	unsigned char Imagedata[Size][Size];
	
						/************************************************/
						/******                                	 ******/
						/****** Read "input.raw" into Imagedata[][]******/
						/******                                	 ******/
						/************************************************/							
	if (!(file=fopen("circle.raw","rb"))){
		cout<<"Cannot open file!"<<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size*Size, file);
	fclose(file);

	/**********************************	do some image processing task... ***/
	
	int i = 0, j = 0;
	int iOffset = 0, jOffset = 0; 	//	 the offset within the moving-window

	
						/********************************************/
						/******                                ******/
						/******     Constructing Element Type I 
						/******     8-Neighbor
						/******                                ******/
						/********************************************/	
	
	unsigned char afterErode[Size][Size];
	float  maxNeighbor;

	for( i = 2; i < Size-2; i++ ){
		for( j = 2; j < Size-2; j++){
		
			maxNeighbor = 257;

			for( iOffset = -2; iOffset <= 2; iOffset++ ){
				for( jOffset = -2; jOffset <= 2; jOffset++ ){
					
					if( Imagedata[i+iOffset][j+jOffset] < maxNeighbor ){
						maxNeighbor = Imagedata[i+iOffset][j+jOffset];
					}


				}	//	End-4-for
			}	//	End-3-for					
			if( maxNeighbor != -1 ){
				afterErode[i][j] = static_cast<unsigned char>(maxNeighbor);
			}
			else if ( maxNeighbor == -1 ){
				//afterErode[i][j] = static_cast<unsigned char>(0);	
			}	
		}	//	End-2-for
	}	//	End-1-for
	/******************************************************** b e g i n ***
	int erodeLoop = 1;
	for(  erodeLoop = 1; erodeLoop <=1; erodeLoop++ ){			

		for( i = 2; i < Size-2; i++ ){
			for( j = 2; j < Size-2; j++){
		
				maxNeighbor = -1;

				for( iOffset = -2; iOffset <= 2; iOffset++ ){
					for( jOffset = -2; jOffset <= 2; jOffset++ ){
							
						if( Imagedata[i+iOffset][j+jOffset] < maxNeighbor ){
							maxNeighbor = afterErode[i+iOffset][j+jOffset];
						}


					}	//	End-4-for
				}	//	End-3-for					

				afterErode[i][j] = maxNeighbor;
					
			}	//	End-2-for
		}	//	End-1-for
  
	} // End-0-for
	
   ******************************************************** END ***/

	unsigned char boundary1[Size][Size];
	unsigned char boundary2[Size][Size];
	unsigned char temp;
	
	for( i=0; i< Size; i++ ){
		for( j=0; j<Size; j++ ){
			temp = Imagedata[i][j] - afterErode[i][j];
			boundary1[i][j] = temp;
	
		}
	}

						/********************************************/
						/******                                ******/
						/******    write image to "boundary_I.raw"  ******/
						/******                                ******/
						/********************************************/		
	if (  !(file=fopen("afterErode.raw","wb"))  ){
		cout<<"Cannot open file!"<<endl;
		exit(1);
	}
	else{
		fwrite(afterErode, sizeof(unsigned char), Size*Size, file);
		fclose(file);
	}
	

						/********************************************/
						/******                                ******/
						/******    write image to "afterErode2.raw"  
						/******                                ******/
						/********************************************	
	if (  !(file=fopen("afterErode2.raw","wb"))  ){
		cout<<"Cannot open file!"<<endl;
		exit(1);
	}
	else{
		fwrite(afterErode, sizeof(unsigned char), Size*Size, file);
		fclose(file);
	}
	
	
						/********************************************/
						/******                                ******/
						/******    write image to "M.raw"  ******/
						/******                                ******/
						/********************************************/		
	if (  !(file=fopen("M.raw","wb"))  ){
		cout<<"Cannot open file!"<<endl;
		exit(1);
	}
	else{
		fwrite(boundary1, sizeof(unsigned char), Size*Size, file);
		fclose(file);
	}
	

						/********************************************/
						/******                                ******/
						/******    write image to "M_2.raw"  ******/
						/******                                ******/
						/********************************************
	if (  !(file=fopen("M_2.raw","wb"))  ){
		cout<<"Cannot open file!"<<endl;
		exit(1);
	}
	else{
		fwrite(boundary2, sizeof(unsigned char), Size*Size, file);
		fclose(file);
	}
	

		/********************************************/		



	system("PAUSE");
	exit(0);
}

