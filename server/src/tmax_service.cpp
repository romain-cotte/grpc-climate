#include "tmax_service.h"

TmaxService::TmaxService(const std::string &file_path) {
  netcdf_proj.open(file_path);
}


::grpc::Status TmaxService::GetValue(::grpc::ServerContext* context,
                                const ::netcdf::DateLocation* request,
                                ::netcdf::Temperature* response) {
  cout << "GetValue for " << endl;
  cout << "Days since start: " << request->days_since_start() << std::endl;
  cout << "Latitude        : " << request->latitude() << std::endl;
  cout << "Longitude       : " << request->longitude() << std::endl;

  float result = netcdf_proj.get_projection(
    request->days_since_start(),
    request->latitude(),
    request->longitude()
  );
  response->set_value(result);

  cout << "Value           : " << response->value() << endl;
  return grpc::Status::OK;
}
