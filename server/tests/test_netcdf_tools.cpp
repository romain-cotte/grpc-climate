#include <iomanip>
#include <iostream>
#include <netcdf>


#include "../src/netcdf_tools.h"

using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;


int main(int argc, char* argv[]) {
  string file_path = "../../server/data/era5_Tmax_40.0_0.0_projection_2030.nc";

  NetcdfProjection proj = NetcdfProjection(file_path);

  cout << std::setprecision(17);
  int days_since_start = 29;

  cout << "0, 40.0, 0.0: " << proj.get_projection(days_since_start, 40.0, 0.0) << endl;

  return 0;
}
