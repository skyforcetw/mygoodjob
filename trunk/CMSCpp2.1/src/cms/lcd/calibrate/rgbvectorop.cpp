#include <includeall.h>
#pragma hdrstop
#include "rgbvectorop.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
//#include "rgbvectorop.h";

namespace cms {
    namespace lcd {
	namespace calibrate {
	    //==================================================================
	    using namespace Dep;
	    using namespace cms::util;
	    using namespace math;
	    RGB_vector_ptr LinearOp::getRendering(RGB_vector_ptr source) {

		int size = source->size();
		RGB_vector_ptr result(new RGB_vector());
		for (int x = 0; x < size; x++) {
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb2->G = rgb2->B = x;
		     result->push_back(rgb2);
		};
		 return result;
	    };
	    //==================================================================

	    //==================================================================
	    RGB_vector_ptr MinusOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result(new RGB_vector());
		 foreach(RGB_ptr rgb, *source) {
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb->R - minusValue;
		     rgb2->G = rgb->G - minusValue;
		     rgb2->B = rgb->B - minusValue;
		     result->push_back(rgb2);
		};
		return result;
	    };
	  MinusOp::MinusOp(double minusValue):minusValue(minusValue)
	    {
	    };
	    //==================================================================
	    // P1P2DGOp
	    //==================================================================
	    RGB_vector_ptr P1P2DGOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGB_ptr rgbp1 = (*result)[p1];


		for (int x = 0; x != p1; x++) {
		    double v = x * rgbp1->G / p1;
		    //double d = java::lang::Math::roundTo(v * 4);
		    RGB_ptr rgb = (*result)[x];
		    rgb->setValues(v, v, v);
		    rgb->quantization(maxValue);
		}

		RGB_ptr rgbp0 = (*result)[p1 - 1];
		RGB_ptr rgbp2 = (*result)[p1 + 1];
		rgbp1->R = (rgbp0->R + rgbp2->R) / 2;
		rgbp1->G = (rgbp0->G + rgbp2->G) / 2;
		rgbp1->B = (rgbp0->B + rgbp2->B) / 2;
		rgbp1->quantization(maxValue);

		return result;
	    };
	  P1P2DGOp::P1P2DGOp(double p1, double p2, const MaxValue & maxValue):p1(p1), p2(p2), maxValue(maxValue)
	    {
	    };
	    //==================================================================

	    //==================================================================
	    // RBInterpolation
	    //==================================================================
	    RGB_vector_ptr RBInterpolationOp::
		getRendering(RGB_vector_ptr source) {

		double rInterval = (*source)[under]->R / under;
		double gInterval = (*source)[under]->G / under;
		double bInterval = (*source)[under]->B / under;
		RGB_vector_ptr result = RGBVector::deepClone(source);


		for (int x = 0; x != under; x++) {
		    //��RB interpolation
		    RGB_ptr rgb = (*result)[x];

		    rgb->R = rInterval * x;
		    rgb->G = gInterval * x;
		    rgb->B = bInterval * x;
		}
		return result;
	    };
	  RBInterpolationOp::RBInterpolationOp(double under):under(under)
	    {
	    };
	    //==================================================================

	    //==================================================================
	    // NewOp
	    //==================================================================
	    RGB_vector_ptr NewOp::getRendering(RGB_vector_ptr source) {
		//return getRendering7_(source);
		return getRendering8_(source);
	    };

