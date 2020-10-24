import shutil
import os


def remove_if_exist(dir):
    if os.path.isdir(dir):
        shutil.rmtree(dir)


def remove_file_if_exist(file):
    if os.path.isfile(file):
        os.remove(file)


rm_dirs = ['Build/', 'Binaries/', '.vs/',
           'DerivedDataCache/', 'Intermediate/', 'Saved',
           'Plugins/StrixSDK/Binaries/', 'Plugins/StrixSDK/Intermediate']

for dir in rm_dirs:
    remove_if_exist(dir)

rm_files = ['gff_08.sln']
for file in rm_files:
    remove_file_if_exist(file)
