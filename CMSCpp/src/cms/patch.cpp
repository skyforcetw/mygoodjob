#include "patch.h"

namespace cms {
    using namespace boost;
    using namespace std;
    using namespace cms::colorspace;
     Patch::Patch(shared_ptr < string > name, shared_ptr < CIEXYZ > XYZ,
		  shared_ptr < CIEXYZ > normalizedXYZ,
		  shared_ptr < RGBColor > rgb):name(name), XYZ(XYZ),
	normalizedXYZ(normalizedXYZ), rgb(rgb) {
    };

    shared_ptr < string > Patch::getName() {
	return name;
    };

    shared_ptr < cms::colorspace::CIEXYZ > Patch::getXYZ() {
	return XYZ;
    };
    shared_ptr < cms::colorspace::CIEXYZ > Patch::getNormalizedXYZ() {
	return normalizedXYZ;
    };
    shared_ptr < cms::colorspace::RGBColor > Patch::getRGB() {
	return rgb;
    };
};

