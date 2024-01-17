import os
import zipfile

YEARS_PRE = [str(y) for y in range(1850, 2015)] # 2015 excluded
YEARS_POST = [str(y) for y in range(2015, 2101)]

SCOPED_AREA = [ 50, -5, 40, 5 ]
MONTHS_ALL = [
    "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"
]

def extract_and_remove(zip_path, destination):
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        for file_name in zip_ref.namelist():
            if file_name[-3:] == ".nc":
                print(f"Extracting {file_name} to {destination}")
                zip_ref.extract(file_name, path=destination)

    os.remove(zip_path)