	    RGB_vector_ptr NewOp::getRendering6_(RGB_vector_ptr source) {

		RGB_vector_ptr result = RGBVector::deepClone(source);
		int begin = getBBiggerThanG(source);
		int end = 1;

		double_array beginRatio = (*result)[begin]->getRGBRatio();
		RGB_ptr endrgb = (*result)[end];
		double endr = (endrgb->G + endrgb->B) / 2;
		double endTotal = endr + endrgb->G + endrgb->B;
		double endRRatio = endr / endTotal;

		for (int x = begin - 1; x > 0; x--) {
		    double rratio = Interpolation::linear(begin, end,
							  beginRatio[0],
							  endRRatio,
							  x);

		    RGB_ptr rgb = (*result)[x];
		    double r = getRCode(rratio, rgb->G, rgb->B);
		    rgb->R = r;
		}

		return result;
	    };
	    RGB_vector_ptr NewOp::getRendering7_(RGB_vector_ptr source) {

		RGB_vector_ptr result = RGBVector::deepClone(source);
		int begin = p1;
		int end = 1;

		double_array beginRatio = (*result)[begin]->getRGBRatio();
		double endRatio = 1. / 3;

		for (int x = begin - 1; x > 0; x--) {
		    double rratio = Interpolation::linear(begin, end,
							  beginRatio[0],
							  endRatio,
							  x);
		    double gratio = Interpolation::linear(begin, end,
							  beginRatio[1],
							  endRatio,
							  x);

		    RGB_ptr rgb = (*result)[x];
		    double b = getBCode(rratio, gratio, rgb->G);
		    double r = getRCode(rratio, rgb->G, b);
		    rgb->R = r;
		    rgb->B = b;
		}

		return result;
	    };

	    RGB_vector_ptr NewOp::getRendering8_(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		int begin = p2;
		int end = 1;

		double_array beginRatio = (*result)[begin]->getRGBRatio();
		double endRatio = 1. / 3;

		for (int x = begin - 1; x > 0; x--) {
		    double rratio = Interpolation::linear(begin, end,
							  beginRatio[0],
							  endRatio,
							  x);
		    double gratio = Interpolation::linear(begin, end,
							  beginRatio[1],
							  endRatio,
							  x);

		    RGB_ptr rgb = (*result)[x];
		    double b = getBCode(rratio, gratio, rgb->G);
		    double r = getRCode(rratio, rgb->G, b);
		    rgb->R = r;
		    rgb->B = b;
		}

		return result;
	    }

