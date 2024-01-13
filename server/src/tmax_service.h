#include <netcdf>

#include "netcdf_tools.h"
#include <myproto/tmax.pb.h>
#include <myproto/tmax.grpc.pb.h>


using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;
using namespace grpc;
using namespace climate;

class TmaxService final: public Tmax::Service {

private:
  NetcdfProjection netcdf_proj;

public:
  TmaxService(const string &file_path);

  virtual Status GetValue(ServerContext* context,
                          const DateLocation* request,
                          Temperature* response);

  virtual Status GetTemperatures(ServerContext* context,
                                 const Location* request,
                                 ServerWriter<Temperature>* writer);

};
