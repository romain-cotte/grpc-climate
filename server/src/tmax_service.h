#include <netcdf>

#include "netcdf_tools.h"
#include <myproto/tmax.pb.h>
#include <myproto/tmax.grpc.pb.h>


using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;


class TmaxService final: public netcdf::Tmax::Service {

private:
  NetcdfProjection netcdf_proj;

public:
  TmaxService(const string &file_path);

  virtual ::grpc::Status GetValue(::grpc::ServerContext* context,
                                  const ::netcdf::DateLocation* request,
                                  ::netcdf::Temperature* response);

};
