# Climate project

This project provides a [GRPC](https://grpc.io/) server that yields temperatures
provided by [copernicus](https://www.copernicus.eu/). Both historical
and simulated measurements are available. Only temperatures are used for now.

There is a convenient interface to dowload netcdf file available at https://cds.climate.copernicus.eu/cdsapp#!/dataset/projections-cmip6

Here is an overview of the surface temperature according to one particular
model:

![Warming stripes](https://github.com/romain-cotte/grpc-climate/blob/master/scripts/figures/warming_stripes.png)

![Scenarios comparaison](https://github.com/romain-cotte/grpc-climate/blob/master/scripts/figures/scenarios_comparaison.png)


## Prerequisites

### ncdump

In order to inspect netcdf file you can use the ncdump tool. You can install it
with:
```sh
sudo apt install netcdf-bin
```

### grpcurl

[grpcurl](https://github.com/fullstorydev/grpcurl) is a tool to make request to a grpc server with command line.
Installation:

```sh
grpcurl_version=$(curl -sS https://api.github.com/repos/fullstorydev/grpcurl/tags | jq .[0].name | tr -d 'v"')
curl -sSL "https://github.com/fullstorydev/grpcurl/releases/download/v${grpcurl_version}/grpcurl_${grpcurl_version}_linux_x86_64.tar.gz" | sudo tar -xz -C /usr/local/bin
```

## GRPC Server

An example of a grpc server, built with cmake:

 * git@github.com:faaxm/exmpl-cmake-grpc.git


## Memory consumption considerations

Number of tiles: 36 * 18 = 648
Total size for one feature: 648 * 70MB = 43360MB = 43.36GB
