#include <netcdf>
#include "netcdf_tools.h"

using namespace netCDF::exceptions;
using namespace netCDF;
using namespace std;


vector<size_t> get_dimensions(const NcGroup &nc_group) {
  vector<size_t> dim;
  for (auto [name, nc_dim]: nc_group.getDims()) {
    dim.push_back(nc_dim.getSize());
  }
  return dim;
}

void display_dimensions(const NcGroup &nc_group, int depth = 0) {
  string prefix(2*depth, ' ');
  cout << prefix << "  dimensions:" << endl;
  for (auto [name, nc_dim]: nc_group.getDims()) {
    cout << prefix  << "   " << name << " = " << nc_dim.getSize() << " ;" << endl;
  }
  // return dim;
}

void display_variables(const NcGroup &nc_group, int depth = 0) {
  string prefix(2*depth, ' ');

  cout << prefix << "  variables:" << endl;
  for (auto [name, nc_var]: nc_group.getVars()) {
    NcType nc_type = nc_var.getType();
    cout << prefix << "   " << nc_type.getName() << " " << nc_var.getName() << "(";
    for (int i = 0; i < nc_var.getDimCount(); ++i) {
      if (i != 0) {
        cout << ", ";
      }
      NcDim nc_dim = nc_var.getDim(i);
      cout << nc_dim.getName();
    }
    cout << ");" << endl;

    for (auto [s, nc_var_att]: nc_var.getAtts()) {
      NcType nc_type = nc_var_att.getType();
      cout << prefix << "    " << name << ":" << s << "(" << nc_type.getName() << ")";

      NcVarAtt att = nc_var.getAtt(s);

      if (nc_type.getName() == "char") {
        string units;
        att.getValues(units);
        cout << " = \"" << units << "\"";
      }
      if (nc_type.getName() == "double") {
        double *d = new double;
        att.getValues(d);
        cout << " = " << *d;
      }
      if (nc_type.getName() == "float") {
        float *f = new float;
        att.getValues(f);
        cout << " = " << *f;
      }
      cout << endl;
    }
  }
}

void display_header_group(NcGroup nc_group, int depth) {
  // cout << "name       : " << nc_group.getName(true) << endl;
  // cout << "is null    : " << nc_group.isNull() << endl;
  // cout << "id         : " << nc_group.getId() << endl;
  // cout << "group count: " << nc_group.getGroupCount() << endl;
  // cout << "getVarCount: " << nc_group.getVarCount() << endl;
  string prefix(2*depth, ' ');

  cout << prefix << "group: " << nc_group.getName(false) << " {" << endl;
  if (nc_group.getVarCount()) {
    display_dimensions(nc_group, depth);
    display_variables(nc_group, depth);
  }
  if (nc_group.getGroupCount()) {
    cout << endl;
  }
  for (auto [name, subgroup]: nc_group.getGroups()) {
    display_header_group(subgroup, depth+1);
  }
  cout << prefix << "}" << endl;
}


NetcdfProjection::NetcdfProjection() {}
NetcdfProjection::NetcdfProjection(std::string file_path) {
  open(file_path);
}

void NetcdfProjection::open(std::string file_path) {
  nc_file.open(file_path, NcFile::read);

  NcDim lat_dim  = nc_file.getDim("latitude");
  NcDim lon_dim  = nc_file.getDim("longitude");
  NcDim date_dim = nc_file.getDim("date");

  if (lat_dim.isNull() || lon_dim.isNull() || date_dim.isNull()) {
    return;
  }

  n_latitudes        = lat_dim.getSize();
  n_longitudes       = lon_dim.getSize();
  n_days_since_start = date_dim.getSize();

  n_all              = (uint)n_days_since_start * n_latitudes * n_longitudes;

  cout << n_longitudes << " " << n_longitudes << endl;
  cout << "days_since_start: " <<  n_days_since_start << endl;

  days_since_start = new int[n_days_since_start];
  latitudes        = new float[n_latitudes];
  longitudes       = new float[n_longitudes];


  NcVar date_var = nc_file.getVar("date");
  NcVar lat_var  = nc_file.getVar("latitude");
  NcVar lon_var  = nc_file.getVar("longitude");

  if (date_var.isNull() || lat_var.isNull() || lon_var.isNull()) {
    printf("Var is null");
    return;
  }

  // cout << "size" << lat_var.getSize() << endl;

  date_var.getVar(days_since_start);
  lat_var.getVar(latitudes);
  lon_var.getVar(longitudes);

  start_latitude  = latitudes[0];
  start_longitude = longitudes[0];

  cout << "start_latitude:" << start_latitude << endl;
  cout << "start_longitude:" << start_longitude << endl;

  // for (int i = 0; i < n_days_since_start; ++i) {
  //   cout << ":" << days_since_start[i] << endl;
  // }

  data = new float[n_all];

  NcVar tasmax_var = nc_file.getVar("tasmax");

  if (tasmax_var.isNull()) {
    printf("Error");
    return;
  }

  tasmax_var.getVar(data);
  // for (int i = 0; i < n_all; ++i) {
  //   cout << data[i] << " ";
  // }
  // cout << endl;
}


NetcdfProjection::~NetcdfProjection() {
  delete[] days_since_start;
  delete[] latitudes;
  delete[] longitudes;
  delete[] data;
}


float NetcdfProjection::get_projection(int days_since_start,
                                      float latitude,
                                      float longitude) {

  if (latitude < start_latitude) {
    throw std::invalid_argument("latitude < start_latitude");
  }
  if (longitude < start_longitude) {
    throw std::invalid_argument("longitude < start_longitude");
  }

  float d_lat = latitude - start_latitude;
  float d_lon = longitude - start_longitude;

  int ilat = d_lat / 0.25;
  int ilon = d_lon / 0.25;


  int i = days_since_start * (n_latitudes * n_longitudes) +
          ilat * n_longitudes +
          ilon;

  cout << "ilat: " << ilat << endl;
  cout << "ilon: " << ilon << endl;

  cout << "i: " << i << endl;

  return data[i];
}
