/*
 * HeisAI_Face_Recognizer.h
 *
 *  Created on: Feb 2, 2018
 *      Author: Yusheng Xu, TUM_PF
 */

#ifndef HEISAI_FACE_RECOGNIZER_H_
#define HEISAI_FACE_RECOGNIZER_H_

#include <math.h>
#include <time.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/public/session.h"

using namespace cv;
using namespace std;
using namespace tensorflow;
using tensorflow::Tensor;
using tensorflow::Status;

#include "HeisAI_Decryption_RSA.h"

const string input_layer_1 = "input:0";
const string input_layer_2 = "phase_train:0";
const string output_layer = "embeddings:0";

class FaceRecognition
{
public:
    FaceRecognition(string graph_pathname);
    ~FaceRecognition();

    void
	calculateFeature(Mat &image, float * image_feature);

    double
	estimateSimilarity(float * master_feature, float * slave_feature);

    void
	checkLicense(string license_pathname);

    string modelPath = "./model/";

private:
    bool valid_ornot=false;
    tensorflow::Session *session;

};

#endif /* HEISAI_FACE_RECOGNIZER_H_ */

