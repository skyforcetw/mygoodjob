#ifndef TCONCONTROLH
#define TCONCONTROLH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
//#include <java/lang.h>
#include <cms/util/util.h>
//#include <i2c/core/ReadWritefunc.h>

namespace i2c {
    class TCONControl {
      private:
	bptr < TCONParameter > parameter;
	bptr < i2cControl > control;
	bptr < i2cControl > control2;
	const bool dualTCON;

      public:
	 TCONControl(bptr < TCONParameter > parameter, bptr < i2cControl > control);
	 TCONControl(bptr < TCONParameter > parameter,
		     bptr < i2cControl > control1, bptr < i2cControl > control2);
	static bptr < cms::util::ByteBuffer > getRGBByteBuffer(int r, int g, int b, const
							       DirectGammaType & directGammaType);
	static bptr < cms::util::ByteBuffer > getRGBByteBufferWith62301(int r, int g, int b,
									const DirectGammaType &
									directGammaType);
	static bptr < cms::util::ByteBuffer > getRGBByteBufferWith12409Aging(int r, int g, int b,
									     const DirectGammaType &
									     directGammaType);
	static bptr < cms::util::ByteBuffer > getRGBByteBufferWith12409(int r, int g, int b,
								        const DirectGammaType &
								        directGammaType);
        static bptr < cms::util::ByteBuffer > getRGBByteBufferWith11311(int r, int g, int b,
								        const DirectGammaType &
								        directGammaType);
        static bptr < cms::util::ByteBuffer > getRGBByteBufferWith12411Aging(int gray,
								        const DirectGammaType &
								        directGammaType);
        static bptr < cms::util::ByteBuffer > getRGBByteBufferWith12411(int r, int g, int b,
								        const DirectGammaType &
								        directGammaType);

	bool setDirectGammaRGB(RGB_ptr rgb);
	bool setDirectGammaRGB(int r, int g, int b);
        bool setAgingModeRGB(int r, int g, int b);
        bool setPGModeRGB(int r, int g, int b);
	void setGammaTest(bool enable);
        void setTconAgingMode(bool enable);
        void setTconAgingTiming(bool enable);
        void setTconPGMode(bool enable);

	const Dep::MaxValue & getLUTBit();
        AnsiString getLUTType();
	void setDGLut(RGB_vector_ptr rgbVector);
	RGB_vector_ptr getDGLut();
	void setDG(bool enable);
	bool isDG();
	void setFRC(bool enable);
	bool isFRC();
	unsigned char readByte(int dataAddress);
	void writeByte(int dataAddress, unsigned char data);
	bool isGammaTestEnable();
        bool isAgingModeEnable();
        bool isPGModeEnable();
      private:

	void write(int dataAddress, bptr < cms::util::ByteBuffer > data);
	 bptr < cms::util::ByteBuffer > read(int dataAddress, int size);
	 bptr < cms::util::ByteBuffer > read(int dataAddress, int size, int tconIndex);
	static int_array getLMHData(int data);

	void setSingleBitData(int dataAddress, unsigned char bit, bool data);
        void setBitData(int dataAddress, unsigned char Startbit, unsigned char Endbit, unsigned char data);
        void setTwoByteData(int MSBAddress, unsigned char MSB_Startbit, unsigned char MSB_Endbit,
                            int LSBAddress, unsigned char LSB_Startbit, unsigned char LSB_Endbit, int value);                                     
	bool getBitData(int dataAddress, unsigned char bit);
      public:
	static bptr < cms::util::ByteBuffer > getDGLut10BitByteBuffer(RGB_vector_ptr rgbVector);
	static bptr < cms::util::ByteBuffer >
	    getDGLut10BitByteBufferType2(RGB_vector_ptr rgbVector);

        //DGLut 12Bit Type        Type1: M0 L0      Type2: H0 M0
        //0000 | 0000 | 0000             L1 H0             L0 H1
        // H      M       L              H1 M1             M1 L1
	static bptr < cms::util::ByteBuffer > getDGLut12BitByteBufferType1(RGB_vector_ptr rgbVector);
        static bptr < cms::util::ByteBuffer > getDGLut12BitByteBufferType2(RGB_vector_ptr rgbVector);
    };
};

#endif

