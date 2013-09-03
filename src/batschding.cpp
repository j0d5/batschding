//  batschding
//
//  Created by Johannes Steudle, Adrian Philipp and Marcel Vielsack on 20.05.11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include <stdio.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "Gamelogic.h"
#include "Output.h"
#include <string>

const int MY_IMAGE_WIDTH  = 640;
const int MY_IMAGE_HEIGHT = 480;
const int MY_WAIT_IN_MS   = 20;

bool setMouse = false;
int mouseX = 0;
int mouseY = 0;

// mouse handler
void mouseHandler(int event, int x, int y, int flags, void *param) {
    switch(event) {
            // left button down
        case CV_EVENT_LBUTTONDOWN:
            printf("Left button down (%d, %d).\n", x, y);
            mouseX = x;
            mouseY = y;
            setMouse = true;
            break;
            
            // right button down
        case CV_EVENT_RBUTTONDOWN:
            printf("Right button down (%d, %d).\n", x, y);
            break;
    }
}

// LiveLoop zieht Bilder von der Kamera ein und stellt die Bilder in einem Fenster dar.
// Beenden der Anwendung: Taste 'e' drücken
void LiveLoop()
{
    IplImage* grabImage = 0;
    IplImage* resultImage = 0;
    Gamelogic gamelogic;
    int key;
    
    // create window for live video
    cvNamedWindow("Live", CV_WINDOW_AUTOSIZE);
    
    // add mouse handler for mouse events
    cvSetMouseCallback("Live", mouseHandler, NULL);
    
    // create connection to camera
    CvCapture* capture = cvCaptureFromCAM(1);
    
    // init camera
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, MY_IMAGE_WIDTH ); 
    cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, MY_IMAGE_HEIGHT );
    
    // check connection to camera by grabbing a frame
    if(!cvGrabFrame(capture))
    {      
        cvReleaseCapture(&capture);
        cvDestroyWindow("Live");
        printf("Could not grab a frame\n\7");
        exit(0);
    }
    
    // retrieve the captured frame
    grabImage = cvRetrieveFrame(capture);           
    // init result image, e.g. with size and depth of grabImage
    resultImage = cvCreateImage(cvGetSize(grabImage), grabImage->depth, grabImage->nChannels);
    
    bool continueGrabbing = true;
    while (continueGrabbing)
    {
        if(!cvGrabFrame(capture))
        {              
            cvReleaseCapture(&capture);
            cvDestroyWindow("Live");
            cvReleaseImage(&grabImage);
            printf("Could not grab a frame\n\7");
            continueGrabbing = false;
        }
        else
        {
            grabImage = cvRetrieveFrame(capture);
            
            cvFlip(grabImage, grabImage, 1);
            
            // todo: insert image processing
            if (setMouse) {
                gamelogic.setMousePointer(mouseX, mouseY);
                setMouse = false;
            }
            gamelogic.processImage(grabImage);
            // dummy line: copy grabbed image
            cvCopy(grabImage, resultImage, NULL );
            
            // end todo
            
            cvShowImage("Live", resultImage);
            
            key = cvWaitKey(MY_WAIT_IN_MS);
            
            if (key == 'e')
                continueGrabbing = false;
        }
    }
    
    // release all
    cvReleaseCapture(&capture);
    cvDestroyWindow("Live");
    cvReleaseImage(&resultImage);
}

int main(int argc, char** argv) {
    LiveLoop();
    
    return 0;
}
