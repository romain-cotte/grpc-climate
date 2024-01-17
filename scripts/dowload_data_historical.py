import cdsapi
import os
from parameters import YEARS_PRE, SCOPED_AREA, MONTHS_ALL, extract_and_remove

cur_dir = os.path.dirname(__file__)
experiment = "historical"
folder=f"{cur_dir}/data/{experiment}"
zip_file_destination=f"{folder}/download.zip"

if not os.path.exists(folder):
   os.makedirs(folder)

c = cdsapi.Client()
c.retrieve(
    "projections-cmip6",
    {
        "format": "zip",
        "temporal_resolution": "monthly",
        "variable": "surface_temperature",
        "model": "cnrm_cm6_1_hr",
        "year": YEARS_PRE,
        "experiment": experiment,
        "area": SCOPED_AREA,
        "month": MONTHS_ALL,
    },
    zip_file_destination
)

extract_and_remove(zip_file_destination, folder)
