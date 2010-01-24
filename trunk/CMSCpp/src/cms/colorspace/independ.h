#ifndef INDEPENDH
#define INDEPENDH
#include "colorspace.h"
#include <cms/core.h>
//#include "ciexyz.h"
#include <boost/shared_ptr.hpp>

namespace cms {
    namespace colorspace {


	enum CIEStandard {
	    //CIE提供的值
	    ActualStandard,
	    //修正CIE的值(會較準確)
	    IntentStandard
	};
	enum Degree {
	    Two = 2, Ten = 10
	};
	class CIEXYZ;
	class DeviceIndependentSpace:public ColorSpace {
	  protected:
	    Degree _degree;
	    static double epsilon;
	    static double kappa;

	     DeviceIndependentSpace():_degree(Two) {

	    };
	     DeviceIndependentSpace(shared_array < double >values) {
		setValues(values);
	    };
	     DeviceIndependentSpace(double value1, double value2,
				    double value3) {
		double values[] = {
		    value1, value2, value3
		};
		 setValues(shared_array < double >(values));
	    };

	    int getNumberBands() {
		return 3;
	    }
	  public:
	    Degree getDegree() {
		return _degree;
	    };
	    void setDegree(Degree degree) {
		_degree = degree;
	    };
	    static void setCIEStandard(CIEStandard standard) {
		if (standard == ActualStandard) {
		    epsilon = ACTUAL_EPSILON;
		    kappa = ACTUAL_KAPPA;
		} else {
		    epsilon = INTENT_EPSILON;
		    kappa = INTENT_KAPPA;
		}
	    }
	    static const double ACTUAL_EPSILON;
	    static const double ACTUAL_KAPPA;

	    static const double INTENT_EPSILON;
	    static const double INTENT_KAPPA;
	    virtual CIEXYZ toXYZ() = 0;
	};


	enum NormalizeY {
	    Normal100 = 100, Normal1 = 1, Not = -1
	};

	class NormalizeYOperator {
	  public:
	    virtual void normalize(NormalizeY normalizeY) = 0;

	    virtual void normalizeY() = 0;

	    void normalizeY100() {
		normalizeY();
		normalize(Normal100);
	    };
	    virtual void setNormalizeNot() = 0;

	    const static double NormalFactor;
	};

	class CIEXYZ:public DeviceIndependentSpace, NormalizeYOperator {
	  protected:
	    NormalizeY _normalizeY;
	  public:
	    double X, Y, Z;
	     vector < string > getBandNames() {
		vector < string > names(3);
		names[0] = "X";
		names[1] = "Y";
		names[2] = "Z";
		return names;
	    };

	    double getCCT() {
		//return CorrelatedColorTemperature.XYZ2CCTByRobertson(this);
	    };

	    NormalizeY getNormalizeY() {
		return _normalizeY;
	    };
	    double getSaturation(CIEXYZ white) {
		/*double[] uv = this.getuvPrimeValues();
		   double[] uvn = white.getuvPrimeValues();
		   return 13 * Math.sqrt(Maths.sqr(uv[0] - uvn[0]) +
		   Maths.sqr(uv[1] - uvn[1])); */
	    };
	    shared_array < double >getuvPrimeValues() {
		/*CIExyY xyY = CIExyY.fromXYZ(this);
		   return xyY.getuvPrimeValues(); */
	    };
	    shared_array < double >getuvValues() {
		/*CIExyY xyY = CIExyY.fromXYZ(this);
		   return xyY.getuvValues(); */
	    }
	    shared_array < double >getValues(shared_array < double >values,
					     NormalizeY normalizeY) {
		if (_normalizeY == Not) {
		    throw
			IllegalStateException
			("this.normalizeY == NormalizeY.Not");
		}
		getValues(values);
		if (_normalizeY == normalizeY) {
		    return values;
		}
		switch (_normalizeY) {
		case Normal100:
		    //DoubleArray.copy(DoubleArray.times(values, 1. / 100),
		    //values);
		    break;
		case Normal1:
		    //DoubleArray.copy(DoubleArray.times(values, 100),
		    //values);
		    break;
		}
		return values;
	    };
	    shared_array < double >getValues() {
		return ColorSpace::getValues();
	    };
	    shared_array < double >getValues(shared_array < double >values) {
		return ColorSpace::getValues(values);
	    };

	    shared_array < double >_getValues(shared_array <
					      double >values) {
		//shared_array < double >values(new double[3]);
		values[0] = X;
		values[1] = Y;
		values[2] = Z;
		return values;
	    };
	    void _setValues(shared_array < double >values) {
		X = values[0];
		Y = values[1];
		Z = values[2];
	    };

	    CIEXYZ toXYZ() {

	    };

	    shared_array < double >getWhitenessIndex() {
		//return new CIExyY(this).getWhitenessIndex();
	    };

	    shared_array < double >getxyValues() {
		if (Y == 0) {
		    //return new double[] {
		    //0, 0};
		    //double *result  = new double[2];
		    shared_array < double >values(new double[2]);
		    values[0] = 0;
		    values[1] = 0;
		    return values;
		} else {
		    double sum = (X + Y + Z);
		    double x = X / sum;
		    double y = Y / sum;
		    shared_array < double >values(new double[2]);
		    values[0] = x;
		    values[1] = y;
		    return values;
		}
	    };

	    shared_array < double >getxyzValues() {
		double sum = (X + Y + Z);
		double x = X / sum;
		double y = Y / sum;
		double z = 1 - x - y;
		shared_array < double >values(new double[3]);
		values[0] = x;
		values[1] = y;
		values[2] = z;
		return values;
	    };

	    double getYellownessIndex() {
		return 100 * (1.2985 * X - 1.1335 * Z) / Y;
	    };

	    boolean isBlack() {
		return X == 0 && Y == 0 && Z == 0;
	    };

	    boolean isLegal() {
		if (Y == 0 && (X > 0 || Z > 0)) {
		    //如果Y=0,就應該為黑色,其他頻道不應該有值
		    return false;
		} else if (Y != 0 && X == 0) {
		    //如果Y有值(具有亮度),X頻道就也應該有值,Z則不一定
		    return false;
		} else if (X < 0 || Y < 0 || Z < 0) {
		    return false;
		}

		return true;
	    };
	    boolean isLegal(CIEXYZ white) {
		return isLegal() && X <= white.X && Y <= white.Y &&
		    Z <= white.Z;
	    };
	    static shared_ptr < CIEXYZ > minus(const CIEXYZ & XYZ1,
					       const CIEXYZ & XYZ2) {

		shared_ptr < CIEXYZ > result(new CIEXYZ());
		result->X = XYZ1.X - XYZ2.X;
		result->Y = XYZ1.Y - XYZ2.Y;
		result->Z = XYZ1.Z - XYZ2.Z;
		return result;
	    };

	    void normalize(CIEXYZ normal) {
		double factor = (NormalFactor / normal.Y);
		X *= factor;
		Y *= factor;
		Z *= factor;
		_normalizeY = Normal1;
	    };

	    void normalizeY() {
		double factor = NormalFactor / Y;
		X *= factor;
		Z *= factor;
		Y = NormalFactor;
		_normalizeY = Normal1;
	    };

	    void normalize(NormalizeY normalizeY) {

		shared_array < double >values =
		    getValues(shared_array < double >(new double[3]),
			      normalizeY);
		setValues(values);
		_normalizeY = normalizeY;
	    };
	    void setNormalizeNot() {
		_normalizeY = Not;
	    };
	};

    };
};
#endif

