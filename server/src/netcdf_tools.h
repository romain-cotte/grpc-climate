// #ifndef NETCDF_TOOLS_H
// #define NETCDF_TOOLS_H

#include <netcdf>
#include <vector>

void display_header_group(netCDF::NcGroup nc_group, int depth = 0);

struct Statistics {
  float max, min, mean;
};

class NetcdfProjection {
private:
  netCDF::NcFile nc_file;
  float *data;


public:
  size_t n_latitudes, n_longitudes;
  size_t n_days_since_start;
  uint   n_all;

  float start_latitude, start_longitude;
  float end_latitude, end_longitude;

  int   *days_since_start;
  float *latitudes, *longitudes;

  NetcdfProjection();
  NetcdfProjection(std::string file_path);
  ~NetcdfProjection();

  void open(std::string file_path);


  void validate_coordinates(float latitude, float longitude) const;
  float get_projection(int days_since_start, float latitude, float longitude) const;
  std::vector<float> get_serie(float latitude, float longitude) const;
  Statistics get_statistics(float latitude, float longitude) const;
};

// #endif /* NETCDF_TOOLS_H */
