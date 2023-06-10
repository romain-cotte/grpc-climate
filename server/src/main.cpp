#include <iostream>
#include <netcdf>

#include <myproto/address.pb.h>
#include <myproto/addressbook.grpc.pb.h>

#include <myproto/tmax.pb.h>
#include <myproto/tmax.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include "netcdf_tools.h"
#include "tmax_service.h"


using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// class AddressBookService final: public expcmake::AddressBook::Service {

// public:
//   virtual ::grpc::Status GetAddress(::grpc::ServerContext* context,
//                                     const ::expcmake::NameQuerry* request,
//                                     ::expcmake::Address* response) {
//     std::cout << "Server: GetAddress for \"" << request->name() << "\"." << std::endl;

//     response->set_name("Peter Peterson");
//     response->set_zip("12345");
//     response->set_country("Superland");

//     return grpc::Status::OK;
//   }
// };


// class TmaxService final: public netcdf::Tmax::Service {

// public:
//   virtual ::grpc::Status GetValue(::grpc::ServerContext* context,
//                                   const ::netcdf::DateLocation* request,
//                                   ::netcdf::Temperature* response) {
//     cout << "GetValue for " << endl;
//     cout << "Days since start:" << request->days_since_start() << std::endl;
//     cout << "Latitude        :" << request->latitude() << std::endl;
//     cout << "Longitude       :" << request->longitude() << std::endl;

//     response->set_value(0.0);

//     return grpc::Status::OK;
//   }
// };


int main(int argc, char* argv[]) {
  NcFile nc_file("./server/data/era5_Tmax_40.0_0.0_projection_2030.nc", NcFile::read);
  display_header_group(nc_file);

  // cout << f(5) << endl;

  grpc::ServerBuilder builder;
  builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

  // AddressBookService my_service;
  // builder.RegisterService(&my_service);

  TmaxService my_service;
  builder.RegisterService(&my_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();

  return 0;
}
