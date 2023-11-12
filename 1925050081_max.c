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
	char *name_img_in = "sample_noise.pgm" ;   /* 入力画像ファイル名 */
	char *name_img_out = "enshu4max.pgm" ;  /* 出力画像ファイル名 */
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
	int x, y, a[9], i, j, tmp;
	for(y = 0; y < image_in->rows; y++){
	  for(x =0; x < image_in->cols; x++){
	    if((x == 0) || (x == image_in->cols - 1) || (y == 0) || (y == image_in->rows - 1)){
	      image_out->p[y][x] = image_in->p[y][x];
	    }
	    else{
	      a[0] = image_in->p[y - 1][x - 1];
	      a[1] = image_in->p[y - 1][x];
	      a[2] = image_in->p[y - 1][x + 1];
	      a[3] = image_in->p[y][x - 1];
	      a[4] = image_in->p[y][x];
	      a[5] = image_in->p[y][x + 1];
	      a[6] = image_in->p[y + 1][x - 1];
	      a[7] = image_in->p[y + 1][x];
	      a[8] = image_in->p[y + 1][x + 1];
	      for(i = 0; i < 8; i++){
		for(j = 8; j > i; j--){
		  if(a[j - 1] > a[j]){
		    tmp = a[j];
		    a[j] = a[j - 1];
		    a[j - 1] = tmp;
		  }
		}
	      }
	      image_out->p[y][x] = a[8];
	    }
	  }
	}

	if ( writeGrayImage( image_out, name_img_out ) == HAS_ERROR ) {
    	printError( name_img_out ) ;
    	return(1) ;
  	}

	return(0) ;
}
