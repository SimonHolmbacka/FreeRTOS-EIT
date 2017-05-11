#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "sobel.h"
#include "file_operations.h"

int sobelmain() {
    char *file_in,
         *file_out,
         *file_out_h,
         *file_out_v,
         *file_gray;
    byte *rgb,
         *gray,
         *sobel_h_res,
         *sobel_v_res,
         *contour_img;

    int rgb_size,
        width,
        height;
    int inter_files = 0,
        gray_file = 0;

    // Get arguments
        /*
    if(argc < ARGS_NEEDED) {
        printf("Usage: TODO\n");
        return 1;
    }
*/
    // File names
    //file_in = argv[1];
    //file_in = "/ram/websrc/img.rgb";
	file_in = "SobelFilter/lenna.rgb";
//    file_out = argv[2];
    //file_out = "/ram/websrc/img_out.gray";
	file_out = "SobelFilter/output.gray";
	file_out_h = "SobelFilter/output_h.gray";
	file_out_v = "SobelFilter/output_v.gray";
    // Get size of input image
    //char *width_token = strtok(argv[3], "x");
    //char *width_token = "62x164";
    /*
    if(width_token) {
        width = atoi(width_token);
    } else {
        printf("Bad image size argument\n");
        return 1;
    }
*/
    /*
    char *height_token = strtok(NULL, "x");
    if(height_token) {
        height = atoi(height_token);
    } else {
        printf("Bad image size argument\n");
        return 1;
    }
    */
    //height = 62;
    //width = 164;
	height = 512;
	width = 512;
    rgb_size = width*height*3;
    // Get optional arguments
    /*
    int arg_index = ARGS_NEEDED;
    while(arg_index < argc) {
        // If there is a flag to create intermediate files
        if(strcmp(argv[arg_index], "-i") == 0) {
            if(arg_index+3 > argc) {
                printf("Usage: TODO\n");
                return 1;
            }

            inter_files = 1;
            file_out_h = argv[arg_index+1];
            file_out_v = argv[arg_index+2];

            arg_index += 3;
        }

        else if(strcmp(argv[arg_index], "-g") == 0) {
            if(arg_index+2 > argc) {
                printf("Usage: TODO\n");
                return 1;
            }

            gray_file = 1;
            file_gray = argv[arg_index+1];

            arg_index += 2;
        }

        else {
            printf("Argument \"%s\", is unknown.\n", argv[arg_index]);
            return 1;
        }
    }
    */
    // Read file to rgb and get size
    readFile(file_in, &rgb, rgb_size);

    int gray_size = sobelFilter(rgb, &gray, &sobel_h_res, &sobel_v_res, &contour_img, width, height); //The content of contour is not right
	//262144 for 512x512
    // Write gray image

	
    if(gray_file) {
        writeFile(file_gray, gray, gray_size);
    }
	printf("Size %d\n", sizeof(gray));
	int ii = 0;
	for (ii = 0; ii < 8; ii++) {
		printf("%u\n", gray[ii]);
	}
#if 0
	printf("Contour %d\n", sizeof(contour_img));
	for (ii = 0; ii < 262144; ii++) {
		if(contour_img[ii] != 0)
		printf("%u\n", contour_img[ii]);
	}
#endif

    // Write image after each sobel operator
	inter_files = 1;
   if(inter_files) {
        writeFile(file_out_h, sobel_h_res, gray_size);
        writeFile(file_out_v, sobel_v_res, gray_size);
    }
#if 0
   byte * test;
   test[0] = 72;
   test[1] = 139;
   test[2] = 139;
   test[3] = 135;
   test[4] = 128;
   test[5] = 124;
   test[6] = 128;
   test[7] = 137;
#endif
    // Write sobel img to a file
    writeFile(file_out, contour_img, gray_size);
   //writeFile(file_out, test, 262144);

    return 0;
}

