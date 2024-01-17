import cdsapi
import os
from parameters import YEARS_POST, SCOPED_AREA, MONTHS_ALL, extract_and_remove

cur_dir = os.path.dirname(__file__)
experiment = "ssp2_4_5"

def download_experiment(experiment):
    folder=f"{cur_dir}/data/post/{experiment}"
    if not os.path.exists(folder):
       os.makedirs(folder)

    zip_file_destination=f"{folder}/download.zip"

    c = cdsapi.Client()
    c.retrieve(
        "projections-cmip6",
        {
            "format": "zip",
            "temporal_resolution": "monthly",
            "variable": "surface_temperature",
            "model": "cnrm_cm6_1_hr",
            "year": YEARS_POST,
            "experiment": experiment,
            "area": SCOPED_AREA,
            "month": MONTHS_ALL,
        },
        zip_file_destination
    )

    extract_and_remove(zip_file_destination, folder)


experiments = [
    "ssp1_2_6",
    "ssp2_4_5",
    "ssp3_7_0",
    "ssp5_8_5",
]

for experiment in experiments:
    print(f"Launch download of experiment {experiment}")
    # download_experiment(experiment)
