package com.example.facialrecogapp;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

import org.opencv.objdetect.Objdetect;
import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewFrame;
import org.opencv.android.LoaderCallbackInterface;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;
import org.opencv.core.Rect;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.imgproc.Imgproc;
import org.opencv.objdetect.CascadeClassifier;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;
import android.view.SurfaceView;

public class MainActivity extends Activity implements CvCameraViewListener2 {
    private static final String  TAG              = "MainActivity";

    private CascadeClassifier cascadeClassifier;
    private Mat                  mRgba;
    Mat grayscaleImage;
    Mat color;
    Size resizedSize;
    int interpolation = Imgproc.INTER_CUBIC;
    private CameraBridgeViewBase mOpenCvCameraView;
    Mat resizeImage;
    MatOfRect burger_king;
    private BaseLoaderCallback  mLoaderCallback = new BaseLoaderCallback(this) {
        @Override
        public void onManagerConnected(int status) {
            switch (status) {
                case LoaderCallbackInterface.SUCCESS:
                {
                    Log.i(TAG, "OpenCV loaded successfully");
                    mOpenCvCameraView.enableView();
                } break;
                default:
                {
                    super.onManagerConnected(status);
                } break;
            }
        }
    };

    public MainActivity() {
        Log.i(TAG, "Instantiated new " + this.getClass());
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        Log.i(TAG, "OpenCV loaded successfully");

        setContentView(R.layout.color_blob_detection_surface_view);

        mOpenCvCameraView = findViewById(R.id.color_blob_detection_activity_surface_view);
        mOpenCvCameraView.setVisibility(SurfaceView.VISIBLE);
        mOpenCvCameraView.setCvCameraViewListener(this);
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    @Override
    public void onResume() {
        super.onResume();
        if (!OpenCVLoader.initDebug()) {
            Log.d(TAG, "Internal OpenCV library not found. Using OpenCV Manager for initialization");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_3_0_0, this, mLoaderCallback);
        } else {
            Log.d(TAG, "OpenCV library found inside package. Using it!");
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS);
        }
        try {
            // Copy the resource into a temp file so OpenCV can load it
            InputStream is = getResources().openRawResource(R.raw.haarcascade_frontalface_default);
            File cascadeDir = getDir("cascade", Context.MODE_PRIVATE);
            File mCascadeFile = new File(cascadeDir, "cascade.xml");
            FileOutputStream os = new FileOutputStream(mCascadeFile);

            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = is.read(buffer)) != -1) {
                os.write(buffer, 0, bytesRead);
            }
            is.close();
            os.close();
//
//            // Load the cascade classifier
            cascadeClassifier = new CascadeClassifier(mCascadeFile.getAbsolutePath());
        } catch (Exception e) {
            Log.e("OpenCVActivity", "Error loading cascade", e);
        }
        grayscaleImage = new Mat();
        resizedSize = new Size(640, 480);
        resizeImage = new Mat();
        burger_king = new MatOfRect();
    }

    public void onDestroy() {
        super.onDestroy();
        if (mOpenCvCameraView != null)
            mOpenCvCameraView.disableView();
    }

    public void onCameraViewStarted(int width, int height) {
        mRgba = new Mat(height, width, CvType.CV_8UC4);
    }

    public void onCameraViewStopped() {
        mRgba.release();
    }


    public Mat onCameraFrame(CvCameraViewFrame inputFrame) {
        Log.e("Status", "  ", null);
        color = inputFrame.rgba();
        Imgproc.resize(color, resizeImage, resizedSize, 0, 0, interpolation );
        Imgproc.cvtColor(resizeImage, grayscaleImage, Imgproc.COLOR_RGBA2GRAY);

        // Use the classifier to detect the logos
        if (cascadeClassifier != null) {
            cascadeClassifier.detectMultiScale(grayscaleImage, burger_king, 1.1, 5,
                    Objdetect.CASCADE_SCALE_IMAGE, new Size(30, 30));
        }
//
        // Placeholder for the logos found
        Rect[] burger_kingArray = burger_king.toArray();

        // Loop through all logos found and get their bounding rectangle coordinates
        for (int i = 0; i < burger_kingArray.length; i++) {
            double xCenterPx =  (burger_kingArray[i].tl().x +  burger_kingArray[i].br().x)/2;
            double xCenterDeg = xCenterPx - (resizedSize.width/2);
//            if(xCenterDeg < 0){
//                xCenterDeg /
//            }

            Log.e("TARGETTING", Double.toString(xCenterDeg), null);
            // Create a rectangle around it

        }
        return color;


    }
}