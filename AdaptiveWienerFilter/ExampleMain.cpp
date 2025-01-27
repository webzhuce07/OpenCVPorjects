/*Copyright(c) 2017-2018 Federico Bolelli, Costantino Grana
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met :

*Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and / or other materials provided with the distribution.

* Neither the name of AdaptiveWienerFilter nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Federico Bolelli: federico.bolelli@unimore.it
*/

#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace cv;
using namespace std;

#include "WienerFilter.h"

int main(void)
{
	// This main applies the Adaptive Wiener Filter on a simple example
	// image and save results in the project installation folder

	string testImage = "test.jpg";
	Mat1f src = imread(testImage, 0);
    
	Mat1f dst3x3, dst5x5, dst5x5_fixedNoise;

	if (src.empty()){
		cout << "The specified image '" << testImage << "' does not exists" << endl;
		exit(-1);
	}

	double estimatedNoiseVariance;

	// Call to WienerFilter function with a 3x3 kernel and estimated noise variances
	estimatedNoiseVariance = WienerFilter(src, dst3x3, Size(5, 1));

	// Call to WienerFilter function with default 5x5 kernel estimated noise variances
	estimatedNoiseVariance = WienerFilter(src, dst5x5, Size(5, 5));

	// Call to WienerFilter function with a default 5x5 kernel and fixed noise variances
	WienerFilter(src, dst5x5_fixedNoise, 5000);

	imwrite("Filtered5X1.png", dst3x3);
	imwrite("Filtered5X5.png", dst5x5);
	imwrite("Filtered5X5_fixedNoise.png", dst5x5_fixedNoise);

	estimatedNoiseVariance = WienerFilter(src, dst3x3, Size(1, 5));
	imwrite("Filtered1X5.png", dst3x3);
	imwrite("Filtered5X11.png", src);

	return 0;
}