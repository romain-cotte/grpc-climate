#include "tmax_service.h"

TmaxService::TmaxService(const std::string &file_path) {
  netcdf_proj.open(file_path);
}


::grpc::Status TmaxService::GetValue(::grpc::ServerContext* context,
                                const ::netcdf::DateLocation* request,
                                ::netcdf::Temperature* response) {


  int days_since_start = request->days_since_start();
  float latitude = request->latitude();
  float longitude = request->longitude();


  if (days_since_start < 0 || netcdf_proj.n_days_since_start < days_since_start) {
    return grpc::Status(
      grpc::StatusCode::INVALID_ARGUMENT,
      "days_since_start not between 0 and " + to_string(netcdf_proj.n_days_since_start)
    );
  }

  if (latitude < netcdf_proj.start_latitude ||
      netcdf_proj.end_latitude <= latitude) {
    return grpc::Status(
      grpc::StatusCode::INVALID_ARGUMENT,
      "latitude y not such that " + to_string(netcdf_proj.start_latitude) +
      " <= y < " + to_string(netcdf_proj.end_latitude)
    );
  }

  if (longitude < netcdf_proj.start_longitude ||
      netcdf_proj.end_longitude <= longitude) {
    return grpc::Status(
      grpc::StatusCode::INVALID_ARGUMENT,
      "longitude x not such that " + to_string(netcdf_proj.start_longitude) +
      " <= x < " + to_string(netcdf_proj.end_longitude)
    );
  }

  cout << "GetValue for " << endl;
  cout << "Days since start: " << days_since_start << std::endl;
  cout << "Latitude        : " << latitude << std::endl;
  cout << "Longitude       : " << longitude << std::endl;


  float result = netcdf_proj.get_projection(
    days_since_start,
    latitude,
    longitude
  );
  response->set_value(result);

  cout << "Value           : " << response->value() << endl;
  return grpc::Status::OK;
}
