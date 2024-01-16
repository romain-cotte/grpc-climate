import os
import xarray as xr
import numpy as np

cur_dir = os.path.dirname(__file__)

file_name=f"{cur_dir}/data/tas_Amon_CNRM-CM6-1-HR_ssp245_r1i1p1f2_gr_20150116-20301216_v20191202.nc"


def kelvin_to_celsius(kelvin):
    return kelvin - 273.15

ds = xr.open_dataset(file_name)

arr = ds.sel(lat=48.0, lon=2.0, method="nearest")
print(f"arr = {arr}")

y = arr["tas"].values
x = arr["time"].values

# print(arr["tas"])

# print("lon", ds.coords["lon"].values)
# print("lat", ds.coords["lat"].values)
# print(ds.coords["height"].values.item())
