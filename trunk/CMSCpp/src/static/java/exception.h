#ifndef EXCEPTIONH
#define EXCEPTIONH
#include <exception>
#include <stdexcept>
#include <string>
#include "lang.h"


namespace java {
    namespace lang {
	using namespace std;
	class Exception:public exception, java::lang::Object {
	  public:
	    Exception();
	    Exception(string message) {
		this->message = message;
	    }

	    string & toString() {
		return message;
	    };
	  private:
	     string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException();
	    RuntimeException(string message):Exception(message) {

	    }
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(string message):RuntimeException(message) {

	    }
	};

	class IllegalArgumentException:public RuntimeException {
	  public:
	    IllegalArgumentException();
	    IllegalArgumentException(string
				     message):RuntimeException(message) {

	    }
	};

    };
};

#endif

