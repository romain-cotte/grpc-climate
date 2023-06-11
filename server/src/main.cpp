#include <iomanip>
#include <iostream>
#include <netcdf>

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

// #include "netcdf_tools.h"
#include "tmax_service.h"

using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;


int main(int argc, char* argv[]) {
  string file_path = "./server/data/era5_Tmax_40.0_0.0_projection_2030.nc";

  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

  TmaxService my_service(file_path);
  builder.RegisterService(&my_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();

  return 0;
}


void test() {
  string file_path = "./server/data/era5_Tmax_40.0_0.0_projection_2030.nc";
  NetcdfProjection proj = NetcdfProjection(file_path);

  cout << std::setprecision(17);
  int days_since_start = 29;
  cout << "0, 40.0, 0.0: " << proj.get_projection(days_since_start, 40.0, 0.0) << endl;
  cout << "0, 40.0, 0.25: " << proj.get_projection(days_since_start, 40.0, 0.25) << endl;
  cout << "0, 40.25, 0.0: " << proj.get_projection(days_since_start, 40.25, 0.0) << endl;
  cout << "0, 40.25, 0.25: " << proj.get_projection(days_since_start, 40.25, 0.25) << endl;
  cout << "0, 44.4, 3.4: " << proj.get_projection(days_since_start, 44.4, 3.4) << endl;
}
