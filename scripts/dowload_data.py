import cdsapi

c = cdsapi.Client()

c.retrieve(
    "projections-cmip6",
    {
        "format": "zip",
        "temporal_resolution": "monthly",
        "experiment": "ssp2_4_5",
        "variable": "near_surface_air_temperature",
        "model": "cnrm_cm6_1_hr",
        "year": [
            "2015", "2016", "2017",
            "2018", "2019", "2020",
            "2021", "2022", "2023",
            "2024", "2025", "2026",
            "2027", "2028", "2029",
            "2030",
        ],
        "month": [
            "01", "02", "03",
            "04", "05", "06",
            "07", "08", "09",
            "10", "11", "12",
        ],
    },
    "scripts/data/download.zip"
)
