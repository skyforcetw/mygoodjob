#include <includeall.h>
#pragma hdrstop
#include "whitefinder.h"

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms;
	    using namespace cms::measure;
	    using namespace cms::lcd::calibrate::algo;
	    using namespace Dep;
	    using namespace Indep;
	    //==================================================================
	    // WhitePointFinder
	    //==================================================================
	     WhitePointFinder::WhitePointFinder(bptr < MeterMeasurement > mm):mm(mm) {	/*,
											   aroundAlgo(ChromaticAroundAlgorithm()) */
		aroundAlgo =
		    bptr < ChromaticAroundAlgorithm >
		    (new ChromaticAroundAlgorithm());
		nearAlgo =
		    bptr < CIEuv1960NearestAlgorithm >
		    (new CIEuv1960NearestAlgorithm
		     (XYZ_ptr((CIEXYZ *) null), mm));
	    };

	    RGB_ptr WhitePointFinder::findMatchRGB0(xyY_ptr xyY,
						    RGB_ptr initRGB) {
		this->mm;
		RGB_ptr nearestRGB = initRGB;
		bool findNearest = false;

		do {
		    RGB_vector_ptr aroundRGB =
			aroundAlgo->getAroundRGB(nearestRGB, 1);
		    XYZ_ptr center = xyY->toXYZ();
		     bptr < AlgoResult > algoResult =
			nearAlgo->getNearestRGB(center, aroundRGB);
		    XYZ_vector_ptr aroundXYZ = algoResult->aroundXYZ;
		     nearestRGB = algoResult->nearestRGB;
		     findNearest =
			MeasuredUtils::isFirstNearestXYZInuvPrime(center,
								  aroundXYZ);
		    //findNearest = true;

		} while (!findNearest);
		 return nearestRGB;
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		aroundAlgo->setMode(Normal);
		RGB_ptr result = findMatchRGB0(xyY, RGBColor::White);
		return result;
	    };

	    /*
	       以此修正後的值, 修正其餘非255的兩點, 使色度達到最接近值.
	       1. 找到最大值頻道
	       2. 計算目前xyY與目標值之delta
	       3.
	     */
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {
		aroundAlgo->setMode(White);
		RGB_ptr result = findMatchRGB0(xyY, initRGB);
		return result;
	    };

	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {
		RGB_ptr clone = rgb->clone();
		//然後再調整White使RGB其中一點為255.
		const Channel & maxChannel = clone->getMaxChannel();
		double maxChannelValue = clone->getValue(maxChannel);
		double diff = 255 - maxChannelValue;
		clone->addValue(diff);
		return clone;
	    };

	    /*
	       白點尋找流程

	       由於缺乏model可以預測適當的白點,
	       1. 因此先以RGB為cube尋找正確白點
	       2. 然後再調整White使RGB其中一點為255.
	       3. 再以此修正後的值, 修正其餘非255的兩點, 使色度達到最接近值.
	     */
	    RGB_ptr WhitePointFinder::findRGB(xyY_ptr xyY) {
		RGB_ptr initRGB = findRGBAround(xyY);
		RGB_ptr fixRGB = fixRGB2TouchMax(initRGB);
		RGB_ptr finalRGB = findMatchRGB(xyY, fixRGB);
		return finalRGB;
	    };

	    //==================================================================
	    //
	    //==================================================================
	  StocktonWhitePointFinder::StocktonWhitePointFinder(bptr < MeterMeasurement > mm, RGB_ptr initRGB):
	    WhitePointFinder(mm), initRGB(initRGB) {

	    };
	    RGB_ptr StocktonWhitePointFinder::findRGB(xyY_ptr targetxyY) {
		using java::lang::Math;
		double_array delta;
		RGB_ptr findRGB = initRGB->clone();
		//==============================================================
		// blue的處理(x/y)
		//==============================================================
		do {
		    Patch_ptr patch =
			mm->measure(findRGB, findRGB->toString());
		    xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
		    delta = measurexyY->getDeltaxy(targetxyY);
		    int adjust = 0;
		    if (Math::abs(delta[0]) > 0.012
			&& Math::abs(delta[1]) > 0.012) {
			adjust = 5;
		    } else if (Math::abs(delta[0]) > 0.003
			       && Math::abs(delta[1]) > 0.003) {
			adjust = 3;
		    } else {
			adjust = 1;
		    }

		    if (delta[0] < 0 && delta[1] < 0) {
			findRGB->B -= adjust;
		    }
		}
		while (!(delta[0] > 0 && delta[1] > 0));
		//==============================================================

		//==============================================================
		// red的處理(x)
		//==============================================================
		do {
		    Patch_ptr patch =
			mm->measure(findRGB, findRGB->toString());
		    xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
		    delta = measurexyY->getDeltaxy(targetxyY);
		    if (delta[0] > 0) {
			findRGB->R -= 1;
		    }
		} while (!(delta[0] < 0));
		//==============================================================

		//==============================================================
		// red的處理(x)
		//==============================================================
		bool stop = false;
		do {
		    Patch_ptr patch =
			mm->measure(findRGB, findRGB->toString());
		    xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
		    delta = measurexyY->getDeltaxy(targetxyY);
		    if (delta[1] > 0) {
			//green的處理
			findRGB->G -= 1;
		    }
		    if (delta[0] > 0 && findRGB->B < 255) {
			findRGB->B += 1;
		    }
		    if (delta[0] > 0 && 255 == findRGB->B) {
			findRGB->R -= 1;
		    }
		    stop = (delta[0] < 0 && delta[1] < 0)
			|| (255 == findRGB->B && delta[1] < 0);
		} while (true == stop);
		stop = false;
		//==============================================================

		//==============================================================
		// 最終一次調整
		//==============================================================
		Patch_ptr patch =
		    mm->measure(findRGB, findRGB->toString());
		xyY_ptr measurexyY(new CIExyY(patch->getXYZ()));
		delta = measurexyY->getDeltaxy(targetxyY);
		if (findRGB->R < 255) {
		    findRGB->R += 1;
		    patch = mm->measure(findRGB, findRGB->toString());
		    measurexyY.reset(new CIExyY(patch->getXYZ()));
		    double_array delta2 =
			measurexyY->getDeltaxy(targetxyY);
		    if (Math::abs(delta2[0]) > Math::abs(delta[0])) {
			findRGB->R -= 1;
		    }
		}
		if (findRGB->G < 255) {
		    findRGB->G += 1;
		    patch = mm->measure(findRGB, findRGB->toString());
		    measurexyY.reset(new CIExyY(patch->getXYZ()));
		    double_array delta2 =
			measurexyY->getDeltaxy(targetxyY);
		    if (Math::abs(delta2[1]) > Math::abs(delta[1])) {
			findRGB->G -= 1;
		    }
		}
		//==============================================================
		return findRGB;
	    };
	    //==================================================================
	};
    };
};

