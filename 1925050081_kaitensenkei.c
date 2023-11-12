#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include "pnmimg.h"
#include <math.h>

#ifdef __STDC__
int
main( int argc, char *argv[] )
#else
int
main( argc, argv )
     int argc ;
     char *argv[] ;
#endif
{
	char *name_img_in = "sample.pgm" ;   /* 入力画像ファイル名 */
	char *name_img_out = "enshu5kaitensenkei.pgm" ;  /* 出力画像ファイル名 */
	GRAY_IMAGE *image_in ; 
	GRAY_IMAGE *image_out ; 


	/* コマンドラインでファイル名が与えられた場合の処理 */
	if ( argc >= 2 ) name_img_in = argv[1] ;
	if ( argc >= 3 ) name_img_out = argv[2] ;

	if (!( image_in = readGrayImage( name_img_in ))) {
		printError( name_img_in ) ;
		return(1) ;
	}

	image_out = allocGrayImage(image_in->cols, image_in->rows);  

	/** ここに画像の処理を書き込む **/
	int X, Y, x0 = 330, y0 = 162, a = 80;
	float x, y;
	double Sx, Sy;
	for(Y = 0; Y < image_out->rows; Y++){
	  for(X =0; X < image_out->cols; X++){
	    x = (X - x0) * cos(a * M_PI / 180) - (Y - y0) * sin(a * M_PI / 180) + x0;
	    y = (X - x0) * sin(a * M_PI / 180) + (Y - y0) * cos(a * M_PI / 180) + y0;
	    if((floor(x) >= 0) && (floor(x) < image_in->cols) && (floor(x + 1) >= 0) && (floor(x + 1) < image_in->cols) && (floor(y) >= 0) && (floor(y) < image_in->rows) && (floor(y + 1) >= 0) && (floor(y + 1) < image_in->rows)){
	      Sx = x - floor(x);
	      Sy = y - floor(y);
	      image_out->p[Y][X] = (1 - Sy) * ((1 - Sx) * image_in->p[(int) floor(y)][(int) floor(x)] + Sx * image_in->p[(int) floor(y)][(int) floor(x + 1)]) + Sy * ((1 - Sx) * image_in->p[(int) floor(y + 1)][(int) floor(x)] + Sx * image_in->p[(int) floor(y + 1)][(int) floor(x + 1)]);
	    }else{
	      image_out->p[Y][X] = 0;
	    }
	  }
	}

	if ( writeGrayImage( image_out, name_img_out ) == HAS_ERROR ) {
    	printError( name_img_out ) ;
    	return(1) ;
  	}

	return(0) ;
}
