#include "rgb.h"
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <math/doublearray.h>

namespace cms {
    namespace colorspace {
	namespace depend {
	    using namespace java::lang;
	    using namespace std;
	    using namespace boost;
	    using namespace math;
	    //======================================================================
	    // RGBColor
	    //======================================================================
	     RGBColor::RGBColor():rgbColorSpace(&RGBColorSpace::unknowRGB),
		maxValue(&MaxValue::Double1) {
	    };
	     RGBColor::RGBColor(RGBColorSpace & rgbColorSpace,
				double_array rgb,
				MaxValue &
				maxValue):rgbColorSpace(&rgbColorSpace),
		maxValue(&maxValue) {

		if (rgb != null) {
		    setValues(rgb);
		}
	    };
	    RGBColor::RGBColor(int r, int g,
			       int b):rgbColorSpace(&RGBColorSpace::
						    unknowRGB),
		maxValue(&MaxValue::Int8Bit) {
		setValues(r, g, b);
	    };

	    RGBColor::RGBColor(double r, double g,
			       double b):rgbColorSpace(&RGBColorSpace::
						       unknowRGB),
		maxValue(&MaxValue::Double255) {
		setValues(r, g, b);
	    };

	  RGBColor::RGBColor(RGBColorSpace rgbColorSpace, CIEXYZ XYZ):rgbColorSpace(&rgbColorSpace),
		maxValue(&MaxValue::
			 Double1) {
		//this(colorSpace, fromXYZValues(XYZ.getValues(), colorSpace),
		//MaxValue.Double1);
	    };


	     double_array RGBColor::_getValues(double_array values) {
		values[0] = R;
		values[1] = G;
		values[2] = B;
		return values;

	    };

	    void RGBColor::_setValues( double_array values) {
		R = values[0];
		G = values[1];
		B = values[2];
	    };

	    string_vector_ptr RGBColor::getBandNames() {
		string_vector_ptr vec(new string_vector(3));

		(*vec)[0] = "R";
		(*vec)[1] = "G";
		(*vec)[2] = "B";
		return vec;
	    };
	    /*static shared_array<double> fromXYZValues(shared_array<double> XYZValues,
	       RGBBColorSpace rgbColorSpace) {
	       double[] linearRGBValues = XYZ2LinearRGBValues(XYZValues, colorSpace);
	       double[] rgbValues = linearToRGBValues(linearRGBValues, colorSpace);

	       return rgbValues;
	       } */
	    //======================================================================

	    void RGBColor::changeMaxValue(const MaxValue & type,
					  bool integerRoundDown) {
		// 類型一樣不需要轉換 || 無限制類型無法進行轉換
		if (*this->maxValue == type ||
		    *this->maxValue == MaxValue::DoubleUnlimited ||
		    type == MaxValue::DoubleUnlimited) {
		    return;
		}

		double_array values = this->getValues();
		changeMaxValue(values, *this->maxValue, type,
			       integerRoundDown);

		this->maxValue = &type;
		this->setValues(values);
		//values = null;
		/*round =
		   integerRoundDown ? Round.RoundDown : Round.RoundOff; */
	    };

	    void RGBColor::changeMaxValue(const MaxValue & type) {
		changeMaxValue(type, false);
	    };

	    void RGBColor::changeMaxValue(double_array values,
					  const MaxValue & srcType,
					  const MaxValue & destType,
					  bool integerRoundDown) {
		if (srcType.integer == true) {
		    changeIntegerMaxValue(values, srcType, destType,
					  integerRoundDown);
		} else {
		    values = normalizeTo100(values, srcType);
		    changeMaxValue(values, destType, integerRoundDown);
		}
	    };