	    int NewOp::getBBiggerThanG(RGB_vector_ptr rgbVector) {
		for (int x = p1; x > 0; x--) {
		    RGB_ptr rgb = (*rgbVector)[x];
		    if (rgb->B > rgb->G) {
			return x;
		    }
		}
		return -1;
	    };
	    double NewOp::getBCode(double rRatio,
				   double gRatio, double GCode) {
		return (1 - rRatio - gRatio) * GCode / gRatio;
	    };
	    double NewOp::getRCode(double rRatio,
				   double GCode, double BCode) {
		return rRatio * (GCode + BCode) / (1 - rRatio);
	    };
	  NewOp::NewOp(int p1, int p2):p1(p1), p2(p2) {
	    };
	    //==================================================================
	    //==================================================================
	    /*BMaxOp::BMaxOp(const Dep::MaxValue & out):out(out) {

	       }; */
	  BMaxOp::BMaxOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {

	    };
	    RGB_vector_ptr BMaxOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		//==============================================================
		//�⥼�Ψ쪺�ϰ�����B�z���̤j��
		int n = bitDepth->getLevel() - 1;
		int effectiven = (bitDepth->getEffectiveLevel() - 1);
		//STORE_RGBVECTOR("0.xls", result);
		for (int x = n; x >= effectiven; x--) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->B = bitDepth->getMaxDigitalCount();
		}
		//STORE_RGBVECTOR("1.xls", result);
		//==============================================================                

		for (int x = effectiven; x != -1; x--) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr nextrgb = (*result)[x - 1];
                    //�]�w�t��
		    double diff =
			x > 252 ? 10 / 4. : (x > 232 ? 8 / 4. : 6 / 4.);
		    double thisB = rgb->B;
		    double nextB = nextrgb->B;
		    if (thisB > nextB) {
			nextrgb->B = thisB - diff;
		    } else {
			double preB = (*result)[x + 1]->B;
			rgb->B = (preB + nextB) / 2.;
			break;
		    }
		}
		//STORE_RGBVECTOR("2.xls", result);

		return result;
	    };
	    //==================================================================

	    //==================================================================
	    RGB_vector_ptr GByPassOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		//8/6 0~244,245~250,251~255
		//6/6 0~251,252~255
		if (bitDepth->is8in6Out()) {
		    for (int x = 0; x != 245; x++) {
			(*result)[x]->G = x;
		    };
		    for (int x = 245; x != 251; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 0.5;
		    };
		    for (int x = 251; x != 256; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 1;
		    };
		} else if (bitDepth->is6in6Out()) {
		    for (int x = 0; x != 252; x++) {
			(*result)[x]->G = x;
		    };
		    for (int x = 252; x != 256; x++) {
			(*result)[x]->G = 252;
		    };
		}
		return result;
	    };
	  GByPassOp::GByPassOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {

	    };
	    //==================================================================
	    RGB_vector_ptr FrcNROp::getRendering(RGB_vector_ptr source) {
		//int size = source->size();
		RGB_vector_ptr result = RGBVector::clone(source);
		RGB_ptr rgb255 = (*result)[255];
		STORE_RGBVECTOR("frcNR_0.xls", result);
		if (!bitDepth->is6in6Out()) {
		    //6in6out�~�ҰʥH�U�ץ�(nb panel�Y�O)
		    foreach(const Channel & ch, *Channel::RGBChannel) {
			//�G�쪺�ץ�
			if (rgb255->getValue(ch) >= 248.5) {
			    //�Y�ϥΨ�248.5�H�W, �ץ���254�~�ϥΨ�FRC
			    (*result)[255]->setValue(ch, 252);
			    (*result)[254]->setValue(ch, 250);
			    (*result)[253]->setValue(ch, 248);
			    for (int x = 252; x != -1; x--) {
				RGB_ptr thisRGB = (*result)[x];
				RGB_ptr nextRGB = (*result)[x + 1];
				double thisv = thisRGB->getValue(ch);
				double nextv = nextRGB->getValue(ch);
				if (thisv >= nextv) {
				    //�Y������, �h�j��]�w�t����0.5
				    thisRGB->setValue(ch, nextv - 2 / 4.);
				} else {
				    break;
				}
			    }
			}
		    }
		    STORE_RGBVECTOR("frcNR_1.xls", result);
		}
		//�H�U�ץ��h�����w�Onb panel
		foreach(const Channel & ch, *Channel::RGBChannel) {
		    //�t�쪺�ץ�1~30
		    for (int x = 1; x != 31; x++) {
			RGB_ptr rgb = (*result)[x];
			double v = rgb->getValue(ch);
			//�u���bv��3 or 1�~���ץ�
			if (v == 12 / 4. || v == 4 / 4.) {
			    double setvalue =
				(v == 12 / 4.) ? 10 / 4. : 2 / 4.;
			    rgb->setValue(ch, setvalue);
			    RGB_ptr prergb = (*result)[x - 1];
			    double prev = prergb->getValue(ch);
			    if (prev == rgb->getValue(ch)) {
				prergb->setValue(ch, prev - 2 / 4.);
			    }
			    if (prergb->getValue(ch) < 0) {
				prergb->setValue(ch, 0);
			    }
			}

		    }
		}
		STORE_RGBVECTOR("frcNR_2.xls", result);
		return result;
	    };
	  FrcNROp::FrcNROp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {
	    };
	    //==================================================================
	    //==================================================================
	    RGB_vector_ptr KeepMaxLuminanceOp::
		getRendering(RGB_vector_ptr source) {
		/* TODO : KeepMaxLuminanceOp���� */
		int size = source->size();
		RGB_vector_ptr result = RGBVector::clone(source);
		RGB_ptr white = (*result)[size - 1];
		double max = bitDepth->getMaxDigitalCount();
		white->setValues(max, max, max);
		return result;
	    };
	  KeepMaxLuminanceOp::KeepMaxLuminanceOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {

	    };
	    //==================================================================
	};
    };
};
