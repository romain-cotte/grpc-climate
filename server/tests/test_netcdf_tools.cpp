#include <assert.h>
#include <iomanip>
#include <iostream>
#include <netcdf>

#define IS_TRUE(x) { \
  if (!(x)) { \
    std::cout << __FILE__ << " failed on line " << __LINE__ << std::endl; \
    assert(0); \
  } \
}

#define ARE_EQUAL(x, y) { \
  IS_TRUE(abs(x-y) < 1E-7) \
}


#include "../src/netcdf_tools.h"

using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;


int main(int argc, char* argv[]) {
  string file_path = "../../server/data/era5_Tmax_40.0_0.0_projection_2030.nc";

  NetcdfProjection proj = NetcdfProjection(file_path);

  int days_since_start = 29;
  ARE_EQUAL(proj.get_projection(days_since_start, 40.0, 0.0), 15.003257751464844);

  vector<float> serie = proj.get_serie(40.0, 0.0);

  ARE_EQUAL((int)serie.size(), 10950);

  // for (float x: serie) {
  //   cout << x << " ";
  // }
  // cout << endl;

  return 0;
}
