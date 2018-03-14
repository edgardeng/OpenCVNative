/*
 * HeisAI_Face_Recognizer.cpp
 *
 *  Created on: Feb 8, 2018
 *      Author: Yusheng Xu
 */

#include "HeisAI_Face_Recognizer.h"

FaceRecognition::FaceRecognition(string graph_pathname)
{
    tensorflow::GraphDef graph_def;

    Status status = NewSession(SessionOptions(), &session);

    // Load graph model
    if (!ReadBinaryProto(tensorflow::Env::Default(), graph_pathname, &graph_def).ok())
    {
        LOG(ERROR) << "Read proto error !";
        return ;
    }

    // Sign loaded graph to session
    if (!session->Create(graph_def).ok())
    {
        LOG(ERROR) << "Create graph in session error !";
        return ;
    }
}

FaceRecognition::~FaceRecognition()
{
	session->Close();
}

void
FaceRecognition::checkLicense(string license_pathname)
{
	string private_pathname="private_key_180201.oem";
	string cipher_pathname= license_pathname;//"cihper_license.dat";
	decryptInformation(cipher_pathname, private_pathname); // Decryption with private key
	this->valid_ornot=verifyLicense(cipher_pathname, private_pathname);  // Check the license
}

void
FaceRecognition::calculateFeature(Mat &input_image, float * output_feature)
{
	// Resize(optional)
	int height=160, width=160, depth=3;
    resize(input_image, input_image, Size(height, width));

	Tensor input_tensor(tensorflow::DT_FLOAT, tensorflow::TensorShape({ 1,height,width,depth }));

    //int64 start=getTickCount();

    auto input_tensor_mapped = input_tensor.tensor<float, 4>();

    // Mean and Std
    // c * r * 3 => c * 3r * 1
    cv::Mat temp = input_image.reshape(1, input_image.rows * 3);

    cv::Mat mean3;
    cv::Mat stddev3;
    cv::meanStdDev(temp, mean3, stddev3);

    double mean_pxl = mean3.at<double>(0);
    double stddev_pxl = stddev3.at<double>(0);

    // Prewhiten
    input_image.convertTo(input_image, CV_64FC1);
    input_image = input_image - cv::Vec3d(mean_pxl, mean_pxl, mean_pxl);
    input_image = input_image / stddev_pxl;

    // Copying the data into the corresponding tensor
    for (int y = 0; y < height; ++y)
    {
        const double* source_row = input_image.ptr<double>(y);
        for (int x = 0; x < width; ++x)
        {
            const double* source_pixel = source_row + (x * depth);
            for (int c = 0; c < depth; ++c)
            {
                const double* source_value = source_pixel + (2-c);//RGB->BGR
                input_tensor_mapped(0, y, x, c) = *source_value;
            }
        }
    }


    // Feature calculation
    Tensor phase_train(tensorflow::DT_BOOL, tensorflow::TensorShape());
    phase_train.scalar<bool>()() = false;

    std::vector<Tensor> outputs;

    Status run_status = session->Run({{input_layer_1, input_tensor},
    							 {input_layer_2,phase_train}},
    							 {output_layer},
    							 {},
    							 &outputs);

    if(!run_status.ok())
    {
        LOG(ERROR) << "Running model failed"<<run_status;
    }

    auto outMap = outputs[0].tensor<float, 2>();

    if(output_feature != NULL)
    {
        for(int i = 0; i < 128; i++)
        {
            output_feature[i] = outMap(i);
        }
    }
}

double
FaceRecognition::estimateSimilarity(float * master_feature, float * slave_feature)
{
	double sum = 0;
	for(int i = 0; i < 128; i++)
	{
		sum += (master_feature[i] - slave_feature[i]) * (master_feature[i] - slave_feature[i]) ;
	}
	return sqrt(sum);
}
