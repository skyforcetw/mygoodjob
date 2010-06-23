#ifndef DGCODEFILEH
#define DGCODEFILEH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <ADODB.hpp>
#include <DB.hpp>
//�����ؤ��Y���
#include <java/lang.h>
#include "excelfile.h"

namespace cms {
    namespace colorformat {


	class DGLutProperty;
	class DGLutFile:public ExcelAccessBase {
	  private:
	    string_vector_ptr makeValues(int n, Component_ptr c);
	    string_vector_ptr makeValues(int n,
					 Component_ptr c,
					 RGB_ptr rgbGamma,
					 RGB_ptr rgbGammaFix);
	    static const std::string & GammaTable;
	    static const std::string & RawData;

	  public:
	     DGLutFile(const std::string & filename, Mode mode);


	    void setProperty(const DGLutProperty & property);
	     bptr < DGLutProperty > getProperty();


	    void setRawData(Component_vector_ptr componentVector,
			    RGBGamma_ptr initialRGBGamma,
			    RGBGamma_ptr finalRGBGamma);
	    void setGammaTable(RGB_vector_ptr dglut);
	    Component_vector_ptr getComponentVector();
	    RGB_vector_ptr getGammaTable();

	    /*
	       �q������Ƥ����o�O0~255���q, ���O���ͪ�gamma�@�w�O����
	       �Ӧp���X���?��ا@�k
	       1. �����q����, �ϸ�Ƭ�0~255
	       2. �����q���쪺gamma, ���O�ʥF��gamma..�N�ʥF�a...
	       �ϥ�����DG Code���ɭ��٬O�i�H�ͥX��.

	       ��ܤ�פG, �ҥH���Ψ�N�h�Y��rgbgamma, ��setRawData�ۤv�h�z */
	};

	class DGLutProperty {
	    friend class DGLutFile;
	  private:
	    /*
	       static const std::string Start;
	       static const std::string End;
	       static const std::string Step;
	       static const std::string LowStart;
	       static const std::string LowEnd;
	       static const std::string LowStep;
	       static const std::string HighStart;
	       static const std::string HighEnd;
	       static const std::string HighStep;
	       static const std::string P1P2;
	       static const std::string P1;
	       static const std::string P2;
	       static const std::string RB;
	       static const std::string RBUnder;
	       static const std::string In;
	       static const std::string LUT;
	       static const std::string FRC;
	       static const std::string Out;
	       static const std::string Gamma;
	       static const std::string RGamma;
	       static const std::string GGamma;
	       static const std::string BGamma;
	       static const std::string GammaCurve;
	       static const std::string GByPass;
	       static const std::string BGain;
	       static const std::string BMax;
	       static const std::string Gamma256;
	       static const std::string FRC_NR;
	       static const std::string DimCorrect;

	       static const std::string KeepMaxLumi; */
	    static const std::string On;
	    static const std::string Off;

	    //bptr < cms::lcd::calibrate::LCDCalibrator > c;
	     cms::lcd::calibrate::LCDCalibrator * c;
	     bptr < DGLutFile > d;
	    DGLutFile *d2;
	    void store(DGLutFile & dglut) const;
	     std::map < const std::string, string_ptr) propertyMap;
	    void addProperty(const std::string key, string_ptr value);
	    void addProperty(const std::string key,
			     const std::string value);
	    void initProperty(bptr < DGLutFile > d);
	    void initProperty(DGLutFile * d);
	  public:
	    //DGLutProperty(bptr < cms::lcd::calibrate::LCDCalibrator > c);
	     DGLutProperty(cms::lcd::calibrate::LCDCalibrator * c);
	     DGLutProperty(bptr < DGLutFile > d);
	     DGLutProperty(DGLutFile * d);
	    string_ptr getProperty(const std::string key);
	    xyY_ptr getReferenceColor(const Dep::Channel & ch);
	};
    };
};
#endif
