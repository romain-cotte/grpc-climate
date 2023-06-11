import xarray as xr
from datetime import datetime


ds = xr.open_dataset("./server/data/era5_Tmax_40.0_0.0_projection_2030.nc")

# print(f"min = {ds.min()}")
# print(f"max = {ds.max()}")


def f(lat, lon):
    r = ds.sel(
        date=datetime(2015, 1, 30),
        latitude=lat,
        longitude=lon
    )["tasmax"].values
    print(f"{lat} {lon} = {r}")


f(40.0, 0.0)
f(40.0, 0.25)
f(40.25, 0.0)
f(40.25, 0.25)
f(44.25, 3.25)

# Loop through all values
# mx = -100.0
# for x in ds:
#     print("{}: {}".format(x, ds[x].values))
#     for v in ds[x].values:
#         for i in v:
#             for j in i:
#                 if mx < j:
#                     mx = j

# print(f"mx = {mx}")


# You need to have netCDF4
# pip install netCDF4
# import xarray as xr

# ds = xr.open_dataset("file.nc")

# # From s3, you need to have h5netcdf
# import s3fs
# from datetime import datetime

# file_path = "s3://bucket/path/file.nc"
# fs = s3fs.S3FileSystem()
# with fs.open(file_path) as file_obj:
#     ds = xr.open_dataset(file_obj, engine="h5netcdf")


# ##################
# # DISPLAY VALUES #
# ##################
# arr: np.ndarray = ds.loc[dict(lon=-179.5, lat=-89.5, time=datetime(2022, 1, 1))]["variable"].values
# print(arr)
# r = ds.sel(latitude=40, longitude=10)
# for x in r:
#     print("{}: {}".format(x, r[x].values))
