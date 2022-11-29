@echo OFF

echo:
echo Running scripts...

python GenMFCCDataForCPP.py -n "mfcc_data" -d "../source/mfcc_data" -i "../source/mfcc_data" -t "file_templates" -cfile "mfcc_data_template.c" -hfile "mfcc_data_template.h" mfccconfig.yaml 

echo:
echo Done!

echo:
PAUSE
