# Docs


```proto
syntax = "proto3";

package netcdf;

message DateLocation {
  uint32 days_since_start = 1;
  float latitude = 2;
  float longitude = 3;
}

message Temperature {
  float value = 1;
}

service Tmax {
  rpc GetValue(DateLocation) returns (Temperature) {}
}
```