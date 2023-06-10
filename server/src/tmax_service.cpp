/**************************
* See implemmentation in .h as it does not compile
* vtable issue
***************************/

// #include <myproto/tmax.pb.h>
// #include <myproto/tmax.grpc.pb.h>
// #include <myproto/address.pb.h>
// #include <myproto/addressbook.grpc.pb.h>


// using namespace std;

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
