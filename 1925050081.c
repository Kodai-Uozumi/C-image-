#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include "pnmimg.h"

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
	char *name_img_in = "sample.ppm" ;   /* 入力画像ファイル名 */
	char *name_img_out = "enshu2.pgm" ;  /* 出力画像ファイル名 */
	RGB_PACKED_IMAGE *image_in ; 
	GRAY_IMAGE *image_out ; 


	/* コマンドラインでファイル名が与えられた場合の処理 */
	if ( argc >= 2 ) name_img_in = argv[1] ;
	if ( argc >= 3 ) name_img_out = argv[2] ;

	if (!( image_in = readRGBPackedImage( name_img_in ))) {
		printError( name_img_in ) ;
		return(1) ;
	}

	image_out = allocGrayImage(image_in->cols, image_in->rows);  

	/** ここに画像の処理を書き込む **/
	int x, y;
	for(y = 0; y < image_in->rows; y++){
	  for(x =0; x < image_in->cols; x++){
	    image_out->p[y][x] = 0.2126 * image_in->p[y][x].r + 0.7152 * image_in->p[y][x].g + 0.0722 * image_in->p[y][x].b;
	  }
	}

	if ( writeGrayImage( image_out, name_img_out ) == HAS_ERROR ) {
    	printError( name_img_out ) ;
    	return(1) ;
  	}

	return(0) ;
}
