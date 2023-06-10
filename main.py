import xarray as xr
from datetime import datetime


ds = xr.open_dataset("./server/data/era5_Tmax_40.0_0.0_projection_2030.nc")

import timeit
start = timeit.default_timer()

print(f"min = {ds.min()}")
print(f"max = {ds.max()}")

stop = timeit.default_timer()

print("{}s".format(stop - start))

# for a in ds:
#     print(f"a = {a}")
#     print(a.item(), a.values)


# arr: np.ndarray = ds.loc[dict(lon=-179.5, lat=-89.5, time=datetime(2022, 1, 1))]["variable"].values
# print(arr)
r = ds.sel(date=datetime(2022, 1, 1), latitude=40.25, longitude=0.25)
print(f"r = {r}")


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
