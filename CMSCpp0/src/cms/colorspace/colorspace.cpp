#include "colorspace.h"
#include "java/lang.h"

namespace cms {
    namespace colorspace {
	using std::string;

  /**
   * �åd��y��=>���y��
   * @param cartesianValues double[]
   * @return double[]
   */
	static double *cartesian2polarCoordinatesValues(double
							*cartesianValues) {
	    using java::lang::Math;
	    /*if (cartesianValues.length != 3) {
	       throw new
	       IllegalArgumentException
	       ("cartesianValues.length != 3");
	       } */
	    double *polarValues = new double[3];

	     polarValues[0] = cartesianValues[0];
	    double t1 = cartesianValues[1];
	    double t2 = cartesianValues[2];
	     polarValues[1] = Math::sqrt(Math::pow(cartesianValues[1], 2) +
					Math::pow(cartesianValues[2], 2));
	    if (t1 == 0 && t2 == 0) {
		polarValues[2] = 0;
	    } else {
		polarValues[2] = Math::atan2(t2, t1);
	    }
	    polarValues[2] *= (180.0 / Math::PI);
	    while (polarValues[2] >= 360.0) {	// Not necessary, but included as a check.
		polarValues[2] -= 360.0;
	    }
	    while (polarValues[2] < 0) {
		polarValues[2] += 360.0;
	    }
	    return polarValues;
	}

	string & ColorSpace::getName() {
	    return this->getClass().getSimpleName();
	}
      ColorSpace::ColorSpace():setValuesLocked(false) {
	}
    };


};

