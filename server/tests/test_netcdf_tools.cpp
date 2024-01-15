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



void test_get_projection(const NetcdfProjection &proj) {
  int days_since_start = 29;
  ARE_EQUAL(proj.get_projection(days_since_start, 40.0, 0.0), 15.003257751464844);
}

void test_get_serie(const NetcdfProjection &proj) {
  vector<float> serie = proj.get_serie(40.0, 0.0);
  ARE_EQUAL((int)serie.size(), 10950);
}

void test_get_statistics(const NetcdfProjection &proj) {
  Statistics stats = proj.get_statistics(40.0, 0.0);
  std::cout << std::setprecision(15);
  cout << "Min: " << stats.min << ", Max: " << stats.max << endl;
  cout << "Mean: " << stats.mean << endl;
  ARE_EQUAL(stats.min, 6.68211650848389);
  ARE_EQUAL(stats.max, 39.751823425293);
  ARE_EQUAL(stats.mean, 21.6053142547607);
}


int main(int argc, char* argv[]) {
  string file_path = "../../server/data/era5_Tmax_40.0_0.0_projection_2030.nc";

  NetcdfProjection proj = NetcdfProjection(file_path);

  test_get_projection(proj);
  test_get_serie(proj);
  test_get_statistics(proj);


  return 0;
}
