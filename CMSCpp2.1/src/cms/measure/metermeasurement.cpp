#include <includeall.h>
#pragma hdrstop
#include "MeterMeasurement.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace measure {
	using namespace boost;
	using namespace cms;
	using namespace Dep;
	using namespace cms::measure::meter;
	using namespace cms::measure::cp;
	using namespace std;
	using namespace java::lang;

	void MeterMeasurement::init(bool calibration) {
	    measureWindow = MeasureWindow;
	    if (true == calibration) {
		calibrate();
	    }
	};
      MeterMeasurement::MeterMeasurement(shared_ptr < Meter > meter, bool calibration):meter(meter), waitTimes(meter->getSuggestedWaitTimes()),
	    measureWindowClosing(false), titleTouched(false),
	    fakeMeasure(false) {
	    init(calibration);
	};

	void MeterMeasurement::calibrate() {
	    MeasureUtils::meterCalibrate(*this);
	};

	void MeterMeasurement::close() {
	    setMeasureWindowsVisible(false);
	    measureWindow->Close();
	    meterClose();
	};

	void MeterMeasurement::setMeasureWindowsVisible(bool visible) {
	    if (!fakeMeasure) {
		if (null == measureWindow) {
		    measureWindow = MeasureWindow;
		}
		measureWindow->setVisible(visible);
		measureWindowClosing = !visible;
	    }
	};

	Patch_ptr
	    MeterMeasurement::measure(RGB_ptr rgb,
				      const string_ptr patchName) {
	    return measure0(rgb, patchName, nil_string_ptr,
			    nil_string_ptr);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b,
					    const string_ptr patchName) {
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, patchName);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b,
					    const string & patchName) {
	    string_ptr str(new string(patchName));
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, str);
	};

	void MeterMeasurement::setBlankTimes(int blankTimes) {
	    this->blankTimes = blankTimes;
	};
	void MeterMeasurement::setWaitTimes(int waitTimes) {
	    this->waitTimes = waitTimes;
	    /*if (waitTimes == 0) {
	       int x = 1;
	       } */
	};
	int MeterMeasurement::getWaitTimes() {
	    return waitTimes;
	};
	void MeterMeasurement::setFakeMeasure(bool fake) {
	    this->fakeMeasure = fake;
	};
	bool MeterMeasurement::isFakeMeasure() {
	    return fakeMeasure;
	};

	bptr < cms::measure::meter::Meter > MeterMeasurement::getMeter() {
	    return meter;
	};

	void MeterMeasurement::meterClose() {

	};

	Patch_ptr
	    MeterMeasurement::measure0(RGB_ptr measureRGB,
				       string_ptr patchName,
				       string_ptr titleNote,
				       string_ptr timeNote) {
	    setMeasureWindowsVisible(true);
	    //�q�����C��, �q�����C��i��P�ɨ㪺�C�⤣�P, �ҥH�S�O�W�ߥX���ܼ�

	    if (!titleTouched) {
		//�p�Gtitle�S�Q�]�w�L
		if (titleNote != NULL) {
		    //measureWindow.setTitle("Measure Window " + titleNote);
		    /*measureWindow->Caption =
		       AnsiString("Measure Window " + titleNote); */

		} else {
		    measureWindow->Caption = AnsiString("Measure Window");
		}
	    }
	    //==========================================================================
	    // �ܴ��������C�⪺�u�Ȱ��d
	    //==========================================================================
	    if (!fakeMeasure) {
		measureWindow->setRGB(measureRGB);
		Application->ProcessMessages();
		Sleep(waitTimes);
	    }
	    //==========================================================================

	    if (true == measureWindowClosing) {
		//�p�G�����Q����, �N�����q��
		return Patch_ptr((Patch *) NULL);
	    }
	    double_array result = meter->triggerMeasurementInXYZ();

	    XYZ_ptr XYZ(new Indep::CIEXYZ(result));
	    Patch_ptr patch(new Patch(patchName, XYZ, XYZ, measureRGB));
	    return patch;
	};
	//======================================================================

	//======================================================================
	// MeasureResult
	//======================================================================
	void MeasureUtils::
	    meterCalibrate(MeterMeasurement & meterMeasurement) {
	    shared_ptr < Meter > meter = meterMeasurement.meter;
	    TMeasureWindow *measureWindow = meterMeasurement.measureWindow;
	    meterCalibrate(meter, measureWindow);
	};
	void MeasureUtils::meterCalibrate(shared_ptr < Meter > meter,
					  TMeasureWindow * measureWindow) {
	    if (!meter->isConnected()) {
		throw IllegalStateException("!meter.isConnected()");
	    } else {
		if (measureWindow != NULL) {
		    //show�X�¹�, �קK�v�T�ե�
		    measureWindow->setRGB(0, 0, 0);
		    Application->ProcessMessages();
		    measureWindow->setVisible(true);
		}
		ShowMessage(meter->getCalibrationDescription()->c_str());
		meter->calibrate();
		if (measureWindow != null) {
		    //�����¹�
		    measureWindow->setVisible(false);
		}
		ShowMessage("End of calibration");
	    };
	};

	MeasureResult::MeasureResult(Patch_vector_ptr result,
				     int practicalMeasureCount):result
	    (result), practicalMeasureCount(practicalMeasureCount) {

	};
	//======================================================================

	//======================================================================
	// MeasureTool
	//======================================================================
      MeasureTool::MeasureTool(bptr < cms::measure::MeterMeasurement > mm):mm(mm),
	    stop(false)
	{

	};
	Patch_vector_ptr MeasureTool::rampMeasure(const Dep::
						  Channel & channel,
						  int start, int end,
						  int step) {
	    Patch_vector_ptr vector(new Patch_vector());
	    for (int c = start; c >= end; c -= step) {
		RGB_ptr rgb(new RGBColor());
		rgb->setValue(channel, c);
		Patch_ptr patch = mm->measure(rgb, rgb->toString());
		vector->push_back(patch);
		if (true == stop) {
		    stop = false;
		    mm->setMeasureWindowsVisible(false);
		    return nil_Patch_vector_ptr;
		}
	    };
	    mm->setMeasureWindowsVisible(false);
	    return vector;
	};
	void MeasureTool::windowClosing() {
	    stop = true;
	}
	//======================================================================
    };
};
