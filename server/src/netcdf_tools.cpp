#include <netcdf>

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

void display_header_group(NcGroup nc_group, int depth = 0) {
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

