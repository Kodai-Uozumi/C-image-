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
	char *name_img_in = "sample_morph.pgm" ;   /* 入力画像ファイル名 */
	char *name_img_out = "enshu7shushuku.pgm" ;  /* 出力画像ファイル名 */
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
	int x, y, T = 100, fM;
	for(y = 0; y < image_in->rows; y++){
	  for(x =0; x < image_in->cols; x++){
	    if(image_in->p[y][x] > T){
			image_out->p[y][x] = 1;
		}else{
			image_out->p[y][x] = 0;
		}
	  }
	}
    for(y = 0; y < image_in->rows; y++){
	  for(x =0; x < image_in->cols; x++){
	    if((x == 0) || (x == image_in->cols - 1) || (y == 0) || (y == image_in->rows - 1)){
	      image_in->p[y][x] = 0;
	    }else{
	      fM = image_out->p[y - 1][x - 1] + image_out->p[y - 1][x] + image_out->p[y - 1][x + 1] + image_out->p[y][x - 1] + image_out->p[y][x] + image_out->p[y][x + 1] + image_out->p[y + 1][x - 1] + image_out->p[y + 1][x] + image_out->p[y + 1][x + 1];
	      if(fM == 9){
              image_in->p[y][x] = 255;
          }else{
              image_in->p[y][x] = 0;
          }
	    }
	  }
	}

	if ( writeGrayImage( image_in, name_img_out ) == HAS_ERROR ) {
    	printError( name_img_out ) ;
    	return(1) ;
  	}

	return(0) ;
}
