
#include <iostream>

#include "Application.h"
#include "ApplicationOptions.h"

using namespace cpuh0g;

int main (int argc, char* argv[]) {
  Application app;
  ApplicationOptions options(argc, argv);

  int result = EXIT_SUCCESS;
  try {
    result = app.run(options);
  }
  catch (string message) {
    cerr << "caught error: " << message << endl;
    result = EXIT_FAILURE;
  }
  catch (const char* message) {
    cerr << "caught error: " << message << endl;
    result = EXIT_FAILURE;
  }
  catch (...) {
    cerr << "caught unexpected error" << endl;
  }
  
  return result;
}
