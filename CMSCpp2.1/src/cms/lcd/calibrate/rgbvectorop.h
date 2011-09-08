#ifndef RGBVECTOROPH
#define RGBVECTOROPH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "rgbop.h"
#include "lcdcalibrator.h"

namespace cms {
    namespace lcd {
	namespace calibrate {

	    class DGLutOp:public RGBOp < RGB_vector > {
	      public:
		//RGB_vector_ptr createInstance();
	    };

	    class LinearOp:public DGLutOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);

	    };
	    class MinusOp:public DGLutOp {
	      private:double minusValue;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 MinusOp(double minusValue);
	    };

	    class P1P2DGOp:public DGLutOp {
	      private:
		double p1, p2;
		//const Dep::MaxValue & maxValue;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 P1P2DGOp(double p1, double p2);
	    };

	    class RBInterpolationOp:public DGLutOp {
	      private:
		double under;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 RBInterpolationOp(double under);
	    };


	    class BMaxOp:public DGLutOp {
	      private:
		//const Dep::MaxValue & out;
		bptr < BitDepthProcessor > bitDepth;

	      public:
		BMaxOp(bptr < BitDepthProcessor > bitDepth);
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };

	    class BMax2Op:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
		int begin;
		double gamma;
	      public:
		 BMax2Op(bptr < BitDepthProcessor > bitDepth, int begin, double gamma);
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };

	    class GByPassOp:public DGLutOp {
	      private:
		//const Dep::MaxValue & in, &out;
		bptr < BitDepthProcessor > bitDepth;
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		GByPassOp(bptr < BitDepthProcessor > bitDepth);
	    };

	    class FrcNROp:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		FrcNROp(bptr < BitDepthProcessor > bitDepth);
	    };


	    /*
	       純粹將EffectiveLevel以後的值全部設成最大值
	     */
	    class KeepNativeWhiteOp:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		KeepNativeWhiteOp(bptr < BitDepthProcessor > bitDepth);

	    };

	    class KeepNativeWhiteAdvancedOp:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
		int over;
		bool compensationR;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 KeepNativeWhiteAdvancedOp(bptr < BitDepthProcessor > bitDepth, int over,
					   bool compensationR);
	    };

	    class DimDGLutFixOp:public DGLutOp {
	      private:
		static bool_array getDefectArray(double2D_ptr deltaxyValues,
								double threshold);
		static bool_array getContinueDefectArray(double2D_ptr deltaxyValues,
									double threshold);
		static int getDefectType(bool dxdefect, bool dydefect);
	      public:
		 DimDGLutFixOp(bptr < BitDepthProcessor > bitDepth, double dimFixThreshold,
			       Component_vector_ptr componentVector);
	    };
	};
    };
}
#endif