	    double_array RGBColor::
		changeIntegerMaxValue(double_array integerValues,
				      const MaxValue & srcType,
				      const MaxValue & destType,
				      bool roundDown) {
		if (false == srcType.integer && false == destType.integer) {
		    //既然是處理整數的轉換, 當然至少要有一個是整數啦~
		    throw IllegalArgumentException
			("false == srcType.integer && false == destType.integer");
		}
		double rate = -1;

		if (true == srcType.integer && false == srcType.divisible
		    && destType.max == 255) {
		    //處理小於8bit, 也就是沒辦法整除的部份
		    rate = (destType.max + 1) / srcType.max;
		} else if (true == destType.integer
			   && false == destType.divisible
			   && srcType.max == 255) {
		    //處理小於8bit, 也就是沒辦法整除的部份
		    rate = destType.max / (srcType.max + 1);
		} else {
		    rate = destType.max / srcType.max;
		}
		//int size = integerValues.length;
		int size = RGBNumberBands;

		for (int x = 0; x < size; x++) {
		    integerValues[x] *= rate;
		    integerValues[x] = destType.integer ?
			(roundDown ? (int) integerValues[x] : Math::
			 round(integerValues[x])) : integerValues[x];
		    //小於8bit的轉換, 會有超過max的狀況, 所以要作clip
		    integerValues[x] =
			(integerValues[x] >
			 destType.max) ? destType.max : integerValues[x];
		}

		return integerValues;
	    };

	    double_array RGBColor::changeMaxValue(double_array normal100,
						  const MaxValue & type,
						  bool integerRoundDown) {
		int size = RGBNumberBands;

		if (type.integer == true) {
		    for (int x = 0; x < size; x++) {
			normal100[x] /= (100. / type.max);
			normal100[x] =
			    integerRoundDown ? (int) normal100[x] : Math::
			    round(normal100[x]);
		    }
		} else {
		    for (int x = 0; x < size; x++) {
			normal100[x] /= (100. / type.max);
		    }

		}
		return normal100;
	    };


	    double_array RGBColor::normalizeTo100(double_array values,
						  const MaxValue &
						  maxValue) {
		double max = maxValue.max;
		//int size = values.length;
		int size = RGBNumberBands;
		for (int x = 0; x < size; x++) {
		    values[x] = values[x] / max * 100;
		};
		return values;
	    };

	    void RGBColor::addValue(const Channel & channel,
				    double addvalue) {
		if (channel.isPrimaryColorChannel()) {
		    double nowvalue = this->getValue(channel);
		    this->setValue(channel, nowvalue + addvalue);
		}

		/*else {
		   Channel[]channels =
		   channel.getPrimaryColorChannel(channel);
		   for (Channel ch:channels) {
		   addValue(ch, addvalue);
		   }
		   } */
	    };

	    void RGBColor::addValue(double addvalue) {
		double_array nowvalues = this->getValues();
		double_array newvalues =
		    DoubleArray::plus(nowvalues, addvalue, RGBNumberBands);
		this->setValues(newvalues);
	    }

	    double RGBColor::getValue(const Channel & channel) {

		switch (channel.index) {
		case 1:
		    return R;
		case 2:
		    return G;
		case 3:
		    return B;
		case 4:
		    return Math::min(R, G);
		case 5:
		    return Math::min(R, B);
		case 6:
		    return Math::min(G, B);
		case 7:
		    Channel minCh = getMinChannel();
		    return getValue(minCh);
		}
	    };

	    void RGBColor::setValue(const Channel & channel, double value) {

		switch (channel.index) {
		case 1:
		    R = value;
		    break;
		case 2:
		    G = value;
		    break;
		case 3:
		    B = value;
		    break;
		case 4:
		    R = G = value;
		    break;
		case 5:
		    R = B = value;
		    break;
		case 6:
		    B = G = value;
		    break;
		case 7:
		    R = G = B = value;
		    break;
		}
	    };

	    const Channel & RGBColor::getMinChannel() {
		double_array rgbValues = getValues();
		int minIndex = Math::minIndex(rgbValues, RGBNumberBands);
		return Channel::getChannelByArrayIndex(minIndex);
	    };

	    const Channel & RGBColor::getMaxChannel() {
		double_array rgbValues = getValues();
		int maxIndex = Math::maxIndex(rgbValues, RGBNumberBands);
		return Channel::getChannelByArrayIndex(maxIndex);
	    };
	    Object_ptr RGBColor::clone() {
		return Object_ptr(new RGBColor(*this));
	    };

	    const RGB_ptr RGBColor::White(new RGBColor(255, 255, 255));
	    const RGB_ptr RGBColor::Black(new RGBColor(0, 0, 0));
	};
    };
};

