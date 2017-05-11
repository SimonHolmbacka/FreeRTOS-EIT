#ifndef __CANNY
#define __CANNY

int cannymain();
typedef short int pixel_t;
extern QueueHandle_t cannyQueue;
extern int chunksize;
typedef struct cannyMessage {
	pixel_t* value;
}cannyMessage;

#endif